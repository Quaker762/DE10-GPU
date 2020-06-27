// I2c Module - Jack Allan
module I2C
(
	input clock,
	input reset_n,
	input start_n,
	inout sda_flag,
	output scl_flag,
	output stop_flag  
);

reg [5:0] table_count = 1'b0;	// Tracks which data is being pointed to
reg [5:0] clock_count = 1'b0; 
reg start_flag = 1'b0; // Start transmission
reg scl_flag_raw = 1'b1; // Serial clock flag
reg sda_flag_raw  = 1'b1; // Serial data bus flag
reg stop_flag_raw   = 1'b0; // End of transmission
reg comm_done = 1'b0;

wire [23:0] table_data; // Current data from table
assign scl_flag   = ((clock_count >= 6'h4) && (clock_count <= 6'h1E)) ? clock : scl_flag_raw;
assign sda_flag   = sda_flag_raw;
assign stop_flag   = stop_flag_raw;

I2CData SerialData(.clock(clock), .count(table_count), .table_data_out(table_data));

// Waiting for start_Flag
always @(posedge(clock), negedge(reset_n), negedge(start_n)) begin
	if(reset_n == 1'b0) begin
		start_flag <= 1'b0;
	end
	else if (start_n == 1'b0) begin
		start_flag <= 1'b1;
	end
	else if (stop_flag_raw == 1'b1) begin
		start_flag <= 1'b0;
	end
	else if ((comm_done  == 1'b0) && ((table_count != 1'b0) || (clock_count > 1'b0))) begin
		start_flag <= 1'b1;
	end
	else if (comm_done  == 1'b1) begin
		start_flag <= 1'b0;
	end
	else begin
		start_flag <= 1'b0;	
	end
end
	
// Table management loop
always @(negedge(reset_n), negedge(start_n), posedge(comm_done)) begin	
	if (reset_n == 1'b0) begin
		table_count <= 1'b0;
	end
	else if (start_n == 1'b0) begin
		table_count <= 1'b0;
	end
	else if (stop_flag_raw == 1'b1) begin
		table_count <= 1'b0;
	end
	else if (comm_done == 1'b0) begin
		table_count <= table_count;
	end
	else if (comm_done   == 1'b1) begin
		table_count <= table_count + 1'b1;
	end
	else begin
		table_count <= 1'b0;
	end
end

// Clock_Count Management
always @(posedge(clock), negedge(reset_n)) begin
	if (reset_n == 1'b0) begin
		clock_count <= 1'b0;
	end
	else if (start_flag == 0) begin
		clock_count <= 1'b0;
	end
	else if (start_flag == 1) begin
		clock_count <= clock_count + 1'b1;
	end
	else begin
		clock_count <= 1'b0;
	end
end

// Data Transmission
always @(negedge(clock)) begin
	case(clock_count)
	// Default
		6'h0: begin
			scl_flag_raw <= 1'b1;
			sda_flag_raw  <= 1'b1;
			comm_done   <= 1'b0;
		end
			
	// Start Bit	
		6'h1:  sda_flag_raw  <= 1'b0;
		6'h2:  scl_flag_raw <= 1'b0;
		
	// Address (Slave)
		6'h3:  sda_flag_raw  <= table_data[23]; 			// bit 7
		6'h4:	 sda_flag_raw  <= table_data[22];			// bit 6
		6'h5:	 sda_flag_raw  <= table_data[21];			// bit 5
		6'h6:  sda_flag_raw  <= table_data[20];			// bit 4
		6'h7:  sda_flag_raw  <= table_data[19];			// bit 3
		6'h8:  sda_flag_raw  <= table_data[18];			// bit 2
		6'h9:  sda_flag_raw  <= table_data[17];			// bit 1
		6'hA:	 sda_flag_raw  <= table_data[16];			// bit 0
		6'hB:	 sda_flag_raw  <= 1'bz;							// Slave Acknowledge
		
	// Address (Register)
		6'hC:  sda_flag_raw  <= table_data[15]; 			// bit 7
		6'hD:	 sda_flag_raw  <= table_data[14];			// bit 6
		6'hE:	 sda_flag_raw  <= table_data[13];			// bit 5
		6'hF:  sda_flag_raw  <= table_data[12];			// bit 4
		6'h10: sda_flag_raw  <= table_data[11];			// bit 3
		6'h11: sda_flag_raw  <= table_data[10];			// bit 2
		6'h12: sda_flag_raw  <= table_data[9];				// bit 1
		6'h13: sda_flag_raw  <= table_data[8];				// bit 0
		6'h14: sda_flag_raw  <= 1'bz;			            // Slave Acknowledge
		
	// Data
		6'h15: sda_flag_raw  <= table_data[7]; 		// bit 7
		6'h16: sda_flag_raw  <= table_data[6];			// bit 6
		6'h17: sda_flag_raw  <= table_data[5];			// bit 5
		6'h18: sda_flag_raw  <= table_data[4];			// bit 4
		6'h19: sda_flag_raw  <= table_data[3];			// bit 3
		6'h1A: sda_flag_raw  <= table_data[2];			// bit 2
		6'h1B: sda_flag_raw  <= table_data[1];			// bit 1
		6'h1C: sda_flag_raw  <= table_data[0];			// bit 0
		6'h1D: sda_flag_raw  <= 1'bz;						// Slave Acknowledge

	// Stop Bit
		6'h1E: begin
				 sda_flag_raw  <= 1'b0;
				 scl_flag_raw <= 1'b1;
				 comm_done   <= 1'b1;
		end
		6'h1F: begin
				 sda_flag_raw  <= 1'b1; 	
				if (table_count == 6'h14) begin
					stop_flag_raw   = 1'b1;
				end
		end
		
		default: begin 
				 sda_flag_raw <= 1'b1;
				 sda_flag_raw  <= 1'b1;
			end
	endcase
end

endmodule 