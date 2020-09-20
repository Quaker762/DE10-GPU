// SDRAM Test for DE-10 Nano SoC
// The RAM has been mapped via the Avalon Memory Mapped Interface.
// The inspiration for this test is from the Alice4 project.
// Dr. Glenn Matthews
// 23/04/2020

module SDRAM_test(
	input wire systemClock,								// 100MHz clock.
    input wire reset_n,									// Active low reset.
    output reg [28:0] address,						// DDR3 address
	 
    output wire [7:0] burstcount,					// Number of bursts in the transactions
    input wire waitrequest,							// Wait request.
	 
    input wire [63:0] readdata,						// Data to write onto the bus? 
    input wire readdatavalid,							// Marker to indicate whether the read is valid.
    output reg read,										// Read data signal.


    output reg [63:0] writedata,						// Data that has been written.
    output wire [7:0] byteenable,
    output reg write

);

// Parameters used to control the read / writes to memory.
assign burstcount = 8'h01;			// Only send one byte at a time.
assign byteenable = 8'hFF;			// Need to see what this one does.

// 1G minus 128M, in 64-bit units:
parameter FRAMEBUFFER1_START = 29'h0700_0000;
parameter FRAMEBUFFER1_END = 29'h0702_5800;
parameter FRAMEBUFFER2_START = 29'h0702_5800;
parameter FRAMEBUFFER2_END = 29'h0704_b000;

parameter TEST_DATA_A = 64'hDEAD_BEEF_CAFE_BABE;
parameter TEST_DATA_B = 64'hFF0F_00FF_FF0F_FF00;
parameter buffer = 1'b1;

// State Machine Variables
parameter STATE_INIT = 4'h0;
parameter STATE_WRITE = 4'h2;
parameter STATE_DONE = 4'h3;

// Current- and next-state varaibles.
reg [3:0] current_state = STATE_INIT;
reg [28:0] current_address = 29'h0;
reg [28:0] current_pixel = 29'h0;


always @(posedge(systemClock), negedge(reset_n)) begin
	if(!reset_n) begin
		current_pixel <= 29'h0;
		current_state <= STATE_INIT;
		address <= 29'h0;
		current_address <= 29'h0;
		write <= 1'b0;
		writedata <= TEST_DATA_A;
	end else begin
		case(current_state)
			STATE_INIT: begin
				current_state <= STATE_WRITE;
				write <= 1'b0;
				writedata <= TEST_DATA_A;
			
				if(buffer) begin
					current_address <= FRAMEBUFFER1_START;
				end else begin
					current_address <= FRAMEBUFFER2_START;
				end
			end
			
			STATE_WRITE: begin	
				if(waitrequest) begin
					current_state <= STATE_WRITE;
				end else	begin							
					if (current_address + current_pixel == FRAMEBUFFER1_END - 1 || current_address + current_pixel >= FRAMEBUFFER2_END - 1) begin
						if(buffer) begin
							current_address <= FRAMEBUFFER1_START;
						end else begin
							current_address <= FRAMEBUFFER2_START;
						end 
						current_pixel <= 29'h0;
					end else begin
						current_pixel <= current_pixel + 1;
					end	
						address <= current_address + current_pixel;
						write <= 1'b1;
						current_state <= STATE_DONE; 
				end
			end	
				
			STATE_DONE: begin
					current_state <= STATE_INIT;	
			end			
		endcase
	end
end

endmodule
