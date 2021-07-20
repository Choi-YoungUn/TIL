library verilog;
use verilog.vl_types.all;
entity onebitfullcomparator is
    port(
        Xo              : out    vl_logic;
        B               : in     vl_logic;
        A               : in     vl_logic;
        Yi              : in     vl_logic;
        Xi              : in     vl_logic;
        Yo              : out    vl_logic;
        Zo              : out    vl_logic;
        Zi              : in     vl_logic
    );
end onebitfullcomparator;
