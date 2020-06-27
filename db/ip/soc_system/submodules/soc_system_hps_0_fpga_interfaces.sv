// (C) 2001-2018 Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License Subscription 
// Agreement, Intel FPGA IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Intel and sold by 
// Intel or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


module soc_system_hps_0_fpga_interfaces(
// h2f_reset
  output wire [1 - 1 : 0 ] h2f_rst_n
// f2h_sdram0_data
 ,input wire [29 - 1 : 0 ] f2h_sdram0_ADDRESS
 ,input wire [8 - 1 : 0 ] f2h_sdram0_BURSTCOUNT
 ,output wire [1 - 1 : 0 ] f2h_sdram0_WAITREQUEST
 ,output wire [64 - 1 : 0 ] f2h_sdram0_READDATA
 ,output wire [1 - 1 : 0 ] f2h_sdram0_READDATAVALID
 ,input wire [1 - 1 : 0 ] f2h_sdram0_READ
 ,input wire [64 - 1 : 0 ] f2h_sdram0_WRITEDATA
 ,input wire [8 - 1 : 0 ] f2h_sdram0_BYTEENABLE
 ,input wire [1 - 1 : 0 ] f2h_sdram0_WRITE
// f2h_sdram0_clock
 ,input wire [1 - 1 : 0 ] f2h_sdram0_clk
// f2h_sdram1_data
 ,input wire [29 - 1 : 0 ] f2h_sdram1_ADDRESS
 ,input wire [8 - 1 : 0 ] f2h_sdram1_BURSTCOUNT
 ,output wire [1 - 1 : 0 ] f2h_sdram1_WAITREQUEST
 ,input wire [64 - 1 : 0 ] f2h_sdram1_WRITEDATA
 ,input wire [8 - 1 : 0 ] f2h_sdram1_BYTEENABLE
 ,input wire [1 - 1 : 0 ] f2h_sdram1_WRITE
// f2h_sdram1_clock
 ,input wire [1 - 1 : 0 ] f2h_sdram1_clk
// f2h_sdram2_data
 ,input wire [29 - 1 : 0 ] f2h_sdram2_ADDRESS
 ,input wire [8 - 1 : 0 ] f2h_sdram2_BURSTCOUNT
 ,output wire [1 - 1 : 0 ] f2h_sdram2_WAITREQUEST
 ,output wire [64 - 1 : 0 ] f2h_sdram2_READDATA
 ,output wire [1 - 1 : 0 ] f2h_sdram2_READDATAVALID
 ,input wire [1 - 1 : 0 ] f2h_sdram2_READ
// f2h_sdram2_clock
 ,input wire [1 - 1 : 0 ] f2h_sdram2_clk
// i2c1_scl_in
 ,input wire [1 - 1 : 0 ] i2c1_scl
// i2c1_clk
 ,output wire [1 - 1 : 0 ] i2c1_out_clk
// i2c1
 ,output wire [1 - 1 : 0 ] i2c1_out_data
 ,input wire [1 - 1 : 0 ] i2c1_sda
);


wire [23 - 1 : 0] intermediate;
assign intermediate[0:0] = ~intermediate[1:1];
assign intermediate[6:6] = intermediate[3:3]|intermediate[5:5];
assign intermediate[2:2] = intermediate[7:7];
assign intermediate[4:4] = intermediate[7:7];
assign intermediate[8:8] = intermediate[7:7];
assign intermediate[9:9] = ~intermediate[10:10];
assign intermediate[13:13] = intermediate[12:12];
assign intermediate[11:11] = intermediate[14:14];
assign intermediate[15:15] = intermediate[14:14];
assign intermediate[16:16] = ~intermediate[17:17];
assign intermediate[20:20] = intermediate[19:19];
assign intermediate[18:18] = intermediate[21:21];
assign intermediate[22:22] = intermediate[21:21];
assign f2h_sdram0_WAITREQUEST[0:0] = intermediate[0:0];
assign f2h_sdram1_WAITREQUEST[0:0] = intermediate[9:9];
assign f2h_sdram2_WAITREQUEST[0:0] = intermediate[16:16];
assign intermediate[3:3] = f2h_sdram0_READ[0:0];
assign intermediate[5:5] = f2h_sdram0_WRITE[0:0];
assign intermediate[7:7] = f2h_sdram0_clk[0:0];
assign intermediate[12:12] = f2h_sdram1_WRITE[0:0];
assign intermediate[14:14] = f2h_sdram1_clk[0:0];
assign intermediate[19:19] = f2h_sdram2_READ[0:0];
assign intermediate[21:21] = f2h_sdram2_clk[0:0];

cyclonev_hps_interface_clocks_resets clocks_resets(
 .f2h_pending_rst_ack({
    1'b1 // 0:0
  })
,.f2h_warm_rst_req_n({
    1'b1 // 0:0
  })
,.f2h_dbg_rst_req_n({
    1'b1 // 0:0
  })
,.h2f_rst_n({
    h2f_rst_n[0:0] // 0:0
  })
,.f2h_cold_rst_req_n({
    1'b1 // 0:0
  })
);


cyclonev_hps_interface_dbg_apb debug_apb(
 .DBG_APB_DISABLE({
    1'b0 // 0:0
  })
,.P_CLK_EN({
    1'b0 // 0:0
  })
);


cyclonev_hps_interface_tpiu_trace tpiu(
 .traceclk_ctl({
    1'b1 // 0:0
  })
);


cyclonev_hps_interface_boot_from_fpga boot_from_fpga(
 .boot_from_fpga_ready({
    1'b0 // 0:0
  })
,.boot_from_fpga_on_failure({
    1'b0 // 0:0
  })
,.bsel_en({
    1'b0 // 0:0
  })
,.csel_en({
    1'b0 // 0:0
  })
,.csel({
    2'b01 // 1:0
  })
,.bsel({
    3'b001 // 2:0
  })
);


cyclonev_hps_interface_fpga2hps fpga2hps(
 .port_size_config({
    2'b11 // 1:0
  })
);


cyclonev_hps_interface_hps2fpga hps2fpga(
 .port_size_config({
    2'b11 // 1:0
  })
);


cyclonev_hps_interface_fpga2sdram f2sdram(
 .cmd_data_2({
    18'b000000000000000000 // 59:42
   ,f2h_sdram2_BURSTCOUNT[7:0] // 41:34
   ,3'b000 // 33:31
   ,f2h_sdram2_ADDRESS[28:0] // 30:2
   ,1'b0 // 1:1
   ,intermediate[19:19] // 0:0
  })
,.cmd_data_1({
    18'b000000000000000000 // 59:42
   ,f2h_sdram1_BURSTCOUNT[7:0] // 41:34
   ,3'b000 // 33:31
   ,f2h_sdram1_ADDRESS[28:0] // 30:2
   ,intermediate[12:12] // 1:1
   ,1'b0 // 0:0
  })
,.cmd_data_0({
    18'b000000000000000000 // 59:42
   ,f2h_sdram0_BURSTCOUNT[7:0] // 41:34
   ,3'b000 // 33:31
   ,f2h_sdram0_ADDRESS[28:0] // 30:2
   ,intermediate[5:5] // 1:1
   ,intermediate[3:3] // 0:0
  })
,.cfg_port_width({
    12'b000000010101 // 11:0
  })
,.rd_valid_1({
    f2h_sdram2_READDATAVALID[0:0] // 0:0
  })
,.rd_valid_0({
    f2h_sdram0_READDATAVALID[0:0] // 0:0
  })
,.wr_clk_1({
    intermediate[11:11] // 0:0
  })
,.wr_clk_0({
    intermediate[4:4] // 0:0
  })
,.wr_data_1({
    2'b00 // 89:88
   ,f2h_sdram1_BYTEENABLE[7:0] // 87:80
   ,16'b0000000000000000 // 79:64
   ,f2h_sdram1_WRITEDATA[63:0] // 63:0
  })
,.cfg_cport_type({
    12'b000000100111 // 11:0
  })
,.wr_data_0({
    2'b00 // 89:88
   ,f2h_sdram0_BYTEENABLE[7:0] // 87:80
   ,16'b0000000000000000 // 79:64
   ,f2h_sdram0_WRITEDATA[63:0] // 63:0
  })
,.cfg_rfifo_cport_map({
    16'b0000000000100000 // 15:0
  })
,.cmd_port_clk_2({
    intermediate[22:22] // 0:0
  })
,.cfg_cport_wfifo_map({
    18'b000000000000001000 // 17:0
  })
,.cmd_port_clk_1({
    intermediate[15:15] // 0:0
  })
,.cmd_port_clk_0({
    intermediate[8:8] // 0:0
  })
,.cfg_cport_rfifo_map({
    18'b000000000001000000 // 17:0
  })
,.rd_ready_1({
    1'b1 // 0:0
  })
,.rd_ready_0({
    1'b1 // 0:0
  })
,.cmd_ready_2({
    intermediate[17:17] // 0:0
  })
,.rd_clk_1({
    intermediate[18:18] // 0:0
  })
,.cmd_ready_1({
    intermediate[10:10] // 0:0
  })
,.rd_clk_0({
    intermediate[2:2] // 0:0
  })
,.cmd_ready_0({
    intermediate[1:1] // 0:0
  })
,.cfg_wfifo_cport_map({
    16'b0000000000010000 // 15:0
  })
,.wrack_ready_1({
    1'b1 // 0:0
  })
,.cmd_valid_2({
    intermediate[20:20] // 0:0
  })
,.wrack_ready_0({
    1'b1 // 0:0
  })
,.cmd_valid_1({
    intermediate[13:13] // 0:0
  })
,.cmd_valid_0({
    intermediate[6:6] // 0:0
  })
,.rd_data_1({
    f2h_sdram2_READDATA[63:0] // 63:0
  })
,.rd_data_0({
    f2h_sdram0_READDATA[63:0] // 63:0
  })
,.cfg_axi_mm_select({
    6'b000000 // 5:0
  })
);


cyclonev_hps_interface_peripheral_i2c peripheral_i2c1(
 .out_clk({
    i2c1_out_clk[0:0] // 0:0
  })
,.scl({
    i2c1_scl[0:0] // 0:0
  })
,.sda({
    i2c1_sda[0:0] // 0:0
  })
,.out_data({
    i2c1_out_data[0:0] // 0:0
  })
);

endmodule

