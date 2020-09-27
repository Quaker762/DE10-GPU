module rush3d_controller
(
	input clock,
	input reset_n,
	
	input [63:0] control_status_in,
	output reg [63:0] control_status_out,
	output reg control_status_load,
	
	output reg fill_background_flag,
	output reg clock_verticies_flag,
	
	input [3:0] framebuffer_write_state
);

reg [7:0] current_state;

parameter STATE_IDLE = 8'h00;
parameter STATE_BACKGROUND_FILL = 8'h01;
parameter STATE_VALID_VERITICES = 8'h02;

parameter WRITE_STATE_WAIT = 4'h0;
parameter WRITE_STATE_WRITE = 4'h1;
parameter WRITE_STATE_PURGE = 4'h2;
parameter WRITE_STATE_BACKGROUND = 4'h3;

parameter BACKGROUND_BIT = 64'h0000_0000_0000_0010;
parameter VALID_VERTICIES_BIT = 64'h0000_0000_0000_0001;

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		control_status_out <= 0;
		control_status_load <= 0;
		fill_background_flag <= 0;
		clock_verticies_flag <= 0;
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
					current_state <= STATE_VALID_VERITICES;
					clock_verticies_flag <= 1'b1;
					control_status_load <= 1'b1;
					control_status_out <= (control_status_in & (~VALID_VERTICIES_BIT));
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
			
			STATE_VALID_VERITICES: begin
				if(~(control_status_in & VALID_VERTICIES_BIT)) begin
					control_status_load <= 1'b0;
					current_state <= STATE_IDLE;
				end
				clock_verticies_flag <= 1'b0;
			end
		endcase
	end
end

endmodule
