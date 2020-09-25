// SDRAM Test for DE-10 Nano SoC
// The RAM has been mapped via the Avalon Memory Mapped Interface.
// The inspiration for this test is from the Alice4 project.
// Dr. Glenn Matthews
// 23/04/2020

module framebuffer_write(
	 input wire clock,								// 100MHz clock.
    input wire reset_n,									// Active low reset.
	 
    output reg [28:0] address,						// DDR3 address
    output wire [7:0] burstcount,					// Number of bursts in the transactions
    input wire waitrequest,							// Wait request.
    output reg [63:0] writedata,						// Data that has been written.
    output reg [7:0] byteenable,
    output reg write,
	 
	 input wire buffer,
	 output wire writing_done,
	 input wire data_done,
	 input wire fill_background,
	 input wire [31:0] backround_colour,
	 
	 input wire [63:0] pixel_data,
	 input wire pixel_data_valid,
	 output wire pixel_fifo_full,
	 input wire pixel_data_clock,
	 
	 output [3:0] state

);

// Parameters used to control the read / writes to memory.
assign burstcount = 8'h01;			// Only send one byte at a time.
//assign byteenable = 8'b1111_1111;			// Need to see what this one does.

// 1G minus 128M, in 64-bit units:
parameter FRAMEBUFFER1_START = 29'h0700_0000;
parameter FRAMEBUFFER1_END = 29'h0702_5800;
parameter FRAMEBUFFER2_START = 29'h0702_5800;
parameter FRAMEBUFFER2_END = 29'h0704_b000;

parameter EVEN_WRITE = 8'b0000_1111;
parameter ODD_WRITE = 8'b1111_0000;
parameter FULL_WRITE = 8'b1111_1111;

parameter WIDTH_OFFSET = 640;

parameter TEST_DATA_A = 64'hFFFF_FFFF_FFFF_FF00;
parameter TEST_DATA_B = 64'hFF0F_00FF_FF0F_FF00;

// State Machine Variables
parameter STATE_WAIT = 4'h0;
parameter STATE_WRITE = 4'h1;
parameter STATE_PURGE = 4'h2;
parameter STATE_BACKGROUND = 4'h3;

assign state = current_state;

// Current- and next-state varaibles.
reg [3:0] current_state = STATE_WAIT;
reg [28:0] base_address = 29'h0;
reg [28:0] current_pixel = 30'h0;

reg clear_fifo;
reg pixel_written;
wire pixel_fifo_empty;

wire [15:0] pixel_x_address;
wire [15:0] pixel_y_address;
wire [31:0] pixel_colour;

//assign writedata = pixel_colour;
//assign writedata = {backround_colour, backround_colour} : pixel_colour;
//assign address = (base_address + pixel_x_address + (pixel_y_address * WIDTH_OFFSET));
//assign address = base_address;

framewriter_fifo pixels(
	.aclr(clear_fifo),
	.data(pixel_data),
	.rdclk(clock),
	.rdreq(pixel_written), // We have this set up to acknowledge, not request
	.wrclk(pixel_data_clock),
	.wrreq(pixel_data_valid),
	.q({pixel_x_address, pixel_y_address, pixel_colour}),
	.rdempty(pixel_fifo_empty),
	.wrfull(pixel_fifo_full)
);

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		current_state <= STATE_WAIT;
		//current_pixel <= 30'h0;
		base_address <= 29'h0;
		write <= 1'b0;
		clear_fifo <= 1'b1;
	   pixel_written <= 1'b0;
	end else begin
		case(current_state)
			STATE_WAIT: begin
				if(!pixel_fifo_empty) begin
					current_state <= STATE_WRITE;
				end
			
				if(fill_background) begin
					current_state <= STATE_BACKGROUND;
				end
				
				address <= 0;
				current_pixel <= 0;
				write <= 1'b0;
				clear_fifo <= 1'b0;
				pixel_written <= 1'b0;
			
				if(buffer) begin
					base_address <= FRAMEBUFFER1_START;
				end else begin
					base_address <= FRAMEBUFFER2_START;
				end
			end
			
			STATE_WRITE: begin	
				if(pixel_x_address % 2) begin
					byteenable <= ODD_WRITE;
					writedata <= {pixel_colour, 32'b0};
				end else begin
					byteenable <= EVEN_WRITE;
					writedata <= {32'b0, pixel_colour};
				end
				
				write <= 1'b1;
				address <= base_address + ((pixel_x_address + (pixel_y_address * WIDTH_OFFSET)) >> 1);
				current_state <= STATE_PURGE;
			end
			
			STATE_PURGE: begin	
				if(waitrequest) begin
				
				end else begin
					current_state <= STATE_WAIT;
					write <= 1'b0;
					pixel_written <= 1'b1;
				end
			end
			
			STATE_BACKGROUND: begin	
				if(waitrequest) begin

				end else	begin					
					if (base_address + current_pixel == FRAMEBUFFER1_END - 1 || base_address + current_pixel >= FRAMEBUFFER2_END - 1) begin
						current_state <= STATE_WAIT;
					end else begin
						current_pixel <= current_pixel + 1;
					end
					address <= base_address + current_pixel;
					writedata <= {backround_colour, backround_colour};
					write <= 1'b1;
					byteenable <= FULL_WRITE;

				end
			end	
				
						
		endcase
	end
end

endmodule
