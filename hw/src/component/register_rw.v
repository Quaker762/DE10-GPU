/**
 *  Read write register. 
 *
 *  Contains two WIDTH-bit data inputs, allowing for two data paths to be set 
 */
module register_rw
#(parameter WIDTH = 32)
(
    input       [WIDTH-1:0] D,
    input       [WIDTH-1:0] D2,
    input                   clk,
    input                   reset,
    input                   load,
    input                   load2,
    
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
     else if(load2 == 1'b0)
     begin
        Q <= D2;
     end
    else
    begin
        Q <= Q;
    end
end

endmodule
