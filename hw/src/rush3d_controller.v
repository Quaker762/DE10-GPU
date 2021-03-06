module rush3d_controller
(
	input clock,
	input reset_n,
	
	input [63:0] control_status_in,
	output reg [63:0] control_status_out,
	output reg control_status_load,
	
	output reg fill_background_flag,
	output reg clock_verticies_flag,
	output reg current_buffer_flag,
	
	input [3:0] framebuffer_write_state,
	input [3:0] rasteriser_state,
	
	input vertex_data_full,
	
	input pixel_fifo_empty,
	input vertex_data_fifo_empty,
	input vsync
);

reg [7:0] current_state;

parameter STATE_IDLE = 8'h00;
parameter STATE_BACKGROUND_FILL = 8'h01;
parameter STATE_VALID_VERITICES_WAIT = 8'h02;
parameter STATE_VALID_VERITICES_FINISH = 8'h03;
parameter STATE_SWAP_BUFFER_WAIT = 8'h04;
parameter STATE_SWAP_BUFFER_FINISH = 8'h05;

parameter WRITE_STATE_WAIT = 4'h0;
parameter WRITE_STATE_WRITE = 4'h1;
parameter WRITE_STATE_PURGE = 4'h2;
parameter WRITE_STATE_BACKGROUND = 4'h3;

parameter SWAP_BUFFER_BIT 		= 64'h0000_0000_0000_0100;
parameter BACKGROUND_BIT 		= 64'h0000_0000_0000_0010;
parameter VALID_VERTICIES_BIT = 64'h0000_0000_0000_0001;

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		control_status_out <= 0;
		control_status_load <= 0;
		fill_background_flag <= 0;
		clock_verticies_flag <= 0;
		current_buffer_flag <= 0;
		current_state <= STATE_IDLE;
	end else begin
		case(current_state)
			STATE_IDLE: begin
				if(control_status_in & BACKGROUND_BIT) begin
					current_state <= STATE_BACKGROUND_FILL;
					fill_background_flag <= 1'b1;
					control_status_load <= 1'b1;
					control_status_out <= (control_status_in & (~BACKGROUND_BIT));
					
				end else if(control_status_in & VALID_VERTICIES_BIT) begin
					current_state <= STATE_VALID_VERITICES_WAIT;
	
				end else if(control_status_in & SWAP_BUFFER_BIT) begin
					current_state <= STATE_SWAP_BUFFER_WAIT;
				end
				
			end
			
			STATE_BACKGROUND_FILL: begin
				if(~(control_status_in & BACKGROUND_BIT)) begin
					control_status_load <= 1'b0;
					
					if(framebuffer_write_state == WRITE_STATE_BACKGROUND) begin
							fill_background_flag <= 1'b0;
							current_state <= STATE_IDLE;
					end
				end
			end
			
			STATE_VALID_VERITICES_WAIT: begin
				if(!vertex_data_full) begin
					clock_verticies_flag <= 1'b1;
					control_status_load <= 1'b1;
					control_status_out <= (control_status_in & (~VALID_VERTICIES_BIT));
					
					current_state <= STATE_VALID_VERITICES_FINISH;
				end
			end
			
			STATE_VALID_VERITICES_FINISH: begin
				if(~(control_status_in & VALID_VERTICIES_BIT)) begin
					control_status_load <= 1'b0;
					current_state <= STATE_IDLE;
				end
				clock_verticies_flag <= 1'b0;
			end
			
			STATE_SWAP_BUFFER_WAIT: begin
				if(pixel_fifo_empty && vertex_data_fifo_empty && vsync && (rasteriser_state == 4'h0)) begin
					current_buffer_flag <= ~current_buffer_flag;
					control_status_load <= 1'b1;
					control_status_out <= (control_status_in & (~SWAP_BUFFER_BIT));
					
					current_state <= STATE_SWAP_BUFFER_FINISH;
				end
			end
			
			STATE_SWAP_BUFFER_FINISH: begin
				if(~(control_status_in & SWAP_BUFFER_BIT)) begin
					control_status_load <= 1'b0;
					current_state <= STATE_IDLE;
				end
			end
			
		endcase
	end
end

endmodule
