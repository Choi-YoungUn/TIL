library verilog;
use verilog.vl_types.all;
entity eittothreeencoder is
    port(
        A               : in     vl_logic_vector(7 downto 0);
        Yo              : out    vl_logic_vector(2 downto 0)
    );
end eittothreeencoder;
