module register
#(parameter WIDTH = 32)
(
    input       [WIDTH-1:0] D,
    input                   clk,
    input                   reset,
    input                   load,
    
    output reg  [WIDTH-1:0] Q
);

always @(posedge(clk), negedge(reset))
begin
    if(reset == 1'b0)
    begin
        Q <= 0;
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
