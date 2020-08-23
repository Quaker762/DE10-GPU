	soc_system u0 (
		.clk_clk                             (<connected-to-clk_clk>),                             //                         clk.clk
		.hps_0_f2h_sdram0_data_address       (<connected-to-hps_0_f2h_sdram0_data_address>),       //       hps_0_f2h_sdram0_data.address
		.hps_0_f2h_sdram0_data_burstcount    (<connected-to-hps_0_f2h_sdram0_data_burstcount>),    //                            .burstcount
		.hps_0_f2h_sdram0_data_waitrequest   (<connected-to-hps_0_f2h_sdram0_data_waitrequest>),   //                            .waitrequest
		.hps_0_f2h_sdram0_data_readdata      (<connected-to-hps_0_f2h_sdram0_data_readdata>),      //                            .readdata
		.hps_0_f2h_sdram0_data_readdatavalid (<connected-to-hps_0_f2h_sdram0_data_readdatavalid>), //                            .readdatavalid
		.hps_0_f2h_sdram0_data_read          (<connected-to-hps_0_f2h_sdram0_data_read>),          //                            .read
		.hps_0_h2f_reset_reset_n             (<connected-to-hps_0_h2f_reset_reset_n>),             //             hps_0_h2f_reset.reset_n
		.hps_0_i2c1_out_data                 (<connected-to-hps_0_i2c1_out_data>),                 //                  hps_0_i2c1.out_data
		.hps_0_i2c1_sda                      (<connected-to-hps_0_i2c1_sda>),                      //                            .sda
		.hps_0_i2c1_clk_clk                  (<connected-to-hps_0_i2c1_clk_clk>),                  //              hps_0_i2c1_clk.clk
		.hps_0_i2c1_scl_in_clk               (<connected-to-hps_0_i2c1_scl_in_clk>),               //           hps_0_i2c1_scl_in.clk
		.memory_mem_a                        (<connected-to-memory_mem_a>),                        //                      memory.mem_a
		.memory_mem_ba                       (<connected-to-memory_mem_ba>),                       //                            .mem_ba
		.memory_mem_ck                       (<connected-to-memory_mem_ck>),                       //                            .mem_ck
		.memory_mem_ck_n                     (<connected-to-memory_mem_ck_n>),                     //                            .mem_ck_n
		.memory_mem_cke                      (<connected-to-memory_mem_cke>),                      //                            .mem_cke
		.memory_mem_cs_n                     (<connected-to-memory_mem_cs_n>),                     //                            .mem_cs_n
		.memory_mem_ras_n                    (<connected-to-memory_mem_ras_n>),                    //                            .mem_ras_n
		.memory_mem_cas_n                    (<connected-to-memory_mem_cas_n>),                    //                            .mem_cas_n
		.memory_mem_we_n                     (<connected-to-memory_mem_we_n>),                     //                            .mem_we_n
		.memory_mem_reset_n                  (<connected-to-memory_mem_reset_n>),                  //                            .mem_reset_n
		.memory_mem_dq                       (<connected-to-memory_mem_dq>),                       //                            .mem_dq
		.memory_mem_dqs                      (<connected-to-memory_mem_dqs>),                      //                            .mem_dqs
		.memory_mem_dqs_n                    (<connected-to-memory_mem_dqs_n>),                    //                            .mem_dqs_n
		.memory_mem_odt                      (<connected-to-memory_mem_odt>),                      //                            .mem_odt
		.memory_mem_dm                       (<connected-to-memory_mem_dm>),                       //                            .mem_dm
		.memory_oct_rzqin                    (<connected-to-memory_oct_rzqin>),                    //                            .oct_rzqin
		.reset_reset_n                       (<connected-to-reset_reset_n>),                       //                       reset.reset_n
		.register_file_0_conduit_end_c_out   (<connected-to-register_file_0_conduit_end_c_out>),   // register_file_0_conduit_end.c_out
		.register_file_0_conduit_end_b_out   (<connected-to-register_file_0_conduit_end_b_out>),   //                            .b_out
		.register_file_0_conduit_end_a_out   (<connected-to-register_file_0_conduit_end_a_out>)    //                            .a_out
	);

