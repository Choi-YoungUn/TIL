library verilog;
use verilog.vl_types.all;
entity fourbit_addsub_vlg_sample_tst is
    port(
        addsub_a        : in     vl_logic_vector(3 downto 0);
        addsub_b        : in     vl_logic_vector(3 downto 0);
        Msign           : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end fourbit_addsub_vlg_sample_tst;
