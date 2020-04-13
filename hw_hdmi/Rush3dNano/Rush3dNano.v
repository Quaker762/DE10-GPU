// TLE Module - Jack Allan - 2019
module Rush3dNano
(
	input FPGA_CLK1_50, 
	input [3:0] SW,
	input reset_KEY0,
	input start_KEY1,
	
	inout  I2C_SDA,
	output I2C_SCL,
	output [23:0] HDMI_TX,
	output HDMI_TX_HS,
	output HDMI_TX_VS,
	output HDMI_TX_DE,
	output HDMI_TX_CLK
);

reg [7:0] HDMI_RED = 8'hFF;
reg [7:0] HDMI_GRN = 8'h00;
reg [7:0] HDMI_BLU = 8'h00;

assign HDMI_TX = {HDMI_RED,HDMI_GRN,HDMI_BLU};

//turns 50MHz system clock into;
// 130MHz pixel clock for 1080p
// 65MHz pixel clock for 768p
// 25.175MHz pixel clock for 480p
PLL systemClockToPixel (
.refclk(FPGA_CLK1_50), 
.rst(1'b0), 
.outclk_0(clock480), 
.outclk_1(clock768), 
.outclk_2(clock1080), 
.outclk_3(clock5));

FreqDivider #(
.inputClockSpeed(5_000_000), 
.outputClockSpeed(400_000), 
.bitWidth(8)) slowClock(.inputclock(clock5), 
.clock_reset_n(reset_KEY0), 
.OutputClock(clock100k));

I2C startConfig (
.reset_n(reset_KEY0), 
.start_n(start_KEY1), 
.clock(clock100k), 
.sda_flag(I2C_SDA), 
.scl_flag(I2C_SCL), 
.stop_flag(i2c_end));

HdmiOutput HdmiOutput(
.clock_480p(clock480), 
.clock_768p(clock768), 
.clock_1080p(clock1080), 
.reset(reset_KEY0), 
.start(i2c_end), 
.switch(SW), 
.horizontal_sync(HDMI_TX_HS), 
.vertical_sync(HDMI_TX_VS), 
.data_enable(HDMI_TX_DE), 
.pixel_clock(HDMI_TX_CLK));

endmodule