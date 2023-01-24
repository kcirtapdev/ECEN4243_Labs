`timescale 1ns / 1ps

module regfile_tb;

    // Inputs
    reg clk;
    reg we3;
    reg [4:0] ra1;
    reg [4:0] ra2;
    reg [4:0] wa3;
    reg [31:0] wd3;

    // Outputs
    wire [31:0] rd1;
    wire [31:0] rd2;

    divider mut(
        // Inputs
        .clk(clk),
        .we3(we3),
        .ra1(ra1),
        .ra2(ra2),
        .wa3(wa3),
        .wd3(wd3),

        // Outputs
        .rd1(rd1),
        .rd2(rd2)
    );

    initial begin
        clk = 0;
        we3 = 0;

    end

endmodule