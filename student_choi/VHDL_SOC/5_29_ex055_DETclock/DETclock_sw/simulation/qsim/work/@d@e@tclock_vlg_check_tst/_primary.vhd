library verilog;
use verilog.vl_types.all;
entity DETclock_vlg_check_tst is
    port(
        fnd_hor_one     : in     vl_logic_vector(6 downto 0);
        fnd_hor_ten     : in     vl_logic_vector(6 downto 0);
        fnd_min_one     : in     vl_logic_vector(6 downto 0);
        fnd_min_ten     : in     vl_logic_vector(6 downto 0);
        fnd_sec_one     : in     vl_logic_vector(6 downto 0);
        fnd_sec_ten     : in     vl_logic_vector(6 downto 0);
        sampler_rx      : in     vl_logic
    );
end DETclock_vlg_check_tst;
