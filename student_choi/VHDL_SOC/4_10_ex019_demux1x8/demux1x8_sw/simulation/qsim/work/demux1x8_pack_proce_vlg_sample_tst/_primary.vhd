library verilog;
use verilog.vl_types.all;
entity demux1x8_pack_proce_vlg_sample_tst is
    port(
        I               : in     vl_logic;
        S               : in     vl_logic_vector(2 downto 0);
        sampler_tx      : out    vl_logic
    );
end demux1x8_pack_proce_vlg_sample_tst;
