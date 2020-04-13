/*
 *	HDMI Controller Module
 * Jack Allan 2020
 */
 module HDMIController
(
	input enable,
	input pixel_clock480, 
	input pixel_clock768, 
	input pixel_clock1080, 
	input reset_n,
	input [1:0] switch_res,
	input beg,
	inout hdmi_sda,
	output hdmi_scl,
	output reg hsync,
	output reg vsync,
	output dac_sync_pin_n,
	output dac_blank_pin_n
);

i2c start_config(.reset_n(reset_n), .start_n(), .CLK(pixel_clock1080), .sda_Flag(hdmi_sda), .scl_Flag(hdmi_scl), .stop_Flag(stop_flag));
 
 // Resolution: VGA_NTSC (640*480@60P, 4:3) and Pixel Clock = 25.175MHz
parameter HTOTAL480 	= 12'd800; // Total Horizontal Pixels (and sync period)
parameter HSLEN480	= 12'd96; // Horizontal Sync Period
parameter HBP480 		= 12'd48; // Horizontal Back Porch
parameter HRES480 	= 12'd640; // Horizontal Resolution
parameter HFP480 		= 12'd16; // Horizontal Front Porch

parameter VTOTAL480 	= 12'd525; // Total Vertical Pixels (and sync period)
parameter VSLEN480 	= 12'd2; // Vertical Sync Period
parameter VBP480 		= 12'd33; // Vertical Back Porch
parameter VRES480 	= 12'd480; // Vertical Resolution
parameter VFP480 		= 12'd10; // Vertical Front Porch

 // Resolution: XGA (1024*768@60P, 4:3) and Pixel Clock = 65MHz
parameter HTOTAL768 	= 12'd1344; // Total Horizontal Pixels (and sync period)
parameter HSLEN768	= 12'd136; // Horizontal Sync Period
parameter HBP768 		= 12'd160; // Horizontal Back Porch
parameter HRES768 	= 12'd1024; // Horizontal Resolution
parameter HFP768 		= 12'd24; // Horizontal Front Porch

parameter VTOTAL768 	= 12'd806; // Total Vertical Pixels (and sync period)
parameter VSLEN768 	= 12'd6; // Vertical Sync Period
parameter VBP768 		= 12'd29; // Vertical Back Porch
parameter VRES768 	= 12'd768; // Vertical Resolution
parameter VFP768 		= 12'd3; // Vertical Front Porch

 
// Resolution: HD1080 (1920*1080@60P, 16:9) and Pixel Clock = 148.5MHz
parameter HTOTAL1080 = 12'd2200; // Total Horizontal Pixels (and sync period)
parameter HSLEN1080	= 12'd44; // Horizontal Sync Period
parameter HBP1080		= 12'd148; // Horizontal Back Porch
parameter HRES1080	= 12'd1920; // Horizontal Resolution
parameter HFP1080 	= 12'd88; // Horizontal Front Porch

parameter VTOTAL1080	= 12'd1125; // Total Vertical Pixels (and sync period)
parameter VSLEN1080	= 12'd5; // Vertical Sync Period
parameter VBP1080		= 12'd36; // Vertical Back Porch
parameter VRES1080	= 12'd1080; // Vertical Resolution
parameter VFP1080		= 12'd4; // Vertical Front Porch 
 
// Default parameters for Resolution 
// Default is 640*480@60p
reg [11:0] HTOTAL =  12'd800; // Total Horizontal Pixels (and sync period)
reg [11:0] HSLEN = 12'd96; // Horizontal Sync Period
reg [11:0] HBP = 12'd48; // Horizontal Back Porch
reg [11:0] HRES = 12'd640; // Horizontal Resolution
reg [11:0] HFP = 12'd16; // Horizontal Front Porch

reg [11:0] VTOTAL = 12'd525; // Total Vertical Pixels (and sync period)
reg [11:0] VSLEN = 12'd2; // Vertical Sync Period
reg [11:0] VBP = 12'd33; // Vertical Back Porch
reg [11:0] VRES = 12'd480; // Vertical Resolution
reg [11:0] VFP = 12'd10; // Vertical Front Porch 
 
 
 
wire [7:0] VGA_RED;
wire [7:0] VGA_BLUE;
wire [7:0] VGA_GRN;
reg pixel_clock;

reg blank_reg = 1'b0;
reg sync_reg = 1'b0;
reg currentRes = 2'b0;
assign dac_blank_pin_n = blank_reg;
assign dac_sync_pin_n = sync_reg; 

reg[11:0] horizontal_pixel_count = 12'd0; // Current Horizontal Pixel Count
reg[11:0] vertical_pixel_count = 12'd0; // Current Vertical Pixel Count
 
always @(negedge(reset_n)) begin: resChange
	case(currentRes)
		2'b00 : begin
		pixel_clock <= pixel_clock480;
		HTOTAL <= HTOTAL480;
		HSLEN <= HSLEN480;
		HBP <= HBP480;
		HRES <= HRES480;
		HFP <= HFP480;
		VTOTAL <= VTOTAL480;
		VSLEN <= VSLEN480;
		VBP <= VBP480;
		VRES <= VRES480;
		VFP <= VFP480;
		end
		2'b01 : begin
		pixel_clock <= pixel_clock768;
		HTOTAL <= HTOTAL768;
		HSLEN <= HSLEN768;
		HBP <= HBP768;
		HRES <= HRES768;
		HFP <= HFP768;
		VTOTAL <= VTOTAL768;
		VSLEN <= VSLEN768;
		VBP <= VBP768;
		VRES <= VRES768;
		VFP <= VFP768;
		end
		2'b10 : begin
		pixel_clock <= pixel_clock1080;
		HTOTAL <= HTOTAL1080;
		HSLEN <= HSLEN1080;
		HBP <= HBP1080;
		HRES <= HRES1080;
		HFP <= HFP1080;
		VTOTAL <= VTOTAL1080;
		VSLEN <= VSLEN1080;
		VBP <= VBP1080;
		VRES <= VRES1080;
		VFP <= VFP1080;
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
	else if(stop_flag)
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
	else if(stop_flag)
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