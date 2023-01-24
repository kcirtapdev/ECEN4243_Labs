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

    regfile mut(
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
        // Read inputs
        ra1 = 5'd0;
        ra2 = 5'd0;

        // Write inputs
        we3 = 1'b1;
        wa3 = 5'd0;
        wd3 = 32'd0;

        // Clock (10MHz)
        clk = 1'b0;
        forever #50 clk = ~clk;
    end
    
    always @(posedge clk) begin
        // Randomize addresses
        ra1 = $urandom%32;
        ra2 = $urandom%32;
        wa3 = $urandom%32;

        // Randomize write data
        wd3 = $urandom;
    end

endmodule
