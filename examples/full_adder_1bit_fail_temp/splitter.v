// Adapted from TimEx generated files for vcd_assert testing
`ifndef begin_time
`define begin_time 8
`endif

`timescale 1ps/100fs

module basic_splitter (in, out1, out2);

// Define inputs
input in;

// Define outputs
output out1, out2;
wire out1, out2;

// Define internal output variables
reg internal_out1, internal_out2;
assign out1 = internal_out1;
assign out2 = internal_out2;

// Single state
integer state;
wire internal_state_0;
assign internal_state_0 = state === 0;

specify
    // Output delays spec params
    specparam delay_state0_in_out1 = 5.0;
    specparam delay_state0_in_out2 = 5.0;

    // No critical timing spec params

    // Define output delays
    (in => out1) = delay_state0_in_out1;
    (in => out2) = delay_state0_in_out2;

    // No critical timings assertions

endspecify

initial begin
    // No state
    internal_out1 = 0;
    internal_out2 = 0;
end

always @(posedge in or negedge in)
if($time > `begin_time) begin
    internal_out1 = !internal_out1;
    internal_out2 = !internal_out2;
end

endmodule
