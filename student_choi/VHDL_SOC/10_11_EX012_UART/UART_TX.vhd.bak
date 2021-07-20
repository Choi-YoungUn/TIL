library ieee;
    use ieee.std_logic_1164.all;
    use ieee.std_logic_arith.all;
    use ieee.std_logic_unsigned.all;
    
entity UART_TX is
  port (
    nRst      : in std_logic;
    clk       : in std_logic;
    start_sig : in std_logic;
    data      : in std_logic_vector(7 downto 0);
    tx        : out std_logic;
    busy      : out std_logic
  );
end UART_TX;

architecture beh of UART_TX is
    
    type   state_type is (IDLE, START, SEND, PARITY, STOP);
    signal state      : state_type;
    signal cnt        : std_logic_vector(8 downto 0);
    signal pclk       : std_logic;
    signal start_d    : std_logic;
    signal flag       : std_logic;
    signal temp_data  : std_logic_vector(7 downto 0);
    signal tx_data    : std_logic_vector(7 downto 0);
    signal bit_cnt    : std_logic_vector(3 downto 0);
    
begin
  
    process(nRst, clk)
    begin
      if(nRst = '0') then
           start_d    <= '0';
           flag       <= '0';
           temp_data  <= (others => '0');
         elsif rising_edge(clk) then
           start_d <= start_sig;
           if(start_d = '0')and (start_sig = '1') then
              flag      <= '1';
              temp_data <= data;
           elsif (state = START) then
              flag      <= '0';
           end if;
      end if;
    end process;
    
    process(nRst, clk)
    begin
       if(nRst = '0') then
           cnt <= (others => '0');
           pclk <= '0';
         elsif rising_edge(clk) then
            if(cnt = 433) then
            cnt <= (others => '0');
            pclk <= not pclk;
          else
            cnt <= cnt + 1;
          end if;
       end if;
  end process;
  
   process(nRst, pclk)
   begin
      if(nRst = '0')then
         state   <= IDLE;
         bit_cnt <= (others => '0');
         tx_data <= (others => '0');
         busy  <= '1';
       elsif rising_edge(pclk) then
         case state is
         when IDLE =>
           if(flag = '1') then
               state <= START;
           else
               state <= IDLE;
         end if;
           bit_cnt <= (others => '0');
           tx_data <= (others => '0');
           busy    <= '1';
        when START =>
           state <= SEND;
           tx_data <= temp_data;
           busy    <= '0';
        when SEND =>
           if(bit_cnt = 7) then
              bit_cnt <= (others => '0');
              state <= PARITY;
           else
              bit_cnt <= bit_cnt + 1;
              tx_data <= '0' & tx_data(7 downto 1);
            end if;
        when PARITY =>
           state <= STOP;
        when STOP =>
           state <= IDLE;
           busy <= '1';
        when others =>
        end case;
      end if;
    end process;
    
    tx <= tx_data(0) when state = SEND else
    '0' when state = START or state = PARITY else
    '1';
end beh;