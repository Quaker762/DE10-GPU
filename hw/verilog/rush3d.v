/**
 *	Top Level Entity for the Rush3D OpenGL Chip
 */
module Rush3D
(
	input clk_ref, // Input reference clock (50MHz)
	input btn_reset,
	input btn_begin,
	input [7:0] switch_color_bits,
	input [1:0] switch_change_res,
	input btn_set_color,
	input btn_switch_color,
	
	
	// Should this be a part of the VGA controller module???
	output [7:0] dac_red_pins,
	output [7:0] dac_green_pins,
	output [7:0] dac_blue_pins,
	
	output vga_pixel_clock,	// Pixel Clock 40MHz
	output dac_sync_n,
	output dac_blank_n,  
	output hsync,
	output vsync,
	output [7:0] led_color_bits,
	output [6:0] segment_leds
);

PixelPLL vga_pll800// PLL 40MHz Pixel Clock Generator (800*600@60p)
(
.refclk(clk_ref),
.rst(1'b0), 
.outclk_0(vga_pixel_clock800)
);

PixelPLL vga_pll640// PLL 25.175MHz Pixel Clock Generator (640*480@60p)
(
.refclk(clk_ref),
.rst(1'b0), 
.outclk_1(vga_pixel_clock640)
);

PixelPLL vga_pll1024// PLL 65MHz Pixel Clock Generator (1024*768@60p)
(
.refclk(clk_ref),
.rst(1'b0), 
.outclk_2(vga_pixel_clock1024)
);


VGAController vga_ctrl
(
	.pixel_clock800(vga_pixel_clock800),
	.pixel_clock640(vga_pixel_clock800),
	.pixel_clock1024(vga_pixel_clock1024),
	.switch_res(switch_change_res),
	.reset_n(btn_reset),
	.beg(btn_begin),
	
	.hsync(hsync),
	.vsync(vsync),
	.dac_sync_pin_n(dac_sync_n),
	.dac_blank_pin_n(dac_blank_n)
);

reg [7:0] RED_reg = 8'hFF;
reg [7:0] GREEN_reg = 8'h00;
reg [7:0] BLUE_reg = 8'hde;
reg [1:0] current_Colour = 2'd1;
reg [7:0] LED_reg = 8'hAA;
reg [6:0] segment_reg = 7'h00;

assign segment_leds = segment_reg;
assign led_color_bits = LED_reg;
assign dac_red_pins = RED_reg;
assign dac_green_pins = GREEN_reg;
assign dac_blue_pins = BLUE_reg;

always @(negedge(btn_switch_color), negedge(btn_set_color)) begin: colourSwitch
	if (!btn_set_color) begin
		case(current_Colour)
			2'd1 : RED_reg = switch_color_bits;
			2'd2 : GREEN_reg = switch_color_bits;
			2'd3 : BLUE_reg = switch_color_bits;
			2'd0 : ;
		endcase
	end
	else if (!btn_switch_color) begin
		case(current_Colour)
			2'd1 : current_Colour = 2'd2;
			2'd2 : current_Colour = 2'd3;
			2'd3 : current_Colour = 2'd1;
			2'd0 : current_Colour = 2'd1;
		endcase
	end
	else begin
	end	
	case(current_Colour)
		2'd1 : begin LED_reg = RED_reg; segment_reg = 7'h2f; end
		2'd2 : begin LED_reg = GREEN_reg; segment_reg = 7'h10; end
		2'd3 : begin LED_reg = BLUE_reg; segment_reg = 7'h03; end
		2'd0 : LED_reg = LED_reg;
	endcase
end

endmodule 