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
    
    integer i;
    integer prev_data = 0;
    integer fail_count = 0;
    initial begin
        for(i = 1; i < 32; i++) begin
            @(posedge clk);
            ra1 = i;
            ra2 = i;
            wa3 = i;
            wd3 = $urandom;
                        
            if(rd1 == prev_data && rd2 == prev_data) begin
                $display("Addr: 0x%h -- 0x%h = 0x%h = 0x%h -- PASSED", wa3, rd1, rd2, prev_data);
            end else begin
                $display("Addr: 0x%h -- 0x%h = 0x%h = 0x%h -- FAILED", wa3, rd1, rd2, prev_data);
                fail_count++;
            end
            
            prev_data = wd3;
        end
        
        // Print test results
        if(fail_count > 0) begin
            $display("FAILED: there were %d failers", fail_count);
        end else begin
            $display("PASSED!");
        end
    end

endmodule
