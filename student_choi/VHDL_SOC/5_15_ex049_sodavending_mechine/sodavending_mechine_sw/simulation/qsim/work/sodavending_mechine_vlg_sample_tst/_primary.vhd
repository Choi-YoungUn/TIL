library verilog;
use verilog.vl_types.all;
entity sodavending_mechine_vlg_sample_tst is
    port(
        coin            : in     vl_logic_vector(1 downto 0);
        reset           : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end sodavending_mechine_vlg_sample_tst;
