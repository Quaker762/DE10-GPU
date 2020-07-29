/*
 *	Register File module
 *	
 * Jesse Buhagiar 2020
 */
module RegisterFile
(
	input 			clock,				// Clock input (platform designer)
	input				write,				// Write signal (platform designer)
	input				read,					// Read signal (platform designer)
	input				reset_n,				// Reset signal
	input[32:0]		register_index,		// Register number
	input[31:0]		register_data_in,
	output[31:0]	register_data_out,
	
	
	// The following is a list of the registers
	output[31:0] status_register,
	output[31:0] fb_color_register,
	output[31:0] fb_fill_command,
	output[15:0] fb_width_register,
	output[15:0] fb_height_register,
	output[15:0] vertex_a_x_register,
	output[15:0] vertex_a_y_register,
	output[15:0] vertex_b_x_register,
	output[15:0] vertex_b_y_register,
	output[15:0] vertex_c_x_register,
	output[15:0] vertex_c_y_register,
	output[31:0] triangle_start_red_register,
	output[31:0] triangle_start_green_register,
	output[31:0] triangle_start_blue_register,
	output[31:0] triangle_red_dx_register,
	output[31:0] triangle_green_dx_register,
	output[31:0] triangle_blue_dx_register,
	output[31:0] triangle_red_dy_register,
	output[31:0] triangle_green_dy_register,
	output[31:0] triangle_blue_dy_register,
	output[31:0] triangle_command_register
);

reg[32:0] registers[0:6];

parameter READ_SIGNAL = 1'b1; 	// Active low signal for READ
parameter WRITE_SIGNAL = 1'b1;	// Active high signal for WRITE
parameter RESET_SIGNAL = 1'b0;	// Active low signal for RESET
parameter NUMBER_OF_REGISTERS = 128;

integer i;

// This occurs on the positive edge of the clock
always @(posedge clock) begin
	if(reset_n == RESET_SIGNAL) begin
		for(i = 0; i < NUMBER_OF_REGISTERS; i = i + 1) begin
			registers[i] <= 32'b0;
		end
	end
	
	if(write == WRITE_SIGNAL) begin
		registers[register_index] <= register_data_in;
	end
end

assign status_register = (read ? registers[0] : 32'bz);
assign fb_color_register = (read ? registers[1] : 32'bz);
assign fb_fill_command = (read ? registers[2] : 32'bz);
assign fb_width_register = (read ? registers[2] : 32'bz);
assign fb_height_register = (read ? registers[2] : 32'bz);
assign vertex_a_x_register = (read ? registers[2] : 32'bz);
assign vertex_a_y_register = (read ? registers[2] : 32'bz);
assign vertex_b_x_register = (read ? registers[2] : 32'bz);
assign vertex_b_y_register = (read ? registers[2] : 32'bz);
assign vertex_c_x_register = (read ? registers[2] : 32'bz);
assign vertex_c_y_register = (read ? registers[2] : 32'bz);
assign triangle_start_red_register = (read ? registers[2] : 32'bz);
assign triangle_start_green_register = (read ? registers[2] : 32'bz);
assign triangle_start_blue_register = (read ? registers[2] : 32'bz);
assign triangle_red_dx_register = (read ? registers[2] : 32'bz);
assign triangle_green_dx_register = (read ? registers[2] : 32'bz);
assign triangle_blue_dx_register = (read ? registers[2] : 32'bz);
assign triangle_red_dy_register = (read ? registers[2] : 32'bz);
assign triangle_green_dy_register = (read ? registers[2] : 32'bz);
assign triangle_blue_dy_register = (read ? registers[2] : 32'bz);
assign triangle_command_register = (read ? registers[2] : 32'bz);

endmodule 