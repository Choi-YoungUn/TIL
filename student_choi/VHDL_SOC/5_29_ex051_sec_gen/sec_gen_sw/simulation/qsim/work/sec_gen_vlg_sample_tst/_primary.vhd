library verilog;
use verilog.vl_types.all;
entity sec_gen_vlg_sample_tst is
    port(
        clk             : in     vl_logic;
        nrst            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end sec_gen_vlg_sample_tst;
