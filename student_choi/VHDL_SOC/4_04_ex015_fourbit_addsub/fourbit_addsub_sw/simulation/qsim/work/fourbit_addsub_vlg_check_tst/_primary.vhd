library verilog;
use verilog.vl_types.all;
entity fourbit_addsub_vlg_check_tst is
    port(
        addsub_num      : in     vl_logic_vector(4 downto 0);
        sampler_rx      : in     vl_logic
    );
end fourbit_addsub_vlg_check_tst;
