library verilog;
use verilog.vl_types.all;
entity eitbit_par_register_vlg_sample_tst is
    port(
        clk             : in     vl_logic;
        data            : in     vl_logic_vector(7 downto 0);
        en              : in     vl_logic;
        rset            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end eitbit_par_register_vlg_sample_tst;
