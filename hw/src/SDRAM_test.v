
// Simple test of the SDRAM interface.

module SDRAM_test(
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
    output reg write
);

// State machine.
localparam STATE_INIT = 4'h0;
localparam STATE_WRITE_START = 4'h1;
localparam STATE_WRITE_WAIT = 4'h2;
localparam STATE_READ_START = 4'h3;
localparam STATE_READ_WAIT = 4'h4;
localparam STATE_DONE = 4'h5;
reg [3:0] state;

// Registers and assignments.
assign burstcount = 8'h01;
assign byteenable = 8'hFF;
reg [63:0] data;
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
                state <= STATE_WRITE_START;
                data <= 64'h2357_1113_1719_2329;
            end

            STATE_WRITE_START: begin
                // Initiate a write.
                address <= TEST_ADDRESS;
                writedata <= 64'hDEAD_BEEF_CAFE_BABE;
                write <= 1;
                state <= STATE_WRITE_WAIT;
            end

            STATE_WRITE_WAIT: begin
                // Wait until we're not requested to wait.
                if (!waitrequest) begin
                    address <= 29'h0;
                    writedata <= 64'h0;
                    write <= 1'b0;
                    state <= STATE_READ_START;
                end
            end

            STATE_READ_START: begin
                // Initiate a read.
                address <= TEST_ADDRESS;
                read <= 1'b1;
                state <= STATE_READ_WAIT;
            end

            STATE_READ_WAIT: begin
                // When no longer told to wait, deassert the request lines.
                if (!waitrequest) begin
                    address <= 29'h0;
                    read <= 1'b0;
                end

                // If we have data, grab it and we're done.
                if (readdatavalid) begin
                    data <= readdata;
                    state <= STATE_DONE;
                end
            end

            STATE_DONE: begin
                // Nothing, stay here.
            end

            default: begin
                // Bug. Just restart.
                state <= STATE_INIT;
            end
        endcase
    end
end

endmodule

