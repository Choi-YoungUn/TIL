library verilog;
use verilog.vl_types.all;
entity sodavending_mechine is
    port(
        coin            : in     vl_logic_vector(1 downto 0);
        reset           : in     vl_logic;
        coffee          : out    vl_logic;
        sevensgzero     : out    vl_logic_vector(6 downto 0);
        sevensgten      : out    vl_logic_vector(6 downto 0);
        sevensghund     : out    vl_logic_vector(6 downto 0)
    );
end sodavending_mechine;
