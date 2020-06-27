module framebuffer_read
(
    input wire clock,
    input wire reset_n,
    output reg [28:0] address,
    output wire [7:0] burstcount,
    input wire waitrequest,
    input wire [63:0] readdata,
    input wire readdatavalid,
    output reg read,
    output reg [63:0] writedata,
    output wire [7:0] byteenable,
    output reg write,
	 
	 output reg [31:0] data,
	 output wire [7:0] leds,
	 input wire pixel_clock,
	 input wire sync
);

// State machine.
localparam STATE_INIT = 4'h0;
localparam STATE_WRITE_START1 = 4'h1;
localparam STATE_WRITE_WAIT1 = 4'h2;
localparam STATE_WRITE_START2 = 4'h3;
localparam STATE_WRITE_WAIT2 = 4'h4;
localparam STATE_READ_START1 = 4'h6;
localparam STATE_READ_WAIT1 = 4'h7;
localparam STATE_HDMI_WAIT1 = 4'h8;
localparam STATE_READ_START2 = 4'h9;
localparam STATE_READ_WAIT2 = 4'hA;
localparam STATE_HDMI_WAIT2 = 4'hB;
localparam STATE_DONE = 4'hC;
reg [3:0] state;

assign leds[3:0] = state;
assign leds[5:4] = buffer;
//assign leds[4] = read;
assign leds[6] = waitrequest;
assign leds[7] = readdatavalid;

// Registers and assignments.
assign burstcount = 8'h01;
assign byteenable = 8'hFF;
reg [127:0] data_buffer;
reg [28:0] current_address;
reg [15:0] pixel_count = 0;
reg [3:0] buffer = 4'h0;
// 1G minus 128M, in 64-bit units:
// This ends up writing to 0x38000000 in actual memory space.

localparam TEST_ADDRESS = 29'h0700_0000;
//localparam TEST_ADDRESS = 29'h0000_0000;

always @(posedge clock or negedge reset_n) begin
    if (!reset_n) begin
        state <= STATE_INIT;
        address <= 29'h0;
        read <= 1'b0;
        writedata <= 64'h0;
        write <= 1'b0;
    end else begin
        case (state)
            STATE_INIT: begin
                // Dummy state to start.
                state <= STATE_WRITE_START1;
                //data <= 64'h0000_0000_00FF_0000;
					// data2 <= 64'h2357_1113_1719_2329;
					 current_address <=  29'h0700_0000;
            end

            STATE_WRITE_START1: begin
                // Initiate a write.
                address <= current_address;
                //writedata <= 64'hDEAD_BEEF_CAFE_BABE;
					 writedata <= 64'hFFFF_FFFF_FFFF_FFFF;
                write <= 1;
                state <= STATE_WRITE_WAIT1;
            end

            STATE_WRITE_WAIT1: begin
                // Wait until we're not requested to wait.
                if (!waitrequest) begin
                    address <= 29'h0;
                    writedata <= 64'h0;
                    write <= 1'b0;
                    state <= STATE_WRITE_START2;
                end
            end
				STATE_WRITE_START2: begin
                // Initiate a write.
                address <= current_address + 1'h1;
                //writedata <= 64'hDEAD_BEEF_CAFE_BABE;
					 writedata <= 64'hFFFF_FFFF_FFFF_FFFF;
                write <= 1;
                state <= STATE_WRITE_WAIT2;
            end

            STATE_WRITE_WAIT2: begin
                // Wait until we're not requested to wait.
                if (!waitrequest) begin
                    address <= 29'h0;
                    writedata <= 64'h0;
                    write <= 1'b0;
                    state <= STATE_READ_START1;
                end
            end
				
				STATE_READ_START1: begin
                // Initiate a read.
                address <= current_address;
                read <= 1'b1;
                state <= STATE_READ_WAIT1;
            end

            STATE_READ_WAIT1: begin
                // When no longer told to wait, deassert the request lines.
                if (!waitrequest) begin
                    address <= 29'h0;
                    read <= 1'b0;
                end

                // If we have data, grab it and we're done.
                if (readdatavalid) begin
                    data_buffer[63:0] <= readdata;
						  //data <= data_buffer[63:0];
						  if(current_address < 29'h0700_0001)
								current_address <= current_address + 1'h1;
							else
								current_address <= 29'h0700_0000;
						  state <= STATE_HDMI_WAIT1; 
                end
            end
				
				STATE_HDMI_WAIT1: begin
				
				//	if(sync) begin
				//		current_address <= 29'h0700_0000;
				//	end
				
				//	if(buffer == 4'h2 || buffer == 4'h3) begin
			//			state <= STATE_HDMI_WAIT1;
			//		end else begin
						state <= STATE_READ_START2;
			//		end
				end
				
				STATE_READ_START2: begin
                // Initiate a read.
                address <= current_address;
                read <= 1'b1;
                state <= STATE_READ_WAIT2;
            end

            STATE_READ_WAIT2: begin
                // When no longer told to wait, deassert the request lines.
                if (!waitrequest) begin
                    address <= 29'h0;
                    read <= 1'b0;
                end

                // If we have data, grab it and we're done.
                if (readdatavalid) begin
                    data_buffer[127:64] <= readdata;
						  //data <= data_buffer[127:64];
						  if(current_address < 29'h0700_0001)
								current_address <= current_address + 1'h1;
							else
								current_address <= 29'h0700_0000;
						  state <= STATE_HDMI_WAIT2;
                end
            end
				
				STATE_HDMI_WAIT2: begin
				
				//	if(sync) begin
				//		current_address <= 29'h0700_0000;
				//	end
				
					//if(buffer == 4'h0 || buffer == 4'h1) begin
					//	state <= STATE_HDMI_WAIT2;
				//	end else begin
						state <= STATE_READ_START1;
				//	end
				end
				
            STATE_DONE: begin
                // Nothing, stay here.
            end

            default: begin
                // Bug. Just restart.
                state <= STATE_INIT;
            end
        endcase
	/*	  
		  case(pixel_count)
			16'd0: begin
				data <= 32'h0000_00FF;
			end
			16'd240: begin
				data <= 32'h00FF_FFFF;
			end		
			default: begin
			
			end
		endcase
		*/
	end
	

end

always @(negedge pixel_clock) begin
////	if(!sync) begin
	//	pixel_count <= 4'h0;
//	end else begin
	//	if(pixel_count < 16'd525) begin
	//		pixel_count <= pixel_count + 4'h1;
	//	end else begin
	//		pixel_count <= 4'h0;
	//	end
//	end
	case(buffer)
		4'h0: begin
			buffer <= 4'h1;
			data <= data_buffer[31:0];
		end
		4'h1: begin
			buffer <= 4'h2;
			data <= data_buffer[63:32];
		end
		4'h2: begin
			buffer <= 4'h3;
			data <= data_buffer[95:64];
		end
		4'h3: begin
			buffer <= 4'h0;
			data <= data_buffer[127:96];
		end
	endcase

end		


endmodule
