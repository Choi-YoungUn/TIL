library verilog;
use verilog.vl_types.all;
entity cnt_60_vlg_sample_tst is
    port(
        clk             : in     vl_logic;
        nrst            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end cnt_60_vlg_sample_tst;
