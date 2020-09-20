// Framebuffer writer writes individual pixels and places them in a fifo.
// 
//
// The inspiration for this test is from the Alice4 project.
// Matthew J Atkin // Jack Allan
// 1-Sept 2020

module framebuffer_write 
(
	input wire clock,									
   input wire reset_n,								// Active low reset.

	output reg [28:0] address,						// DDR3 address
   output wire [7:0] burstcount,					// Number of bursts in the transactions
   input wire waitrequest,							// Wait request. 
   output reg [63:0] writedata,						// Data to write onto the bus? 
   output reg [7:0] byteenable,						// Marker to indicate whether the read is valid.
   output reg write,								// Read data signal.

	input wire buffer,
	input wire pixel_clock,
	input wire pixel_valid,
	input wire sync
);

// State Machine Variables
parameter STATE_INIT = 4'h0;
parameter STATE_IDLE = 4'h1;
parameter STATE_WRITE = 4'h2;
parameter STATE_FINISH_WRITING = 4'h3;
parameter STATE_CLEAR_FIFO = 4'h4;

parameter FRAMEBUFFER1_START = 29'h0700_0000;
parameter FRAMEBUFFER1_END = 29'h0702_5800;
parameter FRAMEBUFFER2_START = 29'h0702_5800;
parameter FRAMEBUFFER2_END = 29'h0704_b000;
//parameter WORDS_TO_READ = 8'h1F;

parameter HORIZONTAL_RESOLUTION = 10'h1E0;

assign burstcount = 8'h01;	

reg clear_fifo;
wire [5:0] fifo_size;
reg [28:0] current_address;
reg [7:0] words_queued;
reg [7:0] words_waiting;
reg [19:0] current_frame_words;
reg [3:0] current_state = STATE_INIT;

/*
framebuffer_write_fifo pixel_fifo
(
	.aclr(clear_fifo),
	.data(writedata),
	.rdclk(~pixel_clock),
	.rdreq(pixel_valid),
	.wrclk(clock),
	.wrreq(writedatavalid),
	.q(pixel),
	.wrusedw(fifo_size)
);
*/

reg [15:0] vertex_ax = 16'h64;
reg [15:0] vertex_ay = 16'd64;

reg [15:0] vertex_bx = 16'd400;
reg [15:0] vertex_by = 16'd200;

reg [15:0] vertex_cx = 16'd200;
reg [15:0] vertex_cy = 16'd400;

reg [63:0] tri_colour = 64'hCAFEBABE;

reg write_data_enable = 1'b1;

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		current_address <= 29'h0;
		current_state <= STATE_INIT;			

	end else begin
		case(current_state)
			STATE_INIT: begin
				current_state <= STATE_IDLE;
				write <= 1'b0;		
				byteenable <= 8'hFF;
				tri_colour = 64'hDEADBEEFCAFEBABE;				
			end
			
			STATE_IDLE: begin
				write <= 1'b1;
				address <= FRAMEBUFFER1_START;
				writedata <= tri_colour;
				
				if(!waitrequest)
					current_state <= STATE_WRITE;	
			end
			
			STATE_WRITE: begin
					current_state <= STATE_INIT;			
				end			
		endcase
	end
end
	
endmodule
