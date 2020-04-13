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
		// 	Power on
		6'h0	:	TABLE_DATA	<=	16'h4110;
		//	Default
		6'h1	:	TABLE_DATA	<=	16'h9803;  
		// Orientation
		6'h2	:	TABLE_DATA	<=	16'h9AE0;  
		6'h3	:	TABLE_DATA	<=	16'h9C30;  
		6'h4	:	TABLE_DATA	<=	16'h9D61;  
		6'h5	:	TABLE_DATA	<=	16'hA2A4;  
		6'h6	:	TABLE_DATA	<=	16'hA3A4;  
		6'h7	:	TABLE_DATA	<=	16'hE0D0;  
		6'h8	:	TABLE_DATA	<=	16'hF900;  
		// Format information status
		6'h9	:	TABLE_DATA	<=	16'h5500;  
		
		// Video Mode (Input)
		//	[7:4] Audio Frequency; [3:0] Video format, 24-bit RGB 4:4:4
		6'hA	:	TABLE_DATA	<=	16'h1500;
		//	Color Depth	
		6'hB	:	TABLE_DATA	<=	16'h1630;  
		//	Aspect ratio
		6'hC	:	TABLE_DATA	<=	16'h1700;  
		// Video Mode (Output)
		//	Default Valyue
		6'hD	:	TABLE_DATA	<=	16'h1846; 
		//	Output Type (HDMI)
		6'hE	:	TABLE_DATA	<=	16'hAF14;  
		
		// HDCP
		6'hF	:	TABLE_DATA	<=	16'h9700;  //	Disable interrupts
		
		// Audio
		6'h10	:	TABLE_DATA	<=	16'h0100; 
		6'h11	:	TABLE_DATA	<=	16'h0218;  
		6'h12	:	TABLE_DATA	<=	16'h0300;  
		6'h13	:	TABLE_DATA	<=	16'h5608;
		
		default: TABLE_DATA	<= 16'h4110;
	
	endcase
end

endmodule 