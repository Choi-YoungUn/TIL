library verilog;
use verilog.vl_types.all;
entity eitbit_par_register is
    port(
        rset            : in     vl_logic;
        en              : in     vl_logic;
        clk             : in     vl_logic;
        data            : in     vl_logic_vector(7 downto 0);
        q               : out    vl_logic_vector(7 downto 0)
    );
end eitbit_par_register;
