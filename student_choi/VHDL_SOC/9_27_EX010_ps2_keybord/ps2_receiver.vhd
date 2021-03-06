library ieee;
   use ieee.std_logic_1164.all;
   use ieee.std_logic_arith.all;
   use ieee.std_logic_unsigned.all;
   
 entity ps2_receiver is
   port (
     nRst : in std_logic;
     clk : in std_logic;
     ps2_clk : in std_logic;
     ps2_data : in std_logic;
     valid : out std_logic;
     received_data : out std_logic_vector(7 downto 0)
   );
 end ps2_receiver;
 
architecture beh of ps2_receiver is
   
    type state_type is(IDLE, START, RECEIVE, PARITY, STOP);
    signal state : state_type;
    signal ps2_clk_d : std_logic;
    signal ps2_clk_det : std_logic;
    signal ps2_data_d : std_logic;
    signal ps2_data_det : std_logic;
    signal bit_cnt : std_logic_vector(2 downto 0);
    signal temp_data : std_logic_vector(7 downto 0);
    
begin

     process(nRst, clk)
       begin
         if(nRst = '0') then
        ps2_clk_d <= '0';
        ps2_clk_det <= '0';
        ps2_data_d <= '0';
        ps2_data_det <= '0';
       elsif rising_edge(clk) then
       ps2_clk_d <= ps2_clk;
       ps2_data_d <= ps2_data;
         if( ps2_clk_d = '0')and(ps2_clk = '1') then
         ps2_clk_det <= '1';
       else
         ps2_clk_det <= '0';
       end if;
       if(ps2_data_d = '1')and(ps2_data = '0')then
       ps2_data_det <= '1';
     else
       ps2_data_det <= '0';
     end if;
   end if;
 end process;    
   
   process(nRst,clk)
     begin
       if(nRst = '0') then
       state <= IDLE;
       bit_cnt  <= (others => '0'); 
       temp_data <= (others => '0');
       received_data  <= (others => '0');
       valid <= '0';
     elsif rising_edge(clk) then
       case state is
     when IDLE =>
       if (ps2_data_det = '1') then
         state <= START;
       else
         state <= IDLE;
       end if;
     bit_cnt <= (others => '0');
     temp_data <= (others => '0');
     received_data  <= (others => '0');
     valid <= '0';
   when START =>
     if(ps2_clk_det = '1') then
     state <= RECEIVE;
   else
     state <= START;
   end if;
 when RECEIVE =>
   if(ps2_clk_det = '1')then
       if(bit_cnt = 7) then
       bit_cnt <= (others => '0');
       state <= PARITY;
       else 
       bit_cnt <= bit_cnt + 1;
       state <= RECEIVE;
 end if;
 temp_data <= ps2_data & temp_data(7 downto 1);
 else
   state <= RECEIVE;
 end if;
 when PARITY =>
   if(ps2_clk_det = '1')then
   state <= STOP;
 else
   state <= PARITY;
 end if;
 
 when STOP =>
   if(ps2_clk_det = '1') then
   state <= IDLE;
 else
   state <= STOP;
 end if;
   received_data <= temp_data;
   valid <= '1';
 when others =>
   state <= IDLE;
 end case;
 end if;
 end process;
 
 end beh;
