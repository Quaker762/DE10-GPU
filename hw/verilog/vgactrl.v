/**
 *	VGA Controller Module
 * Also implements signal loading to the 
 */
 
module VGAController
(
	input pixel_clock800, 
	input pixel_clock640, 
	input pixel_clock1024, 
	input reset_n,
	input [1:0] switch_res,
	input beg,
	
	output reg hsync,
	output reg vsync,
	output dac_sync_pin_n,
	output dac_blank_pin_n
);

// Resolution: SVGA60 (800x600@60P) and Pixel Clock = 40MHz
parameter HTOTAL800 	= 12'd1056; // Total Horizontal Pixels (and sync period)
parameter HSLEN800 	= 12'd128; // Horizontal Sync Period
parameter HBP800 		= 12'd88; // Horizontal Back Porch
parameter HRES800 	= 12'd800; // Horizontal Resolution
parameter HFP800 		= 12'd40; // Horizontal Front Porch

parameter VTOTAL800 	= 12'd628; // Total Vertical Pixels (and sync period)
parameter VSLEN800 	= 12'd4; // Vertical Sync Period
parameter VBP800 		= 12'd23; // Vertical Back Porch
parameter VRES800 	= 12'd600; // Vertical Resolution
parameter VFP800 		= 12'd1; // Vertical Front Porch

// Resolution: VGA60 (640x480@60P) and Pixel Clock = 25.175MHz
parameter HTOTAL640 	= 12'd800; // Total Horizontal Pixels (and sync period)
parameter HSLEN640 	= 12'd96; // Horizontal Sync Period
parameter HBP640		= 12'd48; // Horizontal Back Porch
parameter HRES640		= 12'd640; // Horizontal Resolution
parameter HFP640 		= 12'd16; // Horizontal Front Porch

parameter VTOTAL640 	= 12'd525; // Total Vertical Pixels (and sync period)
parameter VSLEN640 	= 12'd2; // Vertical Sync Period
parameter VBP640 		= 12'd33; // Vertical Back Porch
parameter VRES640 	= 12'd480; // Vertical Resolution
parameter VFP640 		= 12'd10; // Vertical Front Porch

// Resolution: XGA60 (1024x768@60P) and Pixel Clock = 65MHz
parameter HTOTAL1024 = 12'd1344; // Total Horizontal Pixels (and sync period)
parameter HSLEN1024 	= 12'd136; // Horizontal Sync Period
parameter HBP1024		= 12'd160; // Horizontal Back Porch
parameter HRES1024	= 12'd1024; // Horizontal Resolution
parameter HFP1024 	= 12'd24; // Horizontal Front Porch

parameter VTOTAL1024 = 12'd806; // Total Vertical Pixels (and sync period)
parameter VSLEN1024 	= 12'd6; // Vertical Sync Period
parameter VBP1024		= 12'd29; // Vertical Back Porch
parameter VRES1024 	= 12'd768; // Vertical Resolution
parameter VFP1024		= 12'd3; // Vertical Front Porch

wire [7:0] VGA_RED;
wire [7:0] VGA_BLUE;
wire [7:0] VGA_GRN;
reg pixel_clock;

reg blank_reg = 1'b0;
reg sync_reg = 1'b0;
reg currentRes = 2'b0;
assign dac_blank_pin_n = blank_reg;
assign dac_sync_pin_n = sync_reg;

// Default is 800*600@60p
reg [11:0] HTOTAL = 12'd1056; // Total Horizontal Pixels (and sync period)
reg [11:0] HSLEN = 12'd128; 	// Horizontal Sync Period
reg [11:0] HBP = 12'd88; // Horizontal Back Porch
reg [11:0] HRES = 12'd800; // Horizontal Resolution
reg [11:0] HFP = 12'd40; // Horizontal Front Porch

reg [11:0] VTOTAL = 12'd628; // Total Vertical Pixels (and sync period)
reg [11:0] VSLEN = 12'd4; // Vertical Sync Period
reg [11:0] VBP = 12'd23; // Vertical Back Porch
reg [11:0] VRES = 12'd600; // Vertical Resolution
reg [11:0] VFP = 12'd1; // Vertical Front Porch



reg[11:0] horizontal_pixel_count = 12'd0; // Current Horizontal Pixel Count
reg[11:0] vertical_pixel_count = 12'd0; // Current Vertical Pixel Count

always @(negedge(reset_n)) begin: resChange
	case(currentRes)
		2'b00 : begin
		pixel_clock <= pixel_clock800;
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
		2'b01 : begin
		pixel_clock <= pixel_clock640;
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
		2'b10 : begin
		pixel_clock <= pixel_clock1024;
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
		pixel_clock <= pixel_clock;
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
	else if(beg)
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
	else
	begin
		horizontal_pixel_count <= 12'd0;
	end
end	
		
always @(posedge(pixel_clock), negedge(reset_n)) begin: verticalPixelCounter
	if(!reset_n)
	begin
		vertical_pixel_count <= 12'd0;
	end
	else if(beg)
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
		blank_reg <= 1'b0;
	end
	else if(horizontal_pixel_count < HSLEN)
	begin
		hsync <= 1'b0;
		blank_reg <= 1'b0;
	end
		else if(horizontal_pixel_count < HSLEN + HBP)
		begin
			hsync <= 1'b1;
			blank_reg <= 1'b0;
		end
	else if(horizontal_pixel_count < HTOTAL - HFP)
	begin
		hsync <= 1'b1;
		blank_reg <= 1'b1;
	end
		else if(horizontal_pixel_count < HTOTAL)
		begin
			hsync <= 1'b1;
			blank_reg <= 1'b0;
		end
	else 
	begin
		hsync <= 1'b0;
		blank_reg <= 1'b0;
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