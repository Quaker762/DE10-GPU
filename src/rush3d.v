module rush3d
(
	input clock_50,
	input [9:0] slide_switches,
	input [3:0] keys,

	output [9:0] leds,
	
	/* VGA Outputs */
	output [7:0] vga_r,
	output [7:0] vga_g,
	output [7:0] vga_b,
	output vga_clk,
	output vga_blank_n,
	output vga_hs,
	output vga_vs,
	output vga_sync_n,

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

wire hsbridge_clock;

assign leds = slide_switches;

assign vga_r = 8'hFF;
assign vga_g = 8'hFF;
assign vga_b = 8'h00;

vga_controller vga_controller
(
	.refclk(clock_50),
	.reset_n(keys[0]),
	.resolution(slide_switches[1:0]),
	
	.pixel_clock(vga_clk),
	.hsync(vga_hs),
	.vsync(vga_vs),
	.sync_n(vga_sync_n),
	.blank_n(vga_blank_n)
);


soc_system u0
(
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
	.reset_reset_n(1'b1),
	.clk_clk(hsbridge_clock), 

	// sdram0: SDRAM interface for front buffer video scan-out.
	.hps_0_f2h_sdram0_data_address(sdram0_address),
	.hps_0_f2h_sdram0_data_burstcount(sdram0_burstcount),
	.hps_0_f2h_sdram0_data_waitrequest(sdram0_waitrequest),
	.hps_0_f2h_sdram0_data_readdata(sdram0_readdata),
	.hps_0_f2h_sdram0_data_readdatavalid(sdram0_readdatavalid),
	.hps_0_f2h_sdram0_data_read(sdram0_read),
	.hps_0_f2h_sdram0_data_writedata(sdram0_writedata),
	.hps_0_f2h_sdram0_data_byteenable(sdram0_byteenable),
	.hps_0_f2h_sdram0_data_write(sdram0_write),

	// I2C is not used.
	.hps_0_i2c1_out_data(),
	.hps_0_i2c1_sda(),
	.hps_0_i2c1_clk_clk(),
	.hps_0_i2c1_scl_in_clk()
);

SDRAM_test test
(
	.clock(clock_50),
	.reset_n(keys[0] && slide_switches[0]),
	.address(sdram0_address),
	.burstcount(sdram0_burstcount),
	.waitrequest(sdram0_waitrequest),
	.readdata(sdram0_readdata),
	.readdatavalid(sdram0_readdatavalid),
	.read(sdram0_read),
	.writedata(sdram0_writedata),
	.byteenable(sdram0_byteenable),
	.write(sdram0_write),
);

hsbridge_pll hsbridge_pll
(
	.refclk(clock_50), // 50MHz input
	.rst(1'b0),
	.outclk_0(hsbridge_clock) // 133MHz output
);


endmodule
