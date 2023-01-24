/* Lab0
 * Register Read/Write Project 
 * Authors: Ryan Stracener, Patrick Laverty
 *
 * Requirements:
 * (FINISHED)   1. Writes should take effect synchronously on the rising edge of the clock and only when write enable is also asserted (active high).
 *              2. The register file read port should output the value of the selected register combinatorially.
 *              3. The output of the register file read port should change after a rising clock edge if the selected register was modified by a write on the clock edge.
 *              4. Reading register zero ($0) should always return (combinatorially) the value zero.
 *              5. Writing register zero has no effect.
 */

module regfile(
    input logic clk,
    input logic we3, // write enable
    input logic [4:0] ra1, ra2, wa3, // two 5-bit src regs, and 1 5-bit dest reg
    input logic [31:0] wd3, // write data
    output logic [31:0] rd1, rd2 // read 1 and 2
    );

    // a means address
    // d means data

    // logic [31:0] rf [31:0];
    logic [31:0] rf;

    always @(posedge clk) begin
        if(we3) begin
            rf[wa3] <= wd3; // Setting internal register to write data
            rd1 <= rf[ra1]; // Set output1 via address 1
            rd2 <= rf[ra2]; // Set output2 via address 2
        end
    end

    // three ported register file
    // read two ports combinationally
    // write third port on rising edge of clock
    // register 0 hardwired to 0
endmodule