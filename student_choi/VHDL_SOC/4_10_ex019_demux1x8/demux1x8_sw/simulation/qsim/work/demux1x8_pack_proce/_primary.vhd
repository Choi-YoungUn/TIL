library verilog;
use verilog.vl_types.all;
entity demux1x8_pack_proce is
    port(
        I               : in     vl_logic;
        S               : in     vl_logic_vector(2 downto 0);
        Y               : out    vl_logic_vector(7 downto 0)
    );
end demux1x8_pack_proce;
