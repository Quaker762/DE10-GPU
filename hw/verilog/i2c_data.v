// I2c Table Data Module - Jack Allan - 2020
module I2C_DATA
(
    input CLK,
    input [5:0] count,
    output [23:0] table_Data
);

reg [15:0] table_Data_Value;
assign table_Data = {8'h72,table_Data_Value};

always @(negedge(CLK)) begin
    case (count)
        //     Power on
        6'h0    :    table_Data_Value    <=    16'h4110;
        //    Default
        6'h1    :    table_Data_Value    <=    16'h9803;
        // Orientation
        6'h2    :    table_Data_Value    <=    16'h9AE0;
        6'h3    :    table_Data_Value    <=    16'h9C30;
        6'h4    :    table_Data_Value    <=    16'h9D61;
        6'h5    :    table_Data_Value    <=    16'hA2A4;
        6'h6    :    table_Data_Value    <=    16'hA3A4;
        6'h7    :    table_Data_Value    <=    16'hE0D0;
        6'h8    :    table_Data_Value    <=    16'hF900;
        // Format information status
        6'h9    :    table_Data_Value    <=    16'h5500;
        // Video Mode (Input)
        //    [7:4] Audio Frequency; [3:0] Video format, 24-bit RGB 4:4:4
        6'hA    :    table_Data_Value    <=    16'h1500;
        //    Color Depth
        6'hB    :    table_Data_Value    <=    16'h1630;
        //    Aspect ratio
        6'hC    :    table_Data_Value    <=    16'h1700;
        // Video Mode (Output)
        //    Default Value
        6'hD    :    table_Data_Value    <=    16'h1846; 
        //    Output Type (HDMI)
        6'hE    :    table_Data_Value    <=    16'hAF14;
        // HDCP
        6'hF    :    table_Data_Value    <=    16'h9700;  //    Disable interrupts
        // Audio
        6'h10    :    table_Data_Value    <=    16'h0100; 
        6'h11    :    table_Data_Value    <=    16'h0218;
        6'h12    :    table_Data_Value    <=    16'h0300;
        6'h13    :    table_Data_Value    <=    16'h5608;

        default: table_Data_Value    <= 16'h4110;

    endcase
end

endmodule