	component soc_system is
		port (
			clk_clk                             : in    std_logic                     := 'X';             -- clk
			hps_0_f2h_sdram0_data_address       : in    std_logic_vector(28 downto 0) := (others => 'X'); -- address
			hps_0_f2h_sdram0_data_burstcount    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- burstcount
			hps_0_f2h_sdram0_data_waitrequest   : out   std_logic;                                        -- waitrequest
			hps_0_f2h_sdram0_data_readdata      : out   std_logic_vector(63 downto 0);                    -- readdata
			hps_0_f2h_sdram0_data_readdatavalid : out   std_logic;                                        -- readdatavalid
			hps_0_f2h_sdram0_data_read          : in    std_logic                     := 'X';             -- read
			hps_0_f2h_sdram0_data_writedata     : in    std_logic_vector(63 downto 0) := (others => 'X'); -- writedata
			hps_0_f2h_sdram0_data_byteenable    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- byteenable
			hps_0_f2h_sdram0_data_write         : in    std_logic                     := 'X';             -- write
			hps_0_f2h_sdram1_data_address       : in    std_logic_vector(28 downto 0) := (others => 'X'); -- address
			hps_0_f2h_sdram1_data_burstcount    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- burstcount
			hps_0_f2h_sdram1_data_waitrequest   : out   std_logic;                                        -- waitrequest
			hps_0_f2h_sdram1_data_writedata     : in    std_logic_vector(63 downto 0) := (others => 'X'); -- writedata
			hps_0_f2h_sdram1_data_byteenable    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- byteenable
			hps_0_f2h_sdram1_data_write         : in    std_logic                     := 'X';             -- write
			hps_0_f2h_sdram2_data_address       : in    std_logic_vector(28 downto 0) := (others => 'X'); -- address
			hps_0_f2h_sdram2_data_burstcount    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- burstcount
			hps_0_f2h_sdram2_data_waitrequest   : out   std_logic;                                        -- waitrequest
			hps_0_f2h_sdram2_data_readdata      : out   std_logic_vector(63 downto 0);                    -- readdata
			hps_0_f2h_sdram2_data_readdatavalid : out   std_logic;                                        -- readdatavalid
			hps_0_f2h_sdram2_data_read          : in    std_logic                     := 'X';             -- read
			hps_0_h2f_lw_axi_master_awid        : out   std_logic_vector(11 downto 0);                    -- awid
			hps_0_h2f_lw_axi_master_awaddr      : out   std_logic_vector(20 downto 0);                    -- awaddr
			hps_0_h2f_lw_axi_master_awlen       : out   std_logic_vector(3 downto 0);                     -- awlen
			hps_0_h2f_lw_axi_master_awsize      : out   std_logic_vector(2 downto 0);                     -- awsize
			hps_0_h2f_lw_axi_master_awburst     : out   std_logic_vector(1 downto 0);                     -- awburst
			hps_0_h2f_lw_axi_master_awlock      : out   std_logic_vector(1 downto 0);                     -- awlock
			hps_0_h2f_lw_axi_master_awcache     : out   std_logic_vector(3 downto 0);                     -- awcache
			hps_0_h2f_lw_axi_master_awprot      : out   std_logic_vector(2 downto 0);                     -- awprot
			hps_0_h2f_lw_axi_master_awvalid     : out   std_logic;                                        -- awvalid
			hps_0_h2f_lw_axi_master_awready     : in    std_logic                     := 'X';             -- awready
			hps_0_h2f_lw_axi_master_wid         : out   std_logic_vector(11 downto 0);                    -- wid
			hps_0_h2f_lw_axi_master_wdata       : out   std_logic_vector(31 downto 0);                    -- wdata
			hps_0_h2f_lw_axi_master_wstrb       : out   std_logic_vector(3 downto 0);                     -- wstrb
			hps_0_h2f_lw_axi_master_wlast       : out   std_logic;                                        -- wlast
			hps_0_h2f_lw_axi_master_wvalid      : out   std_logic;                                        -- wvalid
			hps_0_h2f_lw_axi_master_wready      : in    std_logic                     := 'X';             -- wready
			hps_0_h2f_lw_axi_master_bid         : in    std_logic_vector(11 downto 0) := (others => 'X'); -- bid
			hps_0_h2f_lw_axi_master_bresp       : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- bresp
			hps_0_h2f_lw_axi_master_bvalid      : in    std_logic                     := 'X';             -- bvalid
			hps_0_h2f_lw_axi_master_bready      : out   std_logic;                                        -- bready
			hps_0_h2f_lw_axi_master_arid        : out   std_logic_vector(11 downto 0);                    -- arid
			hps_0_h2f_lw_axi_master_araddr      : out   std_logic_vector(20 downto 0);                    -- araddr
			hps_0_h2f_lw_axi_master_arlen       : out   std_logic_vector(3 downto 0);                     -- arlen
			hps_0_h2f_lw_axi_master_arsize      : out   std_logic_vector(2 downto 0);                     -- arsize
			hps_0_h2f_lw_axi_master_arburst     : out   std_logic_vector(1 downto 0);                     -- arburst
			hps_0_h2f_lw_axi_master_arlock      : out   std_logic_vector(1 downto 0);                     -- arlock
			hps_0_h2f_lw_axi_master_arcache     : out   std_logic_vector(3 downto 0);                     -- arcache
			hps_0_h2f_lw_axi_master_arprot      : out   std_logic_vector(2 downto 0);                     -- arprot
			hps_0_h2f_lw_axi_master_arvalid     : out   std_logic;                                        -- arvalid
			hps_0_h2f_lw_axi_master_arready     : in    std_logic                     := 'X';             -- arready
			hps_0_h2f_lw_axi_master_rid         : in    std_logic_vector(11 downto 0) := (others => 'X'); -- rid
			hps_0_h2f_lw_axi_master_rdata       : in    std_logic_vector(31 downto 0) := (others => 'X'); -- rdata
			hps_0_h2f_lw_axi_master_rresp       : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- rresp
			hps_0_h2f_lw_axi_master_rlast       : in    std_logic                     := 'X';             -- rlast
			hps_0_h2f_lw_axi_master_rvalid      : in    std_logic                     := 'X';             -- rvalid
			hps_0_h2f_lw_axi_master_rready      : out   std_logic;                                        -- rready
			hps_0_i2c1_out_data                 : out   std_logic;                                        -- out_data
			hps_0_i2c1_sda                      : in    std_logic                     := 'X';             -- sda
			hps_0_i2c1_clk_clk                  : out   std_logic;                                        -- clk
			hps_0_i2c1_scl_in_clk               : in    std_logic                     := 'X';             -- clk
			memory_mem_a                        : out   std_logic_vector(14 downto 0);                    -- mem_a
			memory_mem_ba                       : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck                       : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n                     : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke                      : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n                     : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n                    : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n                    : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n                     : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n                  : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq                       : inout std_logic_vector(31 downto 0) := (others => 'X'); -- mem_dq
			memory_mem_dqs                      : inout std_logic_vector(3 downto 0)  := (others => 'X'); -- mem_dqs
			memory_mem_dqs_n                    : inout std_logic_vector(3 downto 0)  := (others => 'X'); -- mem_dqs_n
			memory_mem_odt                      : out   std_logic;                                        -- mem_odt
			memory_mem_dm                       : out   std_logic_vector(3 downto 0);                     -- mem_dm
			memory_oct_rzqin                    : in    std_logic                     := 'X';             -- oct_rzqin
			reset_reset_n                       : in    std_logic                     := 'X';             -- reset_n
			hps_0_h2f_reset_reset_n             : out   std_logic                                         -- reset_n
		);
	end component soc_system;

	u0 : component soc_system
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                     clk.clk
			hps_0_f2h_sdram0_data_address       => CONNECTED_TO_hps_0_f2h_sdram0_data_address,       --   hps_0_f2h_sdram0_data.address
			hps_0_f2h_sdram0_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram0_data_burstcount,    --                        .burstcount
			hps_0_f2h_sdram0_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram0_data_waitrequest,   --                        .waitrequest
			hps_0_f2h_sdram0_data_readdata      => CONNECTED_TO_hps_0_f2h_sdram0_data_readdata,      --                        .readdata
			hps_0_f2h_sdram0_data_readdatavalid => CONNECTED_TO_hps_0_f2h_sdram0_data_readdatavalid, --                        .readdatavalid
			hps_0_f2h_sdram0_data_read          => CONNECTED_TO_hps_0_f2h_sdram0_data_read,          --                        .read
			hps_0_f2h_sdram0_data_writedata     => CONNECTED_TO_hps_0_f2h_sdram0_data_writedata,     --                        .writedata
			hps_0_f2h_sdram0_data_byteenable    => CONNECTED_TO_hps_0_f2h_sdram0_data_byteenable,    --                        .byteenable
			hps_0_f2h_sdram0_data_write         => CONNECTED_TO_hps_0_f2h_sdram0_data_write,         --                        .write
			hps_0_f2h_sdram1_data_address       => CONNECTED_TO_hps_0_f2h_sdram1_data_address,       --   hps_0_f2h_sdram1_data.address
			hps_0_f2h_sdram1_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram1_data_burstcount,    --                        .burstcount
			hps_0_f2h_sdram1_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram1_data_waitrequest,   --                        .waitrequest
			hps_0_f2h_sdram1_data_writedata     => CONNECTED_TO_hps_0_f2h_sdram1_data_writedata,     --                        .writedata
			hps_0_f2h_sdram1_data_byteenable    => CONNECTED_TO_hps_0_f2h_sdram1_data_byteenable,    --                        .byteenable
			hps_0_f2h_sdram1_data_write         => CONNECTED_TO_hps_0_f2h_sdram1_data_write,         --                        .write
			hps_0_f2h_sdram2_data_address       => CONNECTED_TO_hps_0_f2h_sdram2_data_address,       --   hps_0_f2h_sdram2_data.address
			hps_0_f2h_sdram2_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram2_data_burstcount,    --                        .burstcount
			hps_0_f2h_sdram2_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram2_data_waitrequest,   --                        .waitrequest
			hps_0_f2h_sdram2_data_readdata      => CONNECTED_TO_hps_0_f2h_sdram2_data_readdata,      --                        .readdata
			hps_0_f2h_sdram2_data_readdatavalid => CONNECTED_TO_hps_0_f2h_sdram2_data_readdatavalid, --                        .readdatavalid
			hps_0_f2h_sdram2_data_read          => CONNECTED_TO_hps_0_f2h_sdram2_data_read,          --                        .read
			hps_0_h2f_lw_axi_master_awid        => CONNECTED_TO_hps_0_h2f_lw_axi_master_awid,        -- hps_0_h2f_lw_axi_master.awid
			hps_0_h2f_lw_axi_master_awaddr      => CONNECTED_TO_hps_0_h2f_lw_axi_master_awaddr,      --                        .awaddr
			hps_0_h2f_lw_axi_master_awlen       => CONNECTED_TO_hps_0_h2f_lw_axi_master_awlen,       --                        .awlen
			hps_0_h2f_lw_axi_master_awsize      => CONNECTED_TO_hps_0_h2f_lw_axi_master_awsize,      --                        .awsize
			hps_0_h2f_lw_axi_master_awburst     => CONNECTED_TO_hps_0_h2f_lw_axi_master_awburst,     --                        .awburst
			hps_0_h2f_lw_axi_master_awlock      => CONNECTED_TO_hps_0_h2f_lw_axi_master_awlock,      --                        .awlock
			hps_0_h2f_lw_axi_master_awcache     => CONNECTED_TO_hps_0_h2f_lw_axi_master_awcache,     --                        .awcache
			hps_0_h2f_lw_axi_master_awprot      => CONNECTED_TO_hps_0_h2f_lw_axi_master_awprot,      --                        .awprot
			hps_0_h2f_lw_axi_master_awvalid     => CONNECTED_TO_hps_0_h2f_lw_axi_master_awvalid,     --                        .awvalid
			hps_0_h2f_lw_axi_master_awready     => CONNECTED_TO_hps_0_h2f_lw_axi_master_awready,     --                        .awready
			hps_0_h2f_lw_axi_master_wid         => CONNECTED_TO_hps_0_h2f_lw_axi_master_wid,         --                        .wid
			hps_0_h2f_lw_axi_master_wdata       => CONNECTED_TO_hps_0_h2f_lw_axi_master_wdata,       --                        .wdata
			hps_0_h2f_lw_axi_master_wstrb       => CONNECTED_TO_hps_0_h2f_lw_axi_master_wstrb,       --                        .wstrb
			hps_0_h2f_lw_axi_master_wlast       => CONNECTED_TO_hps_0_h2f_lw_axi_master_wlast,       --                        .wlast
			hps_0_h2f_lw_axi_master_wvalid      => CONNECTED_TO_hps_0_h2f_lw_axi_master_wvalid,      --                        .wvalid
			hps_0_h2f_lw_axi_master_wready      => CONNECTED_TO_hps_0_h2f_lw_axi_master_wready,      --                        .wready
			hps_0_h2f_lw_axi_master_bid         => CONNECTED_TO_hps_0_h2f_lw_axi_master_bid,         --                        .bid
			hps_0_h2f_lw_axi_master_bresp       => CONNECTED_TO_hps_0_h2f_lw_axi_master_bresp,       --                        .bresp
			hps_0_h2f_lw_axi_master_bvalid      => CONNECTED_TO_hps_0_h2f_lw_axi_master_bvalid,      --                        .bvalid
			hps_0_h2f_lw_axi_master_bready      => CONNECTED_TO_hps_0_h2f_lw_axi_master_bready,      --                        .bready
			hps_0_h2f_lw_axi_master_arid        => CONNECTED_TO_hps_0_h2f_lw_axi_master_arid,        --                        .arid
			hps_0_h2f_lw_axi_master_araddr      => CONNECTED_TO_hps_0_h2f_lw_axi_master_araddr,      --                        .araddr
			hps_0_h2f_lw_axi_master_arlen       => CONNECTED_TO_hps_0_h2f_lw_axi_master_arlen,       --                        .arlen
			hps_0_h2f_lw_axi_master_arsize      => CONNECTED_TO_hps_0_h2f_lw_axi_master_arsize,      --                        .arsize
			hps_0_h2f_lw_axi_master_arburst     => CONNECTED_TO_hps_0_h2f_lw_axi_master_arburst,     --                        .arburst
			hps_0_h2f_lw_axi_master_arlock      => CONNECTED_TO_hps_0_h2f_lw_axi_master_arlock,      --                        .arlock
			hps_0_h2f_lw_axi_master_arcache     => CONNECTED_TO_hps_0_h2f_lw_axi_master_arcache,     --                        .arcache
			hps_0_h2f_lw_axi_master_arprot      => CONNECTED_TO_hps_0_h2f_lw_axi_master_arprot,      --                        .arprot
			hps_0_h2f_lw_axi_master_arvalid     => CONNECTED_TO_hps_0_h2f_lw_axi_master_arvalid,     --                        .arvalid
			hps_0_h2f_lw_axi_master_arready     => CONNECTED_TO_hps_0_h2f_lw_axi_master_arready,     --                        .arready
			hps_0_h2f_lw_axi_master_rid         => CONNECTED_TO_hps_0_h2f_lw_axi_master_rid,         --                        .rid
			hps_0_h2f_lw_axi_master_rdata       => CONNECTED_TO_hps_0_h2f_lw_axi_master_rdata,       --                        .rdata
			hps_0_h2f_lw_axi_master_rresp       => CONNECTED_TO_hps_0_h2f_lw_axi_master_rresp,       --                        .rresp
			hps_0_h2f_lw_axi_master_rlast       => CONNECTED_TO_hps_0_h2f_lw_axi_master_rlast,       --                        .rlast
			hps_0_h2f_lw_axi_master_rvalid      => CONNECTED_TO_hps_0_h2f_lw_axi_master_rvalid,      --                        .rvalid
			hps_0_h2f_lw_axi_master_rready      => CONNECTED_TO_hps_0_h2f_lw_axi_master_rready,      --                        .rready
			hps_0_i2c1_out_data                 => CONNECTED_TO_hps_0_i2c1_out_data,                 --              hps_0_i2c1.out_data
			hps_0_i2c1_sda                      => CONNECTED_TO_hps_0_i2c1_sda,                      --                        .sda
			hps_0_i2c1_clk_clk                  => CONNECTED_TO_hps_0_i2c1_clk_clk,                  --          hps_0_i2c1_clk.clk
			hps_0_i2c1_scl_in_clk               => CONNECTED_TO_hps_0_i2c1_scl_in_clk,               --       hps_0_i2c1_scl_in.clk
			memory_mem_a                        => CONNECTED_TO_memory_mem_a,                        --                  memory.mem_a
			memory_mem_ba                       => CONNECTED_TO_memory_mem_ba,                       --                        .mem_ba
			memory_mem_ck                       => CONNECTED_TO_memory_mem_ck,                       --                        .mem_ck
			memory_mem_ck_n                     => CONNECTED_TO_memory_mem_ck_n,                     --                        .mem_ck_n
			memory_mem_cke                      => CONNECTED_TO_memory_mem_cke,                      --                        .mem_cke
			memory_mem_cs_n                     => CONNECTED_TO_memory_mem_cs_n,                     --                        .mem_cs_n
			memory_mem_ras_n                    => CONNECTED_TO_memory_mem_ras_n,                    --                        .mem_ras_n
			memory_mem_cas_n                    => CONNECTED_TO_memory_mem_cas_n,                    --                        .mem_cas_n
			memory_mem_we_n                     => CONNECTED_TO_memory_mem_we_n,                     --                        .mem_we_n
			memory_mem_reset_n                  => CONNECTED_TO_memory_mem_reset_n,                  --                        .mem_reset_n
			memory_mem_dq                       => CONNECTED_TO_memory_mem_dq,                       --                        .mem_dq
			memory_mem_dqs                      => CONNECTED_TO_memory_mem_dqs,                      --                        .mem_dqs
			memory_mem_dqs_n                    => CONNECTED_TO_memory_mem_dqs_n,                    --                        .mem_dqs_n
			memory_mem_odt                      => CONNECTED_TO_memory_mem_odt,                      --                        .mem_odt
			memory_mem_dm                       => CONNECTED_TO_memory_mem_dm,                       --                        .mem_dm
			memory_oct_rzqin                    => CONNECTED_TO_memory_oct_rzqin,                    --                        .oct_rzqin
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                   reset.reset_n
			hps_0_h2f_reset_reset_n             => CONNECTED_TO_hps_0_h2f_reset_reset_n              --         hps_0_h2f_reset.reset_n
		);

