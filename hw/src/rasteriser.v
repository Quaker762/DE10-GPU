module rasteriser
(
	input clock,
	input reset_n,
	
	input [287:0] vertex_data,
	input vertex_data_valid,
	output vertex_data_full,
	output vertex_data_empty,
	input vertex_data_clock,
	output [3:0] state,
	
	output wire [63:0] pixel_data,
   output wire pixel_data_valid,
	input pixel_fifo_full
	 

);

reg clear_fifo;
reg request_data;

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
parameter STATE_START = 4'h1;
parameter STATE_A = 4'h2;
parameter STATE_B = 4'h3;
parameter STATE_C = 4'h4;

assign state = current_state;

reg [3:0] current_state;

rasteriser_fifo vertex_data_fifo(
	.aclr(clear_fifo),
	.data(vertex_data),
	.rdclk(clock),
	.rdreq(request_data), // We have this set up to acknowledge, not request
	.wrclk(vertex_data_clock),
	.wrreq(vertex_data_valid),
	.q({vertex_a_x, vertex_a_y, vertex_b_x, vertex_b_y, vertex_c_x, vertex_c_y, vertex_a_colour, vertex_b_colour, vertex_c_colour}),
	.rdempty(vertex_data_empty),
	.wrfull(vertex_data_full)
);

assign pixel_data[31:0] = current_colour;

reg [31:0] current_colour;
reg draw_line;
wire draw_done;
reg [11:0] x1, x2, y1, y2;

draw_line bresenham
(
	.clock(clock),
	.reset_n(reset_n),
	
	.x1(x1),
	.x2(x2),
	.y1(y1),
	.y2(y2),
	
	.draw(draw_line),
	.stall(pixel_fifo_full),
	
	.x(pixel_data[63:48]),
	.y(pixel_data[47:32]),
	.valid(pixel_data_valid),
	.done(draw_done)
);

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		clear_fifo <= 1;
		request_data <= 0;
//		pixel_data_valid <= 0;
//		pixel_data <= 0;
		draw_line <= 0;
		current_state <= STATE_WAIT;
	end else begin
		case(current_state)
			STATE_WAIT: begin
				if(!vertex_data_empty) begin
					request_data <= 1;
					current_state <= STATE_START;
				end
				
				clear_fifo <= 0;
	//			pixel_data_valid <= 0;
				//draw_line <= 0;
			end
			
			STATE_START: begin
					draw_line <= 1;
					request_data <= 0;
					current_state <= STATE_A;
					x1 <= vertex_a_x[31:20];
					x2 <= vertex_b_x[31:20];
					y1 <= vertex_a_y[31:20];
					y2 <= vertex_b_y[31:20];
					current_colour <= vertex_a_colour;
			end
			
			STATE_A: begin
			//	pixel_data <= {4'b0, vertex_a_x[31:20], 4'b0, vertex_a_y[31:20], vertex_a_colour};
		//		pixel_data_valid <= 1;
				draw_line <= 0;
				if(draw_done) begin
					draw_line <= 1;
					current_state <= STATE_B;
					x1 <= vertex_b_x[31:20];
					x2 <= vertex_c_x[31:20];
					y1 <= vertex_b_y[31:20];
					y2 <= vertex_c_y[31:20];
					current_colour <= vertex_b_colour;
				end
			end
			
			STATE_B: begin
	//			pixel_data <= {4'b0, vertex_b_x[31:20], 4'b0, vertex_b_y[31:20], vertex_b_colour};
		//		pixel_data_valid <= 1;
				draw_line <= 0;
				if(draw_done) begin
					draw_line <= 1;
					current_state <= STATE_C;
					x1 <= vertex_c_x[31:20];
					x2 <= vertex_a_x[31:20];
					y1 <= vertex_c_y[31:20];
					y2 <= vertex_a_y[31:20];
					current_colour <= vertex_c_colour;
				end
			end
			
			STATE_C: begin
		//		pixel_data <= {4'b0, vertex_c_x[31:20], 4'b0, vertex_c_y[31:20], vertex_c_colour};
		//		pixel_data_valid <= 1;
				
				draw_line <= 0;
				if(draw_done) begin
					current_state <= STATE_WAIT;
				end
			end
		endcase
	end
end

endmodule