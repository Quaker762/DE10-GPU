/**
 *	VGA Controller Module
 * Also implements signal loading to the 
 */
 
module VGAController
(
	input pixel_clock, 
	input reset_n,
	input beg,
	
	output reg hsync,
	output reg vsync,
	output dac_sync_pin_n,
	output dac_blank_pin_n
);
	
wire [7:0] VGA_RED;
wire [7:0] VGA_BLUE;
wire [7:0] VGA_GRN;

reg blank_reg = 1'b0;
reg sync_reg = 1'b0;
assign dac_blank_pin_n = blank_reg;
assign dac_sync_pin_n = sync_reg;

// Resolution: SVGA60 (800x600,60P)
// Pixel Clock = 40MHz

parameter HTOTAL 	= 12'd1056; // Total Horizontal Pixels (and sync period)
parameter HSLEN 	= 12'd128; // Horizontal Sync Period
parameter HBP 		= 12'd88; // Horizontal Back Porch
parameter HRES 	= 12'd800; // Horizontal Resolution
parameter HFP 		= 12'd40; // Horizontal Front Porch

parameter VTOTAL 	= 12'd628; // Total Vertical Pixels (and sync period)
parameter VSLEN 	= 12'd4; // Vertical Sync Period
parameter VBP 		= 12'd23; // Vertical Back Porch
parameter VRES 	= 12'd600; // Vertical Resolution
parameter VFP 		= 12'd1; // Vertical Front Porch

reg[11:0] horizontal_pixel_count = 12'd0; // Current Horizontal Pixel Count
reg[11:0] vertical_pixel_count = 12'd0; // Current Vertical Pixel Count

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