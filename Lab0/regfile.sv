/* Lab0
 * Register Read/Write Project 
 * Authors: Ryan Stracener, Patrick Laverty
 *
 * -----------------------------------------------------
 *
 * Requirements:
 * (FINISHED)   1. Writes should take effect synchronously on the rising edge of the clock and only when write enable is also asserted (active high).
 * (Finished)   2. The register file read port should output the value of the selected register combinatorially.
 * (Finished)   3. The output of the register file read port should change after a rising clock edge if the selected register was modified by a write on the clock edge.
 * (Finished)   4. Reading register zero ($0) should always return (combinatorially) the value zero.
 * (Finished)   5. Writing register zero has no effect.
 *
 * -----------------------------------------------------
 *
 * Variable naming:
 * `a` means address
 * `d` means data
 */

module regfile(
    input clk,
    input we3, // write enable
    input [4:0] ra1, ra2, wa3, // two 5-bit src regs, and one 5-bit dest reg
    input [31:0] wd3, // write data
    output [31:0] rd1, rd2 // read 1 and 2
    );

    // Internal memory
    reg [31:0] rf [31:0];

    // Set read ports to value, unless address is 0
    assign rd1 = (ra1 == 5'd0) ? 32'd0 : rf[ra1];
    assign rd2 = (ra2 == 5'd0) ? 32'd0 : rf[ra2];

    always @(posedge clk) begin
        if(we3 && wa3 != 5'd0) begin
            rf[wa3] <= wd3; // Set internal memory to "write data"
        end
    end
endmodule
