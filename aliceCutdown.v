module aliceCutdown(
	input clock_50,
	
	input [3:0] SW,
	input reset_KEY0,
	input start_KEY1,
	
	inout  I2C_SDA,
	output I2C_SCL,
	output wire [23:0] HDMI_TX,
	output HDMI_TX_HS,
	output HDMI_TX_VS,
	output HDMI_TX_DE,
	output HDMI_TX_CLK,
	
	output wire [7:0] leds,
	output H_SYNC, 
	output V_SYNC, 
	
	// HPS specific inputs / outputs
  /* SSTL-15 Class I */
	output [14:0] hps_ddr3_addr,
   output [2:0] hps_ddr3_ba,
	output hps_ddr3_cas_n,
   output hps_ddr3_cke,
   output hps_ddr3_cs_n,
   output [3:0] hps_ddr3_dm,
   inout [31:0] hps_ddr3_dq,
   output hps_ddr3_odt,
   output hps_ddr3_ras_n,
   output hps_ddr3_reset_n,
   input hps_ddr3_rzq,
   output hps_ddr3_we_n,
   
	/* DIFFERENTIAL 1.5-V SSTL CLASS I */
   output hps_ddr3_ck_n,
   output hps_ddr3_ck_p,
   inout [3:0] hps_ddr3_dqs_n,
   inout [3:0] hps_ddr3_dqs_p

);


// To communicate with the Avalon MM Slave, a series of wires are used.
wire [28:0] sdram0_address; 
wire [7:0] sdram0_burstcount;
wire sdram0_waitrequest;
wire [63:0] sdram0_readdata;
wire sdram0_readdatavalid;
wire sdram0_read;

wire [63:0] sdram0_writedata;	 
wire [7:0] sdram0_byteenable;	 
wire sdram0_write;

/*
// Using SDRAM 0 as a test interface.	 
SDRAM_test u1(
    .clock(clock_50),
    .reset_n(SW[3]),
    .address(sdram0_address),
    .burstcount(sdram0_burstcount),
    .waitrequest(sdram0_waitrequest),
    .readdata(sdram0_readdata),
    .readdatavalid(sdram0_readdatavalid),
    .read(sdram0_read),
    .writedata(sdram0_writedata),
    .byteenable(sdram0_byteenable),
    .write(sdram0_write)
);
*/

soc_system u0 (

		// Physical memory interface.
      .memory_mem_a(hps_ddr3_addr),
      .memory_mem_ba(hps_ddr3_ba),
      .memory_mem_ck(hps_ddr3_ck_p),
      .memory_mem_ck_n(hps_ddr3_ck_n),
      .memory_mem_cke(hps_ddr3_cke),
      .memory_mem_cs_n(hps_ddr3_cs_n),
      .memory_mem_ras_n(hps_ddr3_ras_n),
      .memory_mem_cas_n(hps_ddr3_cas_n),
      .memory_mem_we_n(hps_ddr3_we_n),
      .memory_mem_reset_n(hps_ddr3_reset_n),
      .memory_mem_dq(hps_ddr3_dq),
      .memory_mem_dqs(hps_ddr3_dqs_p),
      .memory_mem_dqs_n(hps_ddr3_dqs_n),
      .memory_mem_odt(hps_ddr3_odt),
      .memory_mem_dm(hps_ddr3_dm),
		.memory_oct_rzqin(hps_ddr3_rzq),
		  
		 // Clock resets and system clock.
		.reset_reset_n                       (1'b1),                        //                 reset.reset_n	
		.clk_clk                             (clock_500),                             //                   clk.clk
		
		// sdram0: SDRAM interface for front buffer video scan-out.
		.hps_0_f2h_sdram0_data_address(sdram0_address),
	   .hps_0_f2h_sdram0_data_burstcount(sdram0_burstcount),
		.hps_0_f2h_sdram0_data_waitrequest(sdram0_waitrequest),
      .hps_0_f2h_sdram0_data_readdata(sdram0_readdata),
      .hps_0_f2h_sdram0_data_readdatavalid(sdram0_readdatavalid),
      .hps_0_f2h_sdram0_data_read(sdram0_read),
		.hps_0_f2h_sdram0_data_writedata     (sdram0_writedata),     //                      .writedata
		.hps_0_f2h_sdram0_data_byteenable    (sdram0_byteenable),    //                      .byteenable
		.hps_0_f2h_sdram0_data_write         (sdram0_write),         //                      .write
		
		
		
		// I2C is not used.
		.hps_0_i2c1_out_data                 ( ),                 //            hps_0_i2c1.out_data
		.hps_0_i2c1_sda                      ( ),                      //                      .sda
		.hps_0_i2c1_clk_clk                  ( ),                  //        hps_0_i2c1_clk.clk
		.hps_0_i2c1_scl_in_clk               ( )               //     hps_0_i2c1_scl_in.clk
	
	);

	
reg [7:0] HDMI_RED = 8'hFF;
reg [7:0] HDMI_GRN = 8'h00;
reg [7:0] HDMI_BLU = 8'h00;

//assign HDMI_TX = {HDMI_RED,HDMI_GRN,HDMI_BLU};

framebuffer_read data_out
(
    .clock(clock_500),
    .reset_n(SW[3]),
    .address(sdram0_address),
    .burstcount(sdram0_burstcount),
    .waitrequest(sdram0_waitrequest),
    .readdata(sdram0_readdata),
    .readdatavalid(sdram0_readdatavalid),
    .read(sdram0_read),
    .writedata(sdram0_writedata),
    .byteenable(sdram0_byteenable),
    .write(sdram0_write),
	 
	 .data(HDMI_TX),
	 .leds(leds),
	 .pixel_clock(HDMI_TX_CLK & HDMI_TX_DE),
	 .sync(HDMI_TX_VS)
);

PLL500 memclock (
	.refclk(clock_50), 
	.rst(1'b0), 
	.outclk_0(clock_500)

);

first480 _480 (
	.refclk(clock_50), 
	.rst(1'b0), 
	.outclk_0(clock_480)

);


//turns 50MHz system clock into;
// 130MHz pixel clock for 1080p
// 65MHz pixel clock for 768p
// 25.175MHz pixel clock for 480p
PLL systemClockToPixel (
.refclk(clock_50), 
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
.clock_480p(clock_480), 
.clock_768p(clock768), 
.clock_1080p(clock_148), 
.reset(reset_KEY0), 
.start(i2c_end), 
.switch(SW), 
.horizontal_sync(HDMI_TX_HS), 
.vertical_sync(HDMI_TX_VS), 
.data_enable(HDMI_TX_DE), 
.pixel_clock(HDMI_TX_CLK));

assign H_SYNC = clock_480;
assign V_SYNC = clock_480;

endmodule
