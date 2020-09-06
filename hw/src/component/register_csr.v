module register_csr
#(parameter WIDTH = 32)
(
    input       [WIDTH-1:0] D_all,
    input						 D_bit,
	 input [$clog2(WIDTH)-1:0] bit_address,
    input                   clk,
    input                   reset,
    input                   load_all,
    input                   load_bit,
    
	 output  				    Q_bit,
    output reg  [WIDTH-1:0] Q_all
);

always @(posedge(clk), negedge(reset))
begin
    if(reset == 1'b0)
    begin
        Q_all <= 0;
    end
    else if(load_all == 1'b0)
    begin
        Q_all <= D_all;
    end
     else if(load_bit == 1'b0)
     begin
        Q_all[bit_address] <= D_bit;
     end
    else
    begin
        Q_all <= Q_all;
    end
end

assign Q_bit = Q_all[bit_address];

endmodule
