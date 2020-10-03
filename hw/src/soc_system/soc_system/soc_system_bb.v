
module soc_system (
	clk_clk,
	hps_0_f2h_sdram0_data_address,
	hps_0_f2h_sdram0_data_burstcount,
	hps_0_f2h_sdram0_data_waitrequest,
	hps_0_f2h_sdram0_data_readdata,
	hps_0_f2h_sdram0_data_readdatavalid,
	hps_0_f2h_sdram0_data_read,
	hps_0_f2h_sdram1_data_address,
	hps_0_f2h_sdram1_data_burstcount,
	hps_0_f2h_sdram1_data_waitrequest,
	hps_0_f2h_sdram1_data_writedata,
	hps_0_f2h_sdram1_data_byteenable,
	hps_0_f2h_sdram1_data_write,
	hps_0_h2f_reset_reset_n,
	hps_0_i2c1_out_data,
	hps_0_i2c1_sda,
	hps_0_i2c1_clk_clk,
	hps_0_i2c1_scl_in_clk,
	memory_mem_a,
	memory_mem_ba,
	memory_mem_ck,
	memory_mem_ck_n,
	memory_mem_cke,
	memory_mem_cs_n,
	memory_mem_ras_n,
	memory_mem_cas_n,
	memory_mem_we_n,
	memory_mem_reset_n,
	memory_mem_dq,
	memory_mem_dqs,
	memory_mem_dqs_n,
	memory_mem_odt,
	memory_mem_dm,
	memory_oct_rzqin,
	register_file_0_conduit_end_export_vertex_c,
	register_file_0_conduit_end_export_vertex_a,
	register_file_0_conduit_end_export_vertex_b,
	register_file_0_conduit_end_export_control_status_out,
	register_file_0_conduit_end_export_back_colour_out,
	register_file_0_conduit_end_export_color_a_out,
	register_file_0_conduit_end_export_color_b_out,
	register_file_0_conduit_end_export_color_c_out,
	register_file_0_conduit_end_export_win_size_out,
	register_file_0_conduit_end_export_control_status_load_fpga,
	register_file_0_conduit_end_export_control_status_in,
	reset_reset_n);	

	input		clk_clk;
	input	[28:0]	hps_0_f2h_sdram0_data_address;
	input	[7:0]	hps_0_f2h_sdram0_data_burstcount;
	output		hps_0_f2h_sdram0_data_waitrequest;
	output	[63:0]	hps_0_f2h_sdram0_data_readdata;
	output		hps_0_f2h_sdram0_data_readdatavalid;
	input		hps_0_f2h_sdram0_data_read;
	input	[28:0]	hps_0_f2h_sdram1_data_address;
	input	[7:0]	hps_0_f2h_sdram1_data_burstcount;
	output		hps_0_f2h_sdram1_data_waitrequest;
	input	[63:0]	hps_0_f2h_sdram1_data_writedata;
	input	[7:0]	hps_0_f2h_sdram1_data_byteenable;
	input		hps_0_f2h_sdram1_data_write;
	output		hps_0_h2f_reset_reset_n;
	output		hps_0_i2c1_out_data;
	input		hps_0_i2c1_sda;
	output		hps_0_i2c1_clk_clk;
	input		hps_0_i2c1_scl_in_clk;
	output	[14:0]	memory_mem_a;
	output	[2:0]	memory_mem_ba;
	output		memory_mem_ck;
	output		memory_mem_ck_n;
	output		memory_mem_cke;
	output		memory_mem_cs_n;
	output		memory_mem_ras_n;
	output		memory_mem_cas_n;
	output		memory_mem_we_n;
	output		memory_mem_reset_n;
	inout	[31:0]	memory_mem_dq;
	inout	[3:0]	memory_mem_dqs;
	inout	[3:0]	memory_mem_dqs_n;
	output		memory_mem_odt;
	output	[3:0]	memory_mem_dm;
	input		memory_oct_rzqin;
	output	[63:0]	register_file_0_conduit_end_export_vertex_c;
	output	[63:0]	register_file_0_conduit_end_export_vertex_a;
	output	[63:0]	register_file_0_conduit_end_export_vertex_b;
	output	[63:0]	register_file_0_conduit_end_export_control_status_out;
	output	[63:0]	register_file_0_conduit_end_export_back_colour_out;
	output	[63:0]	register_file_0_conduit_end_export_color_a_out;
	output	[63:0]	register_file_0_conduit_end_export_color_b_out;
	output	[63:0]	register_file_0_conduit_end_export_color_c_out;
	output	[63:0]	register_file_0_conduit_end_export_win_size_out;
	input		register_file_0_conduit_end_export_control_status_load_fpga;
	input	[63:0]	register_file_0_conduit_end_export_control_status_in;
	input		reset_reset_n;
endmodule
