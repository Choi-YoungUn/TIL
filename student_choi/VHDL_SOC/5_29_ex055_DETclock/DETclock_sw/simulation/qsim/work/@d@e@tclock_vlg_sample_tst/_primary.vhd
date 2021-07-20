library verilog;
use verilog.vl_types.all;
entity DETclock_vlg_sample_tst is
    port(
        clk             : in     vl_logic;
        key_hor         : in     vl_logic;
        key_min         : in     vl_logic;
        key_sec         : in     vl_logic;
        nrst            : in     vl_logic;
        sel_sw          : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end DETclock_vlg_sample_tst;
