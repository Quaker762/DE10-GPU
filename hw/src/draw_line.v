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
/*
// File: linedraw.v
// This is the linedraw design for EE178 Lab #6.

// The `timescale directive specifies what the
// simulation time units are (1 ns here) and what
// the simulator time step should be (1 ps here).

`timescale 1 ns / 1 ps

// Declare the module and its ports. This is
// using Verilog-2001 syntax.

module linedraw (
  input wire go,
  output wire busy,
  input wire [11:0] stax,
  input wire [11:0] stay,
  input wire [11:0] endx,
  input wire [11:0] endy,
  output wire wr,
  output wire [31:0] addr,
  input wire pclk
  );

parameter [1:0] IDLE = 2'd0;
parameter [1:0] RUN = 2'd1;
parameter [1:0] DONE = 2'd2;

reg [1:0] state;
reg signed [12:0] err;
reg signed [11:0] x, y;
wire signed [11:0] deltax, deltay, dx, dy, x0, x1, y0, y1, next_x, next_y, xa, ya, xb, yb;
wire signed [12:0] err_next, err1, err2, e2;

wire  in_loop, right, down, complete, e2_lt_dx, e2_gt_dy;

//FSM
always @ (posedge pclk)
begin
  case (state)
    IDLE : if (go)
             state <= RUN;
           else
             state <= IDLE;

    RUN : if (complete)
             state   <= DONE;
          else
             state   <= RUN;

    DONE : if (go)
             state <= RUN;
           else
             state <= IDLE;

    default : state <= IDLE;
  endcase
 end



//Line Drawing Algorithm

//Data Path for dx, dy, right, down
assign x0 =  stax;
assign x1 =  endx;
assign deltax = x1 - x0;
assign right = ~(deltax[7]);
assign dx = (!right) ? (-deltax) : (deltax);

assign y0 = stay;
assign y1 = endy;
assign deltay = y1 - y0;
assign down = ~(deltay[7]);
assign dy = (down) ? (-deltay) : (deltay);

//Data Path for Error

assign e2 = err << 1;
assign e2_gt_dy = (e2 > dy) ? 1 : 0;
assign e2_lt_dx = (e2 < dx) ? 1 : 0;
assign err1 = e2_gt_dy ? (err + dy) : err;
assign err2 = e2_lt_dx ? (err1 + dx) : err1;
assign err_next = (in_loop) ? err2 : (dx + dy);
assign in_loop = (state == RUN);

//Data Path for X and Y
assign next_x = (in_loop) ? xb : x0;
assign xb = e2_gt_dy ? xa : x;
assign xa = right ? (x + 1) : (x - 1);

assign next_y = (in_loop) ? yb : y0;
assign yb = e2_lt_dx ? ya : y;
assign ya = down ? (y + 1) : (y - 1);

assign complete = ( (x == x1) && (y == y1) );

always @(posedge pclk)
 begin
    err <= err_next;
    x <= next_x;
    y <= next_y;
 end

assign busy = in_loop;
assign wr = in_loop;
assign addr = {4'b0, x, 4'b0, y};

endmodule
*/