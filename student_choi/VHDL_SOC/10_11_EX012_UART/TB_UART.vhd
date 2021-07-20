library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity TB_UART is  end ;
   
architecture BEH of TB_UART is
   
   component  UART_TX is
  port (
    nRst      : in std_logic;
    clk       : in std_logic;
    start_sig : in std_logic;
    data      : in std_logic_vector(7 downto 0);
    tx        : out std_logic;
    busy      : out std_logic
  );
   end component;
   
   component  UART_RX is
  port (
    nRst      : in std_logic;
    clk       : in std_logic;
    serialin  : in std_logic;
   rx_data   : out std_logic_vector(7 downto 0);
    valid     : out std_logic
  );
   end component;
     
     signal signRst, sigclk, sigstart_sig : std_logic;
     signal sigdata : std_logic_vector(7 downto 0);
     signal sig_data : std_logic;
     signal int_cnt : std_logic_vector(99 downto 0);
     signal sigvalid : std_logic;
     signal sigbusy : std_logic;
     signal sigrx_data : std_logic_vector(7 downto 0);
          
 begin
   
   process
   begin
     if(NOW = 0 ns) then
      signRst <= '0', '1' after 10 us;
    end if;
      wait for 1 sec;
      end process;
      
      process
   begin
      sigclk <= '0', '1' after 5 ns;
      wait for 10 ns;
      end process;
      
      process(signRst, sigclk)
        begin
          if(signRst = '0') then
          int_cnt <= (others => '0');
        elsif(rising_edge(sigclk)) then
        int_cnt <= int_cnt + 1;
      end if;
    end process;
        
      
      sigstart_sig <= '1'when int_cnt = 500 else
      '0';
      sigdata <= "10100111" when ((int_cnt > 450)and(int_cnt < 550)) else
            "00000000";
      
  u_TB_UART_TX : UART_TX
  port map(
    nRst      => signRst,
    clk       => sigclk,
    start_sig => sigstart_sig, 
    data      => sigdata,
    tx        => sig_data,
    busy      => sigbusy
  );
   
  u_TB_UART_RX : UART_RX
   port map (
    nRst      => signRst,
   clk       => sigclk,
   serialin  => sig_data,
    rx_data   => sigrx_data,
    valid     => sigvalid
  );
   
end BEH;
