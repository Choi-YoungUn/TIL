library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity tb_ps2_keybord is  end ;
   
architecture BEH of tb_ps2_keybord is
   
   component  ps2_keybord is
   port(
     nRst : in std_logic;
     clk : in std_logic;
     start_sig : in std_logic;
     data : in std_logic_vector(7 downto 0);
     ps2_clk : out std_logic;
     ps2_data : out std_logic
   );    
   end component;
   
   component  ps2_receiver is
   port (
     nRst : in std_logic;
     clk : in std_logic;
     ps2_clk : in std_logic;
     ps2_data : in std_logic;
     valid : out std_logic;
     received_data : out std_logic_vector(7 downto 0)
   );
   end component;
     
     signal signRst, sigclk, sigstart_sig : std_logic;
     signal sigdata : std_logic_vector(7 downto 0);
     signal sigps2_clk, sigps2_data : std_logic;
     signal int_cnt : std_logic_vector(99 downto 0);
     signal sigvalid : std_logic;
     signal sigreceived_data : std_logic_vector(7 downto 0);
          
 begin
   
   process
   begin
     if(NOW = 0 ns) then
      signRst <= '0', '1' after 100 us;
    end if;
      wait for 1 sec;
      end process;
      
      process
   begin
      sigclk <= '0', '1' after 5 ns;
      wait for 10ns;
      end process;
      
      process(signRst, sigclk)
        begin
          if(signRst = '0') then
          int_cnt <= (others => '0');
        elsif(rising_edge(sigclk)) then
        int_cnt <= int_cnt + 1;
      end if;
    end process;
        
      
      sigstart_sig <= '1'when int_cnt = 200 else
      '0';
      sigdata <= "00100011" when ((int_cnt > 150)and(int_cnt < 250)) else
            "00000000";
      
  u_tb_ps2_keybord : ps2_keybord
  port map(
     nRst => signRst,
     clk => sigclk,
     start_sig => sigstart_sig,
     data => sigdata,
     ps2_clk => sigps2_clk,
     ps2_data => sigps2_data
   );
   
   u_tb_ps2_receiver : ps2_receiver
   port map(
     nRst => signRst,
     clk => sigclk,
     ps2_clk => sigps2_clk,
     ps2_data => sigps2_data, 
     valid => sigvalid,
     received_data => sigreceived_data
   );
   
end BEH;