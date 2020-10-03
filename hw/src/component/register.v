module register
#(parameter WIDTH = 32)
(
    input       [WIDTH-1:0] D,
    input                   clk,
    input                   reset,
	 input 		 [WIDTH-1:0] reset_value,
    input                   load,
    
    output reg  [WIDTH-1:0] Q
);

always @(posedge(clk), negedge(reset))
begin
    if(reset == 1'b0)
    begin
        Q <= reset_value;
    end
    else if(load == 1'b0)
    begin
        Q <= D;
    end
    else
    begin
        Q <= Q;
    end
end

endmodule
