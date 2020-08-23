module Register_File
(
    input           write,
    input           read,
    input   [63:0]  writedata,
    output  [63:0]  readdata,
    input   [2:0]   address,
    input           clk,
    
    input           reset,  
    
    output  [63:0]  vertex_a_out,
    output  [63:0]  vertex_b_out,
    output  [63:0]  vertex_c_out
);

wire [2:0] decodedAddr;

wire vertex_a_load	= decodedAddr[0];
wire vertex_b_load	= decodedAddr[1];
wire vertex_c_load 	= decodedAddr[2];

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

endmodule
