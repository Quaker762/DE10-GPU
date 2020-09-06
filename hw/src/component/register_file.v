module Register_File
(
    input           write,
    input           read,
    input   [63:0]  writedata,
    output  [63:0]  readdata,
    input   [2:0]   address,
    input           clk,
    
    input           reset,
	 
	 input 	[5:0]	  control_bit_address,
	 input   		  control_bit_load,
	 input           control_bit_in,
	 output 	        control_bit_out,
    
    output  [63:0]  vertex_a_out,
    output  [63:0]  vertex_b_out,
    output  [63:0]  vertex_c_out,
	 output  [63:0]  back_colour_out,
	 output  [63:0]  control_status_out
);

wire [5:0] decodedAddr;

wire vertex_a_load			= decodedAddr[0];
wire vertex_b_load			= decodedAddr[1];
wire vertex_c_load 			= decodedAddr[2];
wire back_colour_load 		= decodedAddr[3];
wire control_status_load_w = decodedAddr[4];
wire control_status_load_r = decodedAddr[5];

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

register #(64) back_colour
(
    .D(writedata),
    .clk(clk),
    .reset(reset),
    .load(~back_colour_load),
    
    .Q(back_colour_out)
);

register_csr #(64) control_status
(
    .D_all(writedata),
	 .D_bit(control_bit_in),
    .clk(clk),
    .reset(reset),
    .load_all(~control_status_load_w),
	 .load_bit(control_bit_load),
    
    .Q_all(control_status_out),
	 .Q_bit(control_bit_out)
);

// We only have one thing to read currently
assign readdata = control_status_out;

endmodule
