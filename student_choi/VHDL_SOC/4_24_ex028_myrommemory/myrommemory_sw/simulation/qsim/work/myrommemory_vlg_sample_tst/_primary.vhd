library verilog;
use verilog.vl_types.all;
entity myrommemory_vlg_sample_tst is
    port(
        addr            : in     vl_logic_vector(2 downto 0);
        sampler_tx      : out    vl_logic
    );
end myrommemory_vlg_sample_tst;
