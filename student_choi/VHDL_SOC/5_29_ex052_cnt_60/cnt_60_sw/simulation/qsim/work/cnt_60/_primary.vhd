library verilog;
use verilog.vl_types.all;
entity cnt_60 is
    port(
        nrst            : in     vl_logic;
        clk             : in     vl_logic;
        digit_ten       : out    vl_logic_vector(3 downto 0);
        digit_one       : out    vl_logic_vector(3 downto 0);
        carry           : out    vl_logic
    );
end cnt_60;
