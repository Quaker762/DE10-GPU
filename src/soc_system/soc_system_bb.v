
module soc_system (
	clk_clk,
	hps_0_f2h_sdram0_data_address,
	hps_0_f2h_sdram0_data_burstcount,
	hps_0_f2h_sdram0_data_waitrequest,
	hps_0_f2h_sdram0_data_readdata,
	hps_0_f2h_sdram0_data_readdatavalid,
	hps_0_f2h_sdram0_data_read,
	hps_0_f2h_sdram0_data_writedata,
	hps_0_f2h_sdram0_data_byteenable,
	hps_0_f2h_sdram0_data_write,
	hps_0_f2h_sdram1_data_address,
	hps_0_f2h_sdram1_data_burstcount,
	hps_0_f2h_sdram1_data_waitrequest,
	hps_0_f2h_sdram1_data_writedata,
	hps_0_f2h_sdram1_data_byteenable,
	hps_0_f2h_sdram1_data_write,
	hps_0_f2h_sdram2_data_address,
	hps_0_f2h_sdram2_data_burstcount,
	hps_0_f2h_sdram2_data_waitrequest,
	hps_0_f2h_sdram2_data_readdata,
	hps_0_f2h_sdram2_data_readdatavalid,
	hps_0_f2h_sdram2_data_read,
	hps_0_h2f_lw_axi_master_awid,
	hps_0_h2f_lw_axi_master_awaddr,
	hps_0_h2f_lw_axi_master_awlen,
	hps_0_h2f_lw_axi_master_awsize,
	hps_0_h2f_lw_axi_master_awburst,
	hps_0_h2f_lw_axi_master_awlock,
	hps_0_h2f_lw_axi_master_awcache,
	hps_0_h2f_lw_axi_master_awprot,
	hps_0_h2f_lw_axi_master_awvalid,
	hps_0_h2f_lw_axi_master_awready,
	hps_0_h2f_lw_axi_master_wid,
	hps_0_h2f_lw_axi_master_wdata,
	hps_0_h2f_lw_axi_master_wstrb,
	hps_0_h2f_lw_axi_master_wlast,
	hps_0_h2f_lw_axi_master_wvalid,
	hps_0_h2f_lw_axi_master_wready,
	hps_0_h2f_lw_axi_master_bid,
	hps_0_h2f_lw_axi_master_bresp,
	hps_0_h2f_lw_axi_master_bvalid,
	hps_0_h2f_lw_axi_master_bready,
	hps_0_h2f_lw_axi_master_arid,
	hps_0_h2f_lw_axi_master_araddr,
	hps_0_h2f_lw_axi_master_arlen,
	hps_0_h2f_lw_axi_master_arsize,
	hps_0_h2f_lw_axi_master_arburst,
	hps_0_h2f_lw_axi_master_arlock,
	hps_0_h2f_lw_axi_master_arcache,
	hps_0_h2f_lw_axi_master_arprot,
	hps_0_h2f_lw_axi_master_arvalid,
	hps_0_h2f_lw_axi_master_arready,
	hps_0_h2f_lw_axi_master_rid,
	hps_0_h2f_lw_axi_master_rdata,
	hps_0_h2f_lw_axi_master_rresp,
	hps_0_h2f_lw_axi_master_rlast,
	hps_0_h2f_lw_axi_master_rvalid,
	hps_0_h2f_lw_axi_master_rready,
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
	reset_reset_n,
	hps_0_h2f_reset_reset_n);	

	input		clk_clk;
	input	[28:0]	hps_0_f2h_sdram0_data_address;
	input	[7:0]	hps_0_f2h_sdram0_data_burstcount;
	output		hps_0_f2h_sdram0_data_waitrequest;
	output	[63:0]	hps_0_f2h_sdram0_data_readdata;
	output		hps_0_f2h_sdram0_data_readdatavalid;
	input		hps_0_f2h_sdram0_data_read;
	input	[63:0]	hps_0_f2h_sdram0_data_writedata;
	input	[7:0]	hps_0_f2h_sdram0_data_byteenable;
	input		hps_0_f2h_sdram0_data_write;
	input	[28:0]	hps_0_f2h_sdram1_data_address;
	input	[7:0]	hps_0_f2h_sdram1_data_burstcount;
	output		hps_0_f2h_sdram1_data_waitrequest;
	input	[63:0]	hps_0_f2h_sdram1_data_writedata;
	input	[7:0]	hps_0_f2h_sdram1_data_byteenable;
	input		hps_0_f2h_sdram1_data_write;
	input	[28:0]	hps_0_f2h_sdram2_data_address;
	input	[7:0]	hps_0_f2h_sdram2_data_burstcount;
	output		hps_0_f2h_sdram2_data_waitrequest;
	output	[63:0]	hps_0_f2h_sdram2_data_readdata;
	output		hps_0_f2h_sdram2_data_readdatavalid;
	input		hps_0_f2h_sdram2_data_read;
	output	[11:0]	hps_0_h2f_lw_axi_master_awid;
	output	[20:0]	hps_0_h2f_lw_axi_master_awaddr;
	output	[3:0]	hps_0_h2f_lw_axi_master_awlen;
	output	[2:0]	hps_0_h2f_lw_axi_master_awsize;
	output	[1:0]	hps_0_h2f_lw_axi_master_awburst;
	output	[1:0]	hps_0_h2f_lw_axi_master_awlock;
	output	[3:0]	hps_0_h2f_lw_axi_master_awcache;
	output	[2:0]	hps_0_h2f_lw_axi_master_awprot;
	output		hps_0_h2f_lw_axi_master_awvalid;
	input		hps_0_h2f_lw_axi_master_awready;
	output	[11:0]	hps_0_h2f_lw_axi_master_wid;
	output	[31:0]	hps_0_h2f_lw_axi_master_wdata;
	output	[3:0]	hps_0_h2f_lw_axi_master_wstrb;
	output		hps_0_h2f_lw_axi_master_wlast;
	output		hps_0_h2f_lw_axi_master_wvalid;
	input		hps_0_h2f_lw_axi_master_wready;
	input	[11:0]	hps_0_h2f_lw_axi_master_bid;
	input	[1:0]	hps_0_h2f_lw_axi_master_bresp;
	input		hps_0_h2f_lw_axi_master_bvalid;
	output		hps_0_h2f_lw_axi_master_bready;
	output	[11:0]	hps_0_h2f_lw_axi_master_arid;
	output	[20:0]	hps_0_h2f_lw_axi_master_araddr;
	output	[3:0]	hps_0_h2f_lw_axi_master_arlen;
	output	[2:0]	hps_0_h2f_lw_axi_master_arsize;
	output	[1:0]	hps_0_h2f_lw_axi_master_arburst;
	output	[1:0]	hps_0_h2f_lw_axi_master_arlock;
	output	[3:0]	hps_0_h2f_lw_axi_master_arcache;
	output	[2:0]	hps_0_h2f_lw_axi_master_arprot;
	output		hps_0_h2f_lw_axi_master_arvalid;
	input		hps_0_h2f_lw_axi_master_arready;
	input	[11:0]	hps_0_h2f_lw_axi_master_rid;
	input	[31:0]	hps_0_h2f_lw_axi_master_rdata;
	input	[1:0]	hps_0_h2f_lw_axi_master_rresp;
	input		hps_0_h2f_lw_axi_master_rlast;
	input		hps_0_h2f_lw_axi_master_rvalid;
	output		hps_0_h2f_lw_axi_master_rready;
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
	input		reset_reset_n;
	output		hps_0_h2f_reset_reset_n;
endmodule
