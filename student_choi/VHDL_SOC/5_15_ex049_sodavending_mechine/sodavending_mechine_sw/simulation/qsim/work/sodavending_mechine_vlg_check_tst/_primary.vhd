library verilog;
use verilog.vl_types.all;
entity sodavending_mechine_vlg_check_tst is
    port(
        coffee          : in     vl_logic;
        sevensghund     : in     vl_logic_vector(6 downto 0);
        sevensgten      : in     vl_logic_vector(6 downto 0);
        sevensgzero     : in     vl_logic_vector(6 downto 0);
        sampler_rx      : in     vl_logic
    );
end sodavending_mechine_vlg_check_tst;
