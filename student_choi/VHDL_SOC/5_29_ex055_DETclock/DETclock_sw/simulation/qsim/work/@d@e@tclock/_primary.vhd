library verilog;
use verilog.vl_types.all;
entity DETclock is
    port(
        nrst            : in     vl_logic;
        clk             : in     vl_logic;
        key_sec         : in     vl_logic;
        key_min         : in     vl_logic;
        key_hor         : in     vl_logic;
        sel_sw          : in     vl_logic;
        fnd_sec_ten     : out    vl_logic_vector(6 downto 0);
        fnd_sec_one     : out    vl_logic_vector(6 downto 0);
        fnd_min_ten     : out    vl_logic_vector(6 downto 0);
        fnd_min_one     : out    vl_logic_vector(6 downto 0);
        fnd_hor_ten     : out    vl_logic_vector(6 downto 0);
        fnd_hor_one     : out    vl_logic_vector(6 downto 0)
    );
end DETclock;
