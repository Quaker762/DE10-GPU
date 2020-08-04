// Framebuffer reader reads from the framebuffers and places them in a fifo.
// The pixel clock is then used to pop the pixel data out of ther fifo.
//
// The inspiration for this test is from the Alice4 project.
// Matthew J Atkin
// 10-Aug 2020

module framebuffer_read 
(
	input wire clock,									
    input wire reset_n,								// Active low reset.

	output reg [28:0] address,						// DDR3 address
    output wire [7:0] burstcount,					// Number of bursts in the transactions
    input wire waitrequest,							// Wait request. 
    input wire [63:0] readdata,						// Data to write onto the bus? 
    input wire readdatavalid,						// Marker to indicate whether the read is valid.
    output reg read,								// Read data signal.

	input wire buffer,
	output wire [31:0] pixel,
	input wire pixel_clock,
	input wire pixel_valid,
	input wire sync

);
// State Machine Variables
parameter STATE_INIT = 4'h0;
parameter STATE_IDLE = 4'h1;
parameter STATE_READ = 4'h2;
parameter STATE_FINISH_READING = 4'h3;
parameter STATE_CLEAR_FIFO = 4'h4;

parameter FRAMEBUFFER1_START = 29'h0700_0000;
parameter FRAMEBUFFER1_END = 29'h0702_5800;
parameter FRAMEBUFFER2_START = 29'h0702_5800;
parameter FRAMEBUFFER2_END = 29'h0704_b000;
parameter WORDS_TO_READ = 8'h1F;

assign burstcount = 8'h01;	

reg clear_fifo;
wire [5:0] fifo_size;
reg [28:0] current_address;
reg [7:0] words_queued;
reg [7:0] words_waiting;
reg [19:0] current_frame_words;
reg [3:0] current_state = STATE_INIT;

framebuffer_fifo pixel_fifo
(
	.aclr(clear_fifo),
	.data(readdata),
	.rdclk(~pixel_clock),
	.rdreq(pixel_valid),
	.wrclk(clock),
	.wrreq(readdatavalid),
	.q(pixel),
	.wrusedw(fifo_size)
);

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		current_state <= STATE_INIT;
		address <= 29'h0;
		current_address <= 29'h0;
		read <= 1'b0;
		words_queued <= 8'h0;
		words_waiting <= 8'h0;
		current_frame_words <= 20'h0;
		clear_fifo <= 1;
	end else begin
		case(current_state)
			STATE_INIT: begin
				current_state <= STATE_IDLE;
				current_frame_words<= 20'h0;
				clear_fifo <= 0;
				read <= 1'b0;
				
				if(buffer) begin
					current_address <= FRAMEBUFFER1_START;
				end else begin
					current_address <= FRAMEBUFFER2_START;
				end
			end
			
			STATE_IDLE: begin
				if(sync) begin
					current_state <= STATE_FINISH_READING;
				end else if(fifo_size[5] == 1'b0) begin
					words_waiting <= 8'h0;
					words_queued <= 8'h0;
					current_state <= STATE_READ;
				end
			end
			
			STATE_READ: begin
				if(readdatavalid) begin
					if(words_queued == WORDS_TO_READ - 1) begin
						current_state <= STATE_IDLE;
					end

					words_queued <= words_queued + 1'b1;
				end
				
				if(sync) begin
					read <= 1'b0;
					current_state <= STATE_FINISH_READING;
				end else if(read && waitrequest) begin
					// wait
				end else begin
					if(words_waiting < WORDS_TO_READ) begin
						address <= current_address;
						read <= 1'b1;
						
						words_waiting <= words_waiting + 1'b1;
						
						if(current_address == FRAMEBUFFER1_END - 1 || current_address == FRAMEBUFFER2_END - 1) begin
							if(buffer) begin
								current_address <= FRAMEBUFFER1_START;
							end else begin
								current_address <= FRAMEBUFFER2_START;
							end
						end else begin
							current_address <= current_address + 1'b1;
						end
					end else begin
						read <= 1'b0;
					end
				end
			end
	
			STATE_FINISH_READING: begin
				if(readdatavalid) begin
					words_queued <= words_queued + 1'b1;
				end
				
				if(words_waiting == words_queued) begin
					current_state <= STATE_CLEAR_FIFO;	
				end
			end
			
			STATE_CLEAR_FIFO: begin
				clear_fifo <= 1;
				current_state <= STATE_INIT;
			end
			
		endcase
	end
end
	
endmodule
