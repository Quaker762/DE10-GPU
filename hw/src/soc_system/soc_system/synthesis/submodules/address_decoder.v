/**
 *  Address decoder module. 
 *
 *  Decodes a 8-bit input address from QSYS into an 11-bit output. Each bit a select
 *  pin for a register loacated in a register file. 
 */
module address_decoder
(
    input               ce,     // Chip enable register
    input      [7:0]    address, // 8-bit Input address
    output reg [10:0]    out     // Output of the decoder
);


always @(ce, address)
begin
    if(ce == 1'b1) // The chip is enabled
    begin
        case(address)
        8'h00:
            out <= 11'b00000000001;
        8'h01:
            out <= 11'b00000000010;
        8'h02:
            out <= 11'b00000000100;
        8'h03:
            out <= 11'b00000001000;
        8'h04:
            out <= 11'b00000010000;
		  8'h05:
				out <= 11'b00000100000;
		  8'h06:
				out <= 11'b00001000000;
		  8'h07:
				out <= 11'b00010000000;
		  8'h08:
				out <= 11'b00100000000;
		  8'h09:
				out <= 11'b01000000000;
		  8'h0A:
				out <= 11'b10000000000;
        default:
            out <= 11'b00000000000;
        endcase
    end
    else
    begin
        out <= 11'b00000000000; // Default value, nothing is selected
    end
end

endmodule 