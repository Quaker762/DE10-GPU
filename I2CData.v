// I2c Table Data Module
module I2CData
(
	input clock,
	input [5:0] count,
	output [23:0] table_data_out
);

reg [15:0] TABLE_DATA;

assign table_data_out = {8'h72,TABLE_DATA};

always @(negedge(clock)) begin
	case (count)
			0: TABLE_DATA <= 16'h4100; //Set N Value (6144)
			1: TABLE_DATA <= 16'h9803; //Set N Value (6144)
			2: TABLE_DATA <= 16'h9a70; //Set N Value (6144)
			3: TABLE_DATA <= 16'h9c30; //Input 444 (RGB or YCrCb) with separate syncs
			4: TABLE_DATA <= 16'h9d01; //44.1kHz fs, YPrPb 444
			5: TABLE_DATA <= 16'ha2a4; //CSC disabled
			6: TABLE_DATA <= 16'ha3a4; //General Control Packet Enable
			7: TABLE_DATA <= 16'he0d0; //Power Down Control
			8: TABLE_DATA <= 16'hf900; //Reverse bus, Data right justified
			9: TABLE_DATA <= 16'h1500; //Set Dither_mode - 12-to-10 bit
			10: TABLE_DATA <= 16'h1702; //12 bit Output
			11: TABLE_DATA <= 16'h1800; //Set RGB444 in AVinfo Frame
		
		default: TABLE_DATA	<= 16'h4110;
	
	endcase
end

endmodule 