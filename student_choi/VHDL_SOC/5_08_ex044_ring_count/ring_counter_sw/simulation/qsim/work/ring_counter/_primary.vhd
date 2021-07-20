library verilog;
use verilog.vl_types.all;
entity ring_counter is
    port(
        reset           : in     vl_logic;
        clk             : in     vl_logic;
        q               : out    vl_logic_vector(3 downto 0)
    );
end ring_counter;
