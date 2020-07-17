/*
 *	VGA Controller Module
 * Jack Allan 2020
 */
module vga_controller
(
	input refclk,
	input reset_n,
	input [1:0] resolution,
	
	output wire pixel_clock,
	output reg hsync,
	output reg vsync,
	output reg sync_n,
	output reg blank_n
);

// Resolution: VGA60 (640x480@60P) and Pixel Clock = 25.175MHz
parameter HTOTAL640 = 12'd800; // Total Horizontal Pixels (and sync period)
parameter HSLEN640  = 12'd96;  // Horizontal Sync Period
parameter HBP640    = 12'd48;  // Horizontal Back Porch
parameter HRES640   = 12'd640; // Horizontal Resolution
parameter HFP640    = 12'd16;  // Horizontal Front Porch

parameter VTOTAL640 = 12'd525; // Total Vertical Pixels (and sync period)
parameter VSLEN640  = 12'd2;   // Vertical Sync Period
parameter VBP640    = 12'd33;  // Vertical Back Porch
parameter VRES640   = 12'd480; // Vertical Resolution
parameter VFP640    = 12'd10;  // Vertical Front Porch

// Resolution: SVGA60 (800x600@60P) and Pixel Clock = 40MHz
parameter HTOTAL800 = 12'd1056; // Total Horizontal Pixels (and sync period)
parameter HSLEN800  = 12'd128;  // Horizontal Sync Period
parameter HBP800    = 12'd88;   // Horizontal Back Porch
parameter HRES800   = 12'd800;  // Horizontal Resolution
parameter HFP800    = 12'd40;   // Horizontal Front Porch

parameter VTOTAL800 = 12'd628; // Total Vertical Pixels (and sync period)
parameter VSLEN800  = 12'd4;   // Vertical Sync Period
parameter VBP800    = 12'd23;  // Vertical Back Porch
parameter VRES800   = 12'd600; // Vertical Resolution
parameter VFP800    = 12'd1;   // Vertical Front Porch

// Resolution: XGA60 (1024x768@60P) and Pixel Clock = 65MHz
parameter HTOTAL1024 = 12'd1344; // Total Horizontal Pixels (and sync period)
parameter HSLEN1024  = 12'd136;  // Horizontal Sync Period
parameter HBP1024    = 12'd160;  // Horizontal Back Porch
parameter HRES1024   = 12'd1024; // Horizontal Resolution
parameter HFP1024    = 12'd24;   // Horizontal Front Porch

parameter VTOTAL1024 = 12'd806; // Total Vertical Pixels (and sync period)
parameter VSLEN1024  = 12'd6;   // Vertical Sync Period
parameter VBP1024    = 12'd29;  // Vertical Back Porch
parameter VRES1024   = 12'd768; // Vertical Resolution
parameter VFP1024    = 12'd3;   // Vertical Front Porch

// Default is 800*600@60p
reg [11:0] HTOTAL = HTOTAL800; // Total Horizontal Pixels (and sync period)
reg [11:0] HSLEN  = HSLEN800;  // Horizontal Sync Period
reg [11:0] HBP    = HBP800;    // Horizontal Back Porch
reg [11:0] HRES   = HRES800;   // Horizontal Resolution
reg [11:0] HFP    = HFP800;    // Horizontal Front Porch

reg [11:0] VTOTAL = VTOTAL800; // Total Vertical Pixels (and sync period)
reg [11:0] VSLEN  = VSLEN800;  // Vertical Sync Period
reg [11:0] VBP    = VBP800;    // Vertical Back Porch
reg [11:0] VRES   = VRES800;   // Vertical Resolution
reg [11:0] VFP    = VFP800;    // Vertical Front Porch

reg[11:0] horizontal_pixel_count = 12'd0; // Current Horizontal Pixel Count
reg[11:0] vertical_pixel_count   = 12'd0; // Current Vertical Pixel Count

wire vga60_pixel_clock;
wire svga60_pixel_clock;
wire xga60_pixel_clock;

vga60_svga60_pll vga60_svga60_pll
(
	.refclk(refclk),               // 50MHz input
	.rst(1'b0),
	.outclk_0(vga60_pixel_clock),  // 25MHz output (This should be 25.175MHz)
	.outclk_1(svga60_pixel_clock), // 40MHz output
);

xga60_pll xga60_pll
(
	.refclk(refclk),              // 50MHz input
	.rst(1'b0),
	.outclk_0(xga60_pixel_clock), // 65MHz output
);

reg [1:0] new_resolution = 2'b01;

assign pixel_clock = new_resolution[1] ? xga60_pixel_clock : (new_resolution[0] ? svga60_pixel_clock : vga60_pixel_clock);

always @(negedge(reset_n)) begin: resChange
	case(resolution)
		2'b00 : begin
		new_resolution <= resolution;
		HTOTAL <= HTOTAL640;
		HSLEN <= HSLEN640;
		HBP <= HBP640;
		HRES <= HRES640;
		HFP <= HFP640;
		VTOTAL <= VTOTAL640;
		VSLEN <= VSLEN640;
		VBP <= VBP640;
		VRES <= VRES640;
		VFP <= VFP640;
		end
		2'b01 : begin
		new_resolution <= resolution;
		HTOTAL <= HTOTAL800;
		HSLEN <= HSLEN800;
		HBP <= HBP800;
		HRES <= HRES800;
		HFP <= HFP800;
		VTOTAL <= VTOTAL800;
		VSLEN <= VSLEN800;
		VBP <= VBP800;
		VRES <= VRES800;
		VFP <= VFP800;
		end
		2'b10 : begin
		new_resolution <= resolution;
		HTOTAL <= HTOTAL1024;
		HSLEN <= HSLEN1024;
		HBP <= HBP1024;
		HRES <= HRES1024;
		HFP <= HFP1024;
		VTOTAL <= VTOTAL1024;
		VSLEN <= VSLEN1024;
		VBP <= VBP1024;
		VRES <= VRES1024;
		VFP <= VFP1024;
		end
		default: begin
		new_resolution <= new_resolution;
		HTOTAL <= HTOTAL;
		HSLEN <= HSLEN;
		HBP <= HBP;
		HRES <= HRES;
		HFP <= HFP;
		VTOTAL <= VTOTAL;
		VSLEN <= VSLEN;
		VBP <= VBP;
		VRES <= VRES;
		VFP <= VFP;	
		end
	endcase	
end

always @(posedge(pixel_clock), negedge(reset_n)) begin: horizontalPixelCounter
	if(!reset_n)
	begin
		horizontal_pixel_count <= 12'd0;
	end
	else
	begin
		if (horizontal_pixel_count >= HTOTAL)
		begin
			horizontal_pixel_count <= 12'd0;
		end
		else 
		begin
			horizontal_pixel_count <= horizontal_pixel_count + 1'b1;
		end
	end
end	
		
always @(posedge(pixel_clock), negedge(reset_n)) begin: verticalPixelCounter
	if(!reset_n)
	begin
		vertical_pixel_count <= 12'd0;
	end
	else
	begin
		if (horizontal_pixel_count >= HTOTAL)
		begin
			if(vertical_pixel_count >= VTOTAL)
			begin
				vertical_pixel_count <= 12'd0;		
			end
			else
			begin
				vertical_pixel_count <= vertical_pixel_count + 1'b1;
			end	
		end
	end
end

always @(posedge(pixel_clock), negedge(reset_n)) begin: horizontalSync
	if(!reset_n) 
	begin
		hsync <= 1'b0;
		blank_n <= 1'b0;
	end
	else if(horizontal_pixel_count < HSLEN)
	begin
		hsync <= 1'b0;
		blank_n <= 1'b0;
	end
		else if(horizontal_pixel_count < HSLEN + HBP)
		begin
			hsync <= 1'b1;
			blank_n <= 1'b0;
		end
	else if(horizontal_pixel_count < HTOTAL - HFP)
	begin
		hsync <= 1'b1;
		blank_n <= 1'b1;
	end
		else if(horizontal_pixel_count < HTOTAL)
		begin
			hsync <= 1'b1;
			blank_n <= 1'b0;
		end
	else 
	begin
		hsync <= 1'b0;
		blank_n <= 1'b0;
	end
end 

always @(posedge(pixel_clock), negedge(reset_n)) begin: verticalSync
	if(!reset_n) 
	begin
		vsync <= 1'b0;
	end
	else if(vertical_pixel_count < VSLEN)
	begin
		vsync <= 1'b0;
	end
	else if(vertical_pixel_count < VTOTAL)
	begin
		vsync <= 1'b1;
	end
	else begin
		vsync <= 1'b0;
	end
end 

endmodule 