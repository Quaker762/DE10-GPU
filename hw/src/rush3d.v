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

wire [28:0] sdram1_address; 
wire [7:0] sdram1_burstcount;
wire sdram1_waitrequest;
wire [63:0] sdram1_writedata;	 
wire [7:0] sdram1_byteenable;	 
wire sdram1_write;




wire hsbridge_clock;
wire [31:0] pixel_data;
wire pixel_clock;
wire display_active;
wire sync;
wire current_buffer;
assign vga_vs = sync;
assign leds = slide_switches;

assign vga_clk = pixel_clock;
assign vga_r = pixel_data[23:16];
assign vga_g = pixel_data[15:8];
assign vga_b = pixel_data[7:0];

vga_controller vga_controller
(
	.refclk(clock_50),
	.reset_n(keys[0]),
	.resolution(slide_switches[1:0]),
	
	.pixel_clock(pixel_clock),
	.hsync(vga_hs),
	.vsync(sync),
	.sync_n(vga_sync_n),
	.blank_n(vga_blank_n),
	.pixel_test(test),
	
	.display_active(display_active)
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
	.reset_reset_n(keys[0]),
	.clk_clk(clock_50), 

	// sdram0: SDRAM interface for front buffer video scan-out.
	.hps_0_f2h_sdram0_data_address(sdram0_address),
	.hps_0_f2h_sdram0_data_burstcount(sdram0_burstcount),
	.hps_0_f2h_sdram0_data_waitrequest(sdram0_waitrequest),
	.hps_0_f2h_sdram0_data_readdata(sdram0_readdata),
	.hps_0_f2h_sdram0_data_readdatavalid(sdram0_readdatavalid),
	.hps_0_f2h_sdram0_data_read(sdram0_read),

	
	.hps_0_f2h_sdram1_data_address(sdram1_address),
	.hps_0_f2h_sdram1_data_burstcount(sdram1_burstcount),
	.hps_0_f2h_sdram1_data_waitrequest(sdram1_waitrequest),	
	.hps_0_f2h_sdram1_data_writedata(sdram1_writedata),
	.hps_0_f2h_sdram1_data_byteenable(sdram1_byteenable),
	.hps_0_f2h_sdram1_data_write(sdram1_write),	
		
	
	.register_file_0_conduit_end_export_vertex_c(vertex_c),            // register_file_0_conduit_end.export_vertex_c
	.register_file_0_conduit_end_export_vertex_a(vertex_a),            //                            .export_vertex_a
	.register_file_0_conduit_end_export_vertex_b(vertex_b),            //                            .export_vertex_b
	.register_file_0_conduit_end_export_control_status_out(control_status_out),  //                            .export_control_status_out
	.register_file_0_conduit_end_export_back_colour_out(back_colour_out),     //                            .export_back_colour_out
	.register_file_0_conduit_end_export_color_a_out(color_a),              //                            .export_color_a_out
	.register_file_0_conduit_end_export_color_b_out(color_b),              //                            .export_color_b_out
	.register_file_0_conduit_end_export_color_c_out(color_c),              //                            .export_color_c_out
	.register_file_0_conduit_end_export_win_size_out(),             //                            .export_win_size_out
	.register_file_0_conduit_end_export_control_status_load_fpga(control_status_load_fpga), //                            .export_control_status_load_fpga
	.register_file_0_conduit_end_export_control_status_in(control_status_in),        //                            .export_control_status_in

	// I2C is not used.
	.hps_0_i2c1_out_data(),
	.hps_0_i2c1_sda(),
	.hps_0_i2c1_clk_clk(),
	.hps_0_i2c1_scl_in_clk()
);

wire [63:0] vertex_a;
wire [63:0] vertex_b;
wire [63:0] vertex_c;
wire [31:0] color_a;
wire [31:0] color_b;
wire [31:0] color_c;
wire [63:0] control_status_out;
wire [63:0] control_status_in;
wire [31:0] back_colour_out;
wire control_status_load_fpga;
wire pixel_data_valid;
wire [63:0] rasterised_pixel_data;

wire vertex_data_fifo_empty;
wire pixel_fifo_empty;

wire fill_background_flag;
wire clock_verticies_flag;
wire [3:0] framebuffer_write_state;

framebuffer_write writer
(
	.clock(clock_50),
	.reset_n(keys[0]),
	.address(sdram1_address),
	.burstcount(sdram1_burstcount),
	.waitrequest(sdram1_waitrequest),
	.writedata(sdram1_writedata),
	.byteenable(sdram1_byteenable),
	.write(sdram1_write),
	.buffer(current_buffer),
	.fill_background(fill_background_flag),
	.backround_colour(back_colour_out),
	 
	//.pixel_data({4'b0, vertex_a[63:52], 4'b0, vertex_a[31:20], color_a[31:0]}),
	.pixel_data(rasterised_pixel_data),
	.pixel_data_valid(pixel_data_valid),
	.pixel_fifo_full(),
	.pixel_fifo_empty(pixel_fifo_empty),
	//.pixel_data_clock(clock_verticies_flag || ~keys[1]), /// ??????
	.pixel_data_clock(clock_50),
	.state(framebuffer_write_state)
);

rasteriser raster
(
	.clock(clock_50),
	.reset_n(keys[0]),
	
	.vertex_data({vertex_a, vertex_b, vertex_c, color_a, color_b, color_c}),
	.vertex_data_valid(clock_verticies_flag),
	.vertex_data_full(),
	.vertex_data_empty(vertex_data_fifo_empty),
	.vertex_data_clock(clock_50),
	 
	.pixel_data(rasterised_pixel_data),
   .pixel_data_valid(pixel_data_valid),
	.pixel_fifo_full()
);

rush3d_controller controller
(
	.clock(clock_50),
	.reset_n(keys[0]),
	
	.control_status_in(control_status_out),
	.control_status_out(control_status_in),
	.control_status_load(control_status_load_fpga),
	
	.fill_background_flag(fill_background_flag),
	.clock_verticies_flag(clock_verticies_flag),
	.current_buffer_flag(current_buffer),
	
	.framebuffer_write_state(framebuffer_write_state),
	
	.pixel_fifo_empty(pixel_fifo_empty),
	.vertex_data_fifo_empty(vertex_data_fifo_empty),
	.vsync(~sync)
);

framebuffer_read reader
(
	.clock(clock_50),
	.reset_n(keys[0]),
	
	.address(sdram0_address),
	.burstcount(sdram0_burstcount),
	.waitrequest(sdram0_waitrequest),
	.readdata(sdram0_readdata),
	.readdatavalid(sdram0_readdatavalid),
	.read(sdram0_read),
	
	.buffer(current_buffer),
	.pixel(pixel_data),
	.pixel_clock(pixel_clock),
	.pixel_valid(display_active),
	.sync(~sync)
);


hsbridge_pll hsbridge_pll
(
	.refclk(clock_50), // 50MHz input
	.rst(1'b0),
	.outclk_0(hsbridge_clock) // 133MHz output
);


endmodule
