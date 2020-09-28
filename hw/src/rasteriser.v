module rasteriser
(
	input clock,
	input reset_n,
	
	input [287:0] vertex_data,
	input vertex_data_valid,
	output vertex_data_full,
	output vertex_data_empty,
	input vertex_data_clock,
	
	output reg [63:0] pixel_data,
   output reg pixel_data_valid,
	input pixel_fifo_full
	 

);

reg clear_fifo;
reg vertex_data_rasterised;

wire [31:0] vertex_a_x;
wire [31:0] vertex_a_y;
wire [31:0] vertex_b_x;
wire [31:0] vertex_b_y;
wire [31:0] vertex_c_x;
wire [31:0] vertex_c_y;
wire [31:0] vertex_a_colour;
wire [31:0] vertex_b_colour;
wire [31:0] vertex_c_colour;

parameter STATE_WAIT = 4'h0;
parameter STATE_A = 4'h1;
parameter STATE_B = 4'h2;
parameter STATE_C = 4'h3;

reg [3:0] current_state;

rasteriser_fifo vertex_data_fifo(
	.aclr(clear_fifo),
	.data(vertex_data),
	.rdclk(clock),
	.rdreq(vertex_data_rasterised), // We have this set up to acknowledge, not request
	.wrclk(vertex_data_clock),
	.wrreq(vertex_data_valid),
	.q({vertex_a_x, vertex_a_y, vertex_b_x, vertex_b_y, vertex_c_x, vertex_c_y, vertex_a_colour, vertex_b_colour, vertex_c_colour}),
	.rdempty(vertex_data_empty),
	.wrfull(vertex_data_full)
);

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		clear_fifo <= 1;
		vertex_data_rasterised <= 0;
		pixel_data_valid <= 0;
		pixel_data <= 0;
		current_state <= STATE_WAIT;
	end else begin
		case(current_state)
			STATE_WAIT: begin
				if(!vertex_data_empty) begin
					current_state <= STATE_A;
				end
				
				clear_fifo <= 0;
				pixel_data_valid <= 0;
				vertex_data_rasterised <= 0;
			end
			
			STATE_A: begin
				pixel_data <= {4'b0, vertex_a_x[31:20], 4'b0, vertex_a_y[31:20], vertex_a_colour};
				pixel_data_valid <= 1;
				current_state <= STATE_B;
			end
			
			STATE_B: begin
				pixel_data <= {4'b0, vertex_b_x[31:20], 4'b0, vertex_b_y[31:20], vertex_b_colour};
				pixel_data_valid <= 1;
				current_state <= STATE_C;
			end
			
			STATE_C: begin
				pixel_data <= {4'b0, vertex_c_x[31:20], 4'b0, vertex_c_y[31:20], vertex_c_colour};
				pixel_data_valid <= 1;
				vertex_data_rasterised <= 1;
				current_state <= STATE_WAIT;
			end
		endcase
	end
end

endmodule
