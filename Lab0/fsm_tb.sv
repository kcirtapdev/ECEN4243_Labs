`timescale 1ns / 1ps
module fsm_tb ();

   logic  clock;
   logic  In;
   logic  reset_b;
   
   logic  Out;
   
   // Instantiate DUT
   fsm dut (Out, reset_b, clock, In);

   // Setup the clock to toggle every 1 time units 
   initial begin	
      clock = 1'b1;
      forever #5 clock = ~clock;
   end

   initial begin
      // Tells when to finish simulation
      #100 $finish;		
   end

   // Write data to console
   always @(posedge clock) begin
      $display("reset, in||out: %b, %b||%b", reset_b, In, Out);
   end
   
   initial begin      
      #0  reset_b = 1'b0;
      #12 reset_b = 1'b1; // -> S0	
      #0  In = 1'b0; // S0 -> S2
      #20 In = 1'b1; // S2 -> S2
      #20 In = 1'b0; // S2 -> S1
   end

endmodule // FSM_tb

