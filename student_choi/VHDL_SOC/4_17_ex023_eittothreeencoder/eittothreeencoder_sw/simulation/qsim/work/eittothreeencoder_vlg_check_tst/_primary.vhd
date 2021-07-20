library verilog;
use verilog.vl_types.all;
entity eittothreeencoder_vlg_check_tst is
    port(
        Yo              : in     vl_logic_vector(2 downto 0);
        sampler_rx      : in     vl_logic
    );
end eittothreeencoder_vlg_check_tst;
