library verilog;
use verilog.vl_types.all;
entity fourbit_addsub is
    port(
        addsub_a        : in     vl_logic_vector(3 downto 0);
        addsub_b        : in     vl_logic_vector(3 downto 0);
        Msign           : in     vl_logic;
        addsub_num      : out    vl_logic_vector(4 downto 0)
    );
end fourbit_addsub;
