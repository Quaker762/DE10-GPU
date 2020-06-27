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
			reset_reset_n                       : in    std_logic                     := 'X'              -- reset_n
		);
	end component soc_system;

	u0 : component soc_system
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                   clk.clk
			hps_0_f2h_sdram0_data_address       => CONNECTED_TO_hps_0_f2h_sdram0_data_address,       -- hps_0_f2h_sdram0_data.address
			hps_0_f2h_sdram0_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram0_data_burstcount,    --                      .burstcount
			hps_0_f2h_sdram0_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram0_data_waitrequest,   --                      .waitrequest
			hps_0_f2h_sdram0_data_readdata      => CONNECTED_TO_hps_0_f2h_sdram0_data_readdata,      --                      .readdata
			hps_0_f2h_sdram0_data_readdatavalid => CONNECTED_TO_hps_0_f2h_sdram0_data_readdatavalid, --                      .readdatavalid
			hps_0_f2h_sdram0_data_read          => CONNECTED_TO_hps_0_f2h_sdram0_data_read,          --                      .read
			hps_0_f2h_sdram0_data_writedata     => CONNECTED_TO_hps_0_f2h_sdram0_data_writedata,     --                      .writedata
			hps_0_f2h_sdram0_data_byteenable    => CONNECTED_TO_hps_0_f2h_sdram0_data_byteenable,    --                      .byteenable
			hps_0_f2h_sdram0_data_write         => CONNECTED_TO_hps_0_f2h_sdram0_data_write,         --                      .write
			hps_0_f2h_sdram1_data_address       => CONNECTED_TO_hps_0_f2h_sdram1_data_address,       -- hps_0_f2h_sdram1_data.address
			hps_0_f2h_sdram1_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram1_data_burstcount,    --                      .burstcount
			hps_0_f2h_sdram1_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram1_data_waitrequest,   --                      .waitrequest
			hps_0_f2h_sdram1_data_writedata     => CONNECTED_TO_hps_0_f2h_sdram1_data_writedata,     --                      .writedata
			hps_0_f2h_sdram1_data_byteenable    => CONNECTED_TO_hps_0_f2h_sdram1_data_byteenable,    --                      .byteenable
			hps_0_f2h_sdram1_data_write         => CONNECTED_TO_hps_0_f2h_sdram1_data_write,         --                      .write
			hps_0_f2h_sdram2_data_address       => CONNECTED_TO_hps_0_f2h_sdram2_data_address,       -- hps_0_f2h_sdram2_data.address
			hps_0_f2h_sdram2_data_burstcount    => CONNECTED_TO_hps_0_f2h_sdram2_data_burstcount,    --                      .burstcount
			hps_0_f2h_sdram2_data_waitrequest   => CONNECTED_TO_hps_0_f2h_sdram2_data_waitrequest,   --                      .waitrequest
			hps_0_f2h_sdram2_data_readdata      => CONNECTED_TO_hps_0_f2h_sdram2_data_readdata,      --                      .readdata
			hps_0_f2h_sdram2_data_readdatavalid => CONNECTED_TO_hps_0_f2h_sdram2_data_readdatavalid, --                      .readdatavalid
			hps_0_f2h_sdram2_data_read          => CONNECTED_TO_hps_0_f2h_sdram2_data_read,          --                      .read
			hps_0_i2c1_out_data                 => CONNECTED_TO_hps_0_i2c1_out_data,                 --            hps_0_i2c1.out_data
			hps_0_i2c1_sda                      => CONNECTED_TO_hps_0_i2c1_sda,                      --                      .sda
			hps_0_i2c1_clk_clk                  => CONNECTED_TO_hps_0_i2c1_clk_clk,                  --        hps_0_i2c1_clk.clk
			hps_0_i2c1_scl_in_clk               => CONNECTED_TO_hps_0_i2c1_scl_in_clk,               --     hps_0_i2c1_scl_in.clk
			memory_mem_a                        => CONNECTED_TO_memory_mem_a,                        --                memory.mem_a
			memory_mem_ba                       => CONNECTED_TO_memory_mem_ba,                       --                      .mem_ba
			memory_mem_ck                       => CONNECTED_TO_memory_mem_ck,                       --                      .mem_ck
			memory_mem_ck_n                     => CONNECTED_TO_memory_mem_ck_n,                     --                      .mem_ck_n
			memory_mem_cke                      => CONNECTED_TO_memory_mem_cke,                      --                      .mem_cke
			memory_mem_cs_n                     => CONNECTED_TO_memory_mem_cs_n,                     --                      .mem_cs_n
			memory_mem_ras_n                    => CONNECTED_TO_memory_mem_ras_n,                    --                      .mem_ras_n
			memory_mem_cas_n                    => CONNECTED_TO_memory_mem_cas_n,                    --                      .mem_cas_n
			memory_mem_we_n                     => CONNECTED_TO_memory_mem_we_n,                     --                      .mem_we_n
			memory_mem_reset_n                  => CONNECTED_TO_memory_mem_reset_n,                  --                      .mem_reset_n
			memory_mem_dq                       => CONNECTED_TO_memory_mem_dq,                       --                      .mem_dq
			memory_mem_dqs                      => CONNECTED_TO_memory_mem_dqs,                      --                      .mem_dqs
			memory_mem_dqs_n                    => CONNECTED_TO_memory_mem_dqs_n,                    --                      .mem_dqs_n
			memory_mem_odt                      => CONNECTED_TO_memory_mem_odt,                      --                      .mem_odt
			memory_mem_dm                       => CONNECTED_TO_memory_mem_dm,                       --                      .mem_dm
			memory_oct_rzqin                    => CONNECTED_TO_memory_oct_rzqin,                    --                      .oct_rzqin
			reset_reset_n                       => CONNECTED_TO_reset_reset_n                        --                 reset.reset_n
		);

