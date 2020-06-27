// HDMI Outputter Module
module HdmiOutput
(
	input 	clock_480p,
	input 	clock_768p,
	input 	clock_1080p,
	input		reset,
	input 	start,
	input 	[3:0] switch,
	output	reg horizontal_sync,
	output	reg vertical_sync,
	output	data_enable,
	output	pixel_clock
);

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
/*
parameter HTOTAL1080 = 12'd2000-12'd1; // Total Horizontal Pixels (and sync period)
parameter HSLEN1080	= 12'd12; // Horizontal Sync Period
parameter HBP1080		= 12'd40; // Horizontal Back Porch
parameter HRES1080	= 12'd1920; // Horizontal Resolution
parameter HFP1080 	= 12'd28; // Horizontal Front Porch

parameter VTOTAL1080	= 12'd1105-12'd1; // Total Vertical Pixels (and sync period)
parameter VSLEN1080	= 12'd4; // Vertical Sync Period
parameter VBP1080		= 12'd18; // Vertical Back Porch
parameter VRES1080	= 12'd1080; // Vertical Resolution
parameter VFP1080		= 12'd3; // Vertical Front Porch 
*/
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
// Current Horizontal/Vertical Resolution
reg[11:0] hor_total 			= HTOTAL480;	// Total Horizontal Pixels
reg[11:0] hor_sync_len  	= HSLEN480;	// Horizontal Sync Length
reg[11:0] hor_back_porch 	= HBP480;		//	Horizontal Back Porch
reg[11:0] hor_resolution	= HRES480;		// Horizontal Resolution
reg[11:0] hor_front_porch	= HFP480;		// Horizontal Front Porch

reg[11:0] ver_total			= VTOTAL480;	// Total Vertical Pixels
reg[11:0] ver_sync_len		= VSLEN480;	// Vertical Sync Length
reg[11:0] ver_back_porch	= VBP480;		// Vertical Back Porch
reg[11:0] ver_resolution	= VRES480;		// Vertical Resolution
reg[11:0] ver_front_porch	= VFP480;		// Vertical Front Porch

reg currentRes = 2'b10;
assign pixel_clock = clock_480p;
assign data_enable = hdmi_active;
reg hdmi_active;

reg[11:0] hor_pixel_count = 12'd0;	// Count the horizontal pixels				
reg[11:0] ver_pixel_count = 12'd0;	// Count the vertical pixels

/*
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
*/


always @(posedge(pixel_clock), negedge(reset)) begin: HorizontalPixelCounter
		if(!reset) begin
			hor_pixel_count <= 12'd0;
		end
		else if(start) begin
				if (hor_pixel_count >= hor_total) begin
					hor_pixel_count <= 12'd0;
				end
				else begin
					hor_pixel_count <= hor_pixel_count + 1'b1;
				end
			end
		else begin
			hor_pixel_count <= 12'd0;
		end
	end

always @(posedge(pixel_clock), negedge(reset)) begin: VerticalPixelCounter
		if(!reset) begin
			ver_pixel_count <= 12'd0;
		end
		else if(start)  begin
				if(hor_pixel_count >= hor_total) begin
						if(ver_pixel_count >= ver_total) begin
							ver_pixel_count <= 12'd0;
						end
						else begin
							ver_pixel_count <= ver_pixel_count + 1'b1;
						end
					end
				else begin
					ver_pixel_count <= ver_pixel_count;
				end
			end
		else begin
			ver_pixel_count <= 12'd0;
		end
	end	
always @(posedge(pixel_clock), negedge(reset))	begin: HorizontalSync 					
		if(!reset) begin
			horizontal_sync <= 1'b0;
		end
		else if(hor_pixel_count < hor_sync_len)	begin				
			horizontal_sync <= 1'b1;	
		end
		else begin
			horizontal_sync <= 1'b0;			
		end
	end
always @(posedge(pixel_clock), negedge(reset))	begin: VerticalSync						
		if(!reset) begin
			vertical_sync <= 1'b0;
		end
		else if(ver_pixel_count < ver_sync_len)	begin
			vertical_sync <= 1'b1;
		end
		else begin
			vertical_sync <= 1'b0;
		end
	end


always @(posedge(pixel_clock), negedge(reset)) begin: DataEnable
	if(!reset) begin
		hdmi_active <= 1'b0;
	end
	else if((hor_pixel_count >= (hor_sync_len + hor_back_porch)) && (hor_pixel_count <  (hor_sync_len + hor_back_porch + hor_resolution)) && (ver_pixel_count  >= (ver_sync_len  + ver_back_porch)) && (ver_pixel_count  <  (ver_sync_len  + ver_back_porch  + ver_resolution))) begin
		hdmi_active <= 1'b1;	// Data only enable between front and back porches
	end	 
	else begin
		hdmi_active <= 1'b0;	// Otherwise don't send data
	end
end




endmodule 
