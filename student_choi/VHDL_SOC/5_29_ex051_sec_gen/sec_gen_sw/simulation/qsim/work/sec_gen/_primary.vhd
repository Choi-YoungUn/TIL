library verilog;
use verilog.vl_types.all;
entity sec_gen is
    port(
        nrst            : in     vl_logic;
        clk             : in     vl_logic;
        sec_sig         : out    vl_logic
    );
end sec_gen;
