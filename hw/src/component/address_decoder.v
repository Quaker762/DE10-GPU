/**
 *  Address decoder module. 
 *
 *  Decodes a 3-bit input address from QSYS into a 4-bit output. Each bit a select
 *  pin for a register loacated in a register file. 
 */
module address_decoder
(
    input               ce,     // Chip enable register
    input      [2:0]    address, // 3-bit Input address
    output reg [5:0]    out     // Output of the decoder
);


always @(ce, address)
begin
    if(ce == 1'b1) // The chip is enabled
    begin
        case(address)
        3'b000:
            out <= 6'h01;   // Control register load enable (from HPS)
        3'b001:
            out <= 6'h02;   // Control register load enable (from Card)     
        3'b010:
            out <= 6'h04;   // Address register load enable (from HPS)
        3'b011:
            out <= 6'h08;   // Data register load enable (from HPS)
        3'b100:
            out <= 6'h10;   // Data Register load enable (from Card)
        3'b101:
            out <= 6'h11;   //test
        default:
            out <= 6'h00;
        endcase
    end
    else
    begin
        out <= 6'h00; // Default value, nothing is selected
    end
end

endmodule 