library verilog;
use verilog.vl_types.all;
entity demux1x8_pack_proce_vlg_check_tst is
    port(
        Y               : in     vl_logic_vector(7 downto 0);
        sampler_rx      : in     vl_logic
    );
end demux1x8_pack_proce_vlg_check_tst;
