// SDRAM Test for DE-10 Nano SoC
// The RAM has been mapped via the Avalon Memory Mapped Interface.
// The inspiration for this test is from the Alice4 project.
// Dr. Glenn Matthews
// 23/04/2020

module SDRAM_test(
	input wire systemClock,								// 100MHz clock.
    input wire reset_n,									// Active low reset.
    output reg [28:0] address,						// DDR3 address
	 
    output wire [7:0] burstcount,					// Number of bursts in the transactions
    input wire waitrequest,							// Wait request.
	 
    input wire [63:0] readdata,						// Data to write onto the bus? 
    input wire readdatavalid,							// Marker to indicate whether the read is valid.
    output reg read,										// Read data signal.


    output reg [63:0] writedata,						// Data that has been written.
    output wire [7:0] byteenable,
    output reg write

  //  output wire [31:0] debug_value0,
   // output wire [31:0] debug_value1


);

// Parameters used to control the read / writes to memory.
assign burstcount = 8'h01;			// Only send one byte at a time.
assign byteenable = 8'hFF;			// Need to see what this one does.

reg [63:0] data;						// Data to be written / read from the DDR3

// 1G minus 128M, in 64-bit units:
parameter TEST_ADDRESS = 29'h0700_0000;

// State Machine Variables
parameter stateReset = 4'h0;
parameter stateInit = 4'h1;						// Initialisation
parameter stateWriteStart = 4'h2;
parameter stateWriteWait = 4'h3;
parameter stateReadStart = 4'h4;
parameter stateReadWait = 4'h5;
parameter stateDone = 4'h6;

// Current- and next-state varaibles.
reg [3:0] currentState = stateReset;
reg [3:0] nextState = stateReset;

// Create the stateLogic
always @(posedge(systemClock), negedge(reset_n))
	begin: stateLogic
		if(!reset_n)
			currentState <= stateReset;
		else
			currentState <= nextState;
	end
	
	
// State Transition Logic
always @(currentState, waitrequest, readdatavalid)
		begin :nextStateLogic
			case (currentState)
				stateReset:			nextState = stateInit;
				stateInit: 			nextState = stateWriteStart;
				stateWriteStart:	nextState = stateWriteWait;
				stateWriteWait:
					begin
						if(!waitrequest) nextState = stateReadStart;
						else nextState = stateWriteWait;
					end
				stateReadStart:	nextState = stateReadWait;
				stateReadWait:
					begin
						//if(!waitrequest) nextState = stateReadWait;
						if(readdatavalid) nextState = stateDone;
						else nextState = stateReadWait;
					end
				stateDone:			nextState = stateDone;
			
			default: nextState = stateInit;
			
			endcase	
		end

// State output logic
always @(currentState, waitrequest, readdatavalid)
	begin
	case (currentState)
		stateReset: 
			begin
				address = 29'h0;								// Set the start address to 0.
				read = 1'b0;									// Read bit low.
				writedata = 64'h0;							// Data to write set to 0.
				write = 1'b0;									// Write bit low.
				data <= 64'h0;									// Data packet to 0.
			end
		
		stateInit:
			begin
				address = 29'h0;								// Set the start address to 0.
				read = 1'b0;									// Read bit low.
				writedata = 64'h0;							// Data to write set to 0.
				write = 1'b0;									// Write bit low.
				data <= 64'h2357_1113_1719_2329;			// Data packet value
		
			end
			
		stateWriteStart:
			begin
				address = TEST_ADDRESS;						// Set the address to write to.
				read = 1'b0;									// Read bit low.
				writedata = 64'hDEAD_BEEF_CAFE_BABE;	// Data to write set to 0.
				write = 1'b1;									// Write bit low.
				data <= 64'h2357_1113_1719_2329;			// Data packet value
			
			end

		stateWriteWait:
			begin
				if (!waitrequest) 
					begin
						address = 29'h0;								// Set the address to read from
						read = 1'b0;									// Keep the read bit set low.
						writedata = 64'h0;							// Data to write set to 0 (as we are in the read phase).
						write = 1'b0;									// Write bit low.
						data <= 64'h0;									// Data packet value
					end
				else
					begin
						address = TEST_ADDRESS;						// Set the address to write to.
						read = 1'b0;									// Read bit low.
						writedata = 64'hDEAD_BEEF_CAFE_BABE;	// Data to write set to 0.
						write = 1'b1;									// Write bit low.
						data <= 64'h2357_1113_1719_2329;			// Data packet value
					end
			end
		
		stateReadStart:
			begin
				address = TEST_ADDRESS;						// Set the address to read from
				read = 1'b1;									// Enable the read bit.
				writedata = 64'h0;							// Data to write set to 0 (as we are in the read phase).
				write = 1'b0;									// Write bit low.
				data <= 64'h0;									// Data packet value
			end
			
			
		stateReadWait:
			begin
				if(!waitrequest) 
					begin
						address = TEST_ADDRESS;				// Set the address to read from
						read = 1'b0;							// Enable the read bit.
						writedata = 64'h0;					// Data to write set to 0 (as we are in the read phase).
						write = 1'b0;							// Write bit low.
						data <= 64'h0;							// Data packet value
					end
				if(readdatavalid)
					begin
						address = TEST_ADDRESS;				// Set the address to read from
						read = 1'b0;							// Enable the read bit.
						writedata = 64'h0;					// Data to write set to 0 (as we are in the read phase).
						write = 1'b0;							// Write bit low.
						data <= readdata;						// Data packet value
					end
				else
					begin
						address = TEST_ADDRESS;						// Set the address to read from
						read = 1'b1;									// Enable the read bit.
						writedata = 64'h0;							// Data to write set to 0 (as we are in the read phase).
						write = 1'b0;									// Write bit low.
						data <= 64'h0;									// Data packet value
					end
					
			end
		
		stateDone:
			begin
				address = 29'h0;
				read = 1'b0;								// Enable the read bit.
				writedata = 64'h0;							// Data to write set to 0 (as we are in the read phase).
				write = 1'b0;								// Write bit low.
				data <= readdata;							// Data packet value
			end
			
		default: 
			begin
				address = 29'h0;							// Set the start address to 0.
				read = 1'b0;								// Read bit low.
				writedata = 64'h0;						// Data to write set to 0.
				write = 1'b0;								// Write bit low.
				data <= 64'h0;								// Data packet to 0.
			end
		endcase	
	end
	


endmodule
