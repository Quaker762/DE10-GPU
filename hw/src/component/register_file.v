module Register_File
(
    input           write,
    input           read,
    input   [63:0]  writedata,
    output  [63:0]  readdata,
    input   [3:0]   address,
    input           clk,
    
    input           reset,
	 
	 input 	[63:0]  control_status_in,
	 input			  control_status_load_fpga,
    
    output  [63:0]  vertex_a_out,
    output  [63:0]  vertex_b_out,
    output  [63:0]  vertex_c_out,
	 output  [63:0]  color_a_out,
    output  [63:0]  color_b_out,
    output  [63:0]  color_c_out,
	 output  [63:0]  back_colour_out,
	 output  [63:0]  control_status_out,
	 output  [63:0]  win_size_out
);

wire [10:0] decodedAddr;

wire vertex_a_load			= decodedAddr[0];
wire vertex_b_load			= decodedAddr[1];
wire vertex_c_load 			= decodedAddr[2];
wire color_a_load				= decodedAddr[3];
wire color_b_load				= decodedAddr[4];
wire color_c_load 			= decodedAddr[5];
wire back_colour_load 		= decodedAddr[6];
wire control_status_load_w = decodedAddr[7];
wire control_status_load_r = decodedAddr[8];
wire win_size_load		   = decodedAddr[9];

address_decoder decoder
(
	.ce(write || read),
	.address(address),
	.out(decodedAddr)
);

register #(64) vertex_a
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~vertex_a_load),
    
    .Q(vertex_a_out)
);

register #(64) vertex_b
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~vertex_b_load),
    
    .Q(vertex_b_out)
);

register #(64) vertex_c
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~vertex_c_load),
    
    .Q(vertex_c_out)
);

register #(64) color_a
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~color_a_load),
    
    .Q(color_a_out)
);

register #(64) color_b
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~color_b_load),
    
    .Q(color_b_out)
);

register #(64) color_c
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~color_c_load),
    
    .Q(color_c_out)
);

register #(64) back_colour
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~back_colour_load),
    
    .Q(back_colour_out)
);

register_rw #(64) control_status
(
    .D(writedata),
    .D2(control_status_in),
    .clk(clk),
    .reset(reset),
    .load(~control_status_load_w),
    .load2(~control_status_load_fpga),
    
    .Q(control_status_out)
);

register #(64) win_size
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~win_size_load),
    
    .Q(win_size_out)
);

// We only have one thing to read currently
assign readdata = control_status_out;

endmodule
