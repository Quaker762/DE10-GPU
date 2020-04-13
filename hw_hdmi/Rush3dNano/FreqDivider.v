// Frequency Divider Module
module FreqDivider
(
	input inputclock, 
	input clock_reset_n, 
	output OutputClock
);

parameter	inputClockSpeed = 50_000_000;		// 50MHz Internal FPGA Clock
parameter	outputClockSpeed = 1;				// 1Hz clock
parameter	bitWidth = 26;							// length of the counter

// toggle twice to make output fit the designed frequency
localparam [(bitWidth - 1) : 0] MaxCounting = (0.5 * (inputClockSpeed / outputClockSpeed));

reg [(bitWidth - 1) : 0] countNo = 0;
reg clock = 1'b0;

always @ (posedge (inputclock))
	begin
		if(clock_reset_n == 1'b0)				// if reset active
			begin
				clock 	<= 1'b0;					// reset all register
				countNo 	<= 1'b0;
			end
		
		else if(countNo == MaxCounting)		// if reach maximum counting number
			begin
				clock 	<= ~clock;				// toggle clock
				countNo 	<= 0;						// reset counter
			end
		else
			begin
				countNo <= countNo + 1'b1;		// counting
			end
	end
	
assign OutputClock = clock;

endmodule 