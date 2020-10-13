module draw_line
(
	input clock,
	input reset_n,
	
	input [11:0] x1,
	input [11:0] x2,
	input [11:0] y1,
	input [11:0] y2,
	
	input draw,
	input stall,
	
	output reg [11:0] x,
	output reg [11:0] y,
	output reg valid,
	output reg done
);

reg [3:0] current_state; 

parameter STATE_IDLE = 4'h0;
parameter STATE_DRAW = 4'h1;

reg signed [11:0] dx, dy;
reg signed [12:0] err, err2;
reg down, right;

always @(posedge(clock), negedge(reset_n)) begin
	if(!reset_n) begin
		current_state <= STATE_IDLE;
		valid <= 0;
		done <= 0;
		x <= 0;
		y <= 0;
	end else begin
		case(current_state)
			STATE_IDLE: begin
				if(draw) begin
					dx = x2 - x1;
					right = dx >= 0;
					if(!right) dx = -dx;
					
					dy = y2 - y1;
					down = dy >= 0;
					if(down) dy = -dy;
					
					err = dx + dy;
					
					x <= x1;
					y <= y1;
					valid <= 1;
					
					current_state <= STATE_DRAW;
				end else begin
					valid <= 0;
					done <= 0;
				end
			end
			
			STATE_DRAW: begin
				if(x == x2 && y == y2) begin
					current_state <= STATE_IDLE;
					done <= 1;
					valid <= 0;
				end else if (!stall) begin
					valid <= 1;
					err2 = err << 1;
					
					if(err2 > dy) begin
						err = err + dy;
						if(right) 	x <= x + 1;
						else 			x <= x - 1;
					end
					
					if(err2 < dx) begin
						err = err + dx;
						if(down) 	y <= y + 1;
						else			y <= y - 1;
					end
				end else begin
					valid <= 0;
				end
			end
		endcase
	end
end

endmodule
