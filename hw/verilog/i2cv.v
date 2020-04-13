// I2c Module - Jack Allan - 2020
module i2c
(
	input reset_n,
	input start_n,
	input CLK,
	
	inout sda_Flag,
	
	output scl_Flag,
	output stop_Flag  
);


reg [5:0] table_Count = 1'b0;	// Tracks which data is being pointed to
reg [5:0] clock_Count = 1'b0; 


wire [23:0] table_Data; // Current data from table


reg start_Flag = 1'b0; // Start transmission

reg scl_Flag_Raw = 1'b1; // Serial clock flag
reg sda_Flag_Raw  = 1'b1; // Serial data bus flag
reg stop_Flag_Raw   = 1'b0; // End of transmission

reg comm_Done = 1'b0;

assign scl_Flag   = ((clock_Count >= 6'h4) && (clock_Count <= 6'h1E)) ? CLK : scl_Flag_Raw;
assign sda_Flag   = sda_Flag_Raw;
assign stop_Flag   = stop_Flag_Raw;

I2C_DATA SerialData(.CLK(CLK), .count(table_Count), .table_Data(table_Data));


// Waiting for start_Flag
always @(posedge(CLK), negedge(reset_n), negedge(start_n)) begin
	if(reset_n == 1'b0) begin
		start_Flag <= 1'b0;
	end
	else if (start_n == 1'b0) begin
		start_Flag <= 1'b1;
	end
	else if (stop_Flag_Raw == 1'b1) begin
		start_Flag <= 1'b0;
	end
	else if ((comm_Done  == 1'b0) && ((table_Count != 1'b0) || (clock_Count > 1'b0))) begin
		start_Flag <= 1'b1;
	end
	else if (comm_Done  == 1'b1) begin
		start_Flag <= 1'b0;
	end
	else begin
		start_Flag <= 1'b0;	
	end
end
	
// Table management loop
always @(negedge(reset_n), negedge(start_n), posedge(comm_Done)) begin	
	if (reset_n == 1'b0) begin
		table_Count <= 1'b0;
	end
	else if (start_n == 1'b0) begin
		table_Count <= 1'b0;
	end
	else if (stop_Flag_Raw == 1'b1) begin
		table_Count <= 1'b0;
	end
	else if (comm_Done == 1'b0) begin
		table_Count <= table_Count;
	end
	else if (comm_Done   == 1'b1) begin
		table_Count <= table_Count + 1'b1;
	end
	else begin
		table_Count <= 1'b0;
	end
end

// Clock_Count Management
always @(posedge(CLK), negedge(reset_n)) begin
	if (reset_n == 1'b0) begin
		clock_Count <= 1'b0;
	end
	else if (start_Flag == 0) begin
		clock_Count <= 1'b0;
	end
	else if (start_Flag == 1) begin
		clock_Count <= clock_Count + 1'b1;
	end
	else begin
		clock_Count <= 1'b0;
	end
end

// Data Transmission
always @(negedge(CLK)) begin
	case(clock_Count)
	// Default
		6'h0: begin
			scl_Flag_Raw <= 1'b1;
			sda_Flag_Raw  <= 1'b1;
			comm_Done   <= 1'b0;
		end
			
	// Start Bit	
		6'h1:  sda_Flag_Raw  <= 1'b0;
		6'h2:  scl_Flag_Raw <= 1'b0;
		
	// Address (Slave)
		6'h3:  sda_Flag_Raw  <= table_Data[23]; 			// bit 7
		6'h4:	 sda_Flag_Raw  <= table_Data[22];			// bit 6
		6'h5:	 sda_Flag_Raw  <= table_Data[21];			// bit 5
		6'h6:  sda_Flag_Raw  <= table_Data[20];			// bit 4
		6'h7:  sda_Flag_Raw  <= table_Data[19];			// bit 3
		6'h8:  sda_Flag_Raw  <= table_Data[18];			// bit 2
		6'h9:  sda_Flag_Raw  <= table_Data[17];			// bit 1
		6'hA:	 sda_Flag_Raw  <= table_Data[16];			// bit 0
		6'hB:	 sda_Flag_Raw  <= 1'bz;							// Slave Acknowledge
		
	// Address (Register)
		6'hC:  sda_Flag_Raw  <= table_Data[15]; 			// bit 7
		6'hD:	 sda_Flag_Raw  <= table_Data[14];			// bit 6
		6'hE:	 sda_Flag_Raw  <= table_Data[13];			// bit 5
		6'hF:  sda_Flag_Raw  <= table_Data[12];			// bit 4
		6'h10: sda_Flag_Raw  <= table_Data[11];			// bit 3
		6'h11: sda_Flag_Raw  <= table_Data[10];			// bit 2
		6'h12: sda_Flag_Raw  <= table_Data[9];				// bit 1
		6'h13: sda_Flag_Raw  <= table_Data[8];				// bit 0
		6'h14: sda_Flag_Raw  <= 1'bz;			            // Slave Acknowledge
		
	// Data
		6'h15: sda_Flag_Raw  <= table_Data[7]; 		// bit 7
		6'h16: sda_Flag_Raw  <= table_Data[6];			// bit 6
		6'h17: sda_Flag_Raw  <= table_Data[5];			// bit 5
		6'h18: sda_Flag_Raw  <= table_Data[4];			// bit 4
		6'h19: sda_Flag_Raw  <= table_Data[3];			// bit 3
		6'h1A: sda_Flag_Raw  <= table_Data[2];			// bit 2
		6'h1B: sda_Flag_Raw  <= table_Data[1];			// bit 1
		6'h1C: sda_Flag_Raw  <= table_Data[0];			// bit 0
		6'h1D: sda_Flag_Raw  <= 1'bz;						// Slave Acknowledge

	// Stop Bit
		6'h1E: begin
				 sda_Flag_Raw  <= 1'b0;
				 scl_Flag_Raw <= 1'b1;
				 comm_Done   <= 1'b1;
		end
		6'h1F: begin
				 sda_Flag_Raw  <= 1'b1; 	
				if (table_Count == 6'h14) begin
					stop_Flag_Raw   = 1'b1;
				end
		end
		
		default: begin 
				 scl_Flag_Raw <= 1'b1;
				 sda_Flag_Raw  <= 1'b1;
			end
	endcase
end

endmodule 