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
   
   component data_parsing is
   port(
      nRst : in std_logic;                             
      clk : in std_logic;
      in_data : in std_logic_vector(7 downto 0);
      valid : in std_logic;
      write_s : out std_logic;
      read_s : out std_logic;
      address : out std_logic_vector(7 downto 0);
      data : out std_logic_vector(7 downto 0)
   );
 end component;
 
   component register_map is
    port(
        nRst              : in std_logic;
        clk               : in std_logic;

        uart_write        : in std_logic;
        uart_read         : in std_logic;
        uart_address      : in std_logic_vector(7 downto 0);
        uart_data         : in std_logic_vector(7 downto 0);
        
        trans_write       : out std_logic;
        trans_read        : out std_logic;
        trans_address     : out std_logic_vector(7 downto 0);
        trans_data        : out std_logic_vector(7 downto 0);
        
        reg0              : out std_logic_vector(7 downto 0); -- led  r0~r7
        reg1              : out std_logic_vector(7 downto 0); -- led  r8~r15 
        reg2              : out std_logic_vector(7 downto 0); -- led  g0~g7
        
        reg3              : in std_logic_vector(7 downto 0); -- led sw0~ sw7
        reg4              : in std_logic_vector(7 downto 0)  -- led sw8~ sw15
        );
  end component;
  
  component load_tx_data is
   port(
      nRst : in std_logic;
      clk : in std_logic;
      write : in std_logic;
      read : in std_logic;
      address : in std_logic_vector(7 downto 0);
      data : in std_logic_vector(7 downto 0);
      busy : in std_logic;
      start_sig : out std_logic;
      tx_data : out std_logic_vector(7 downto 0)
   );
 end component;
     
     signal signRst, sigclk, sigstart_sig : std_logic;
     signal sigdata : std_logic_vector(7 downto 0);
     signal sig_data : std_logic;
     signal int_cnt : std_logic_vector(99 downto 0);
     signal sigvalid : std_logic;
     signal sigbusy : std_logic;
     signal sigrx_data : std_logic_vector(7 downto 0);
     
     signal rx_data_pasing : std_logic_vector(7 downto 0);
     signal valid_data_pasing : std_logic;  
     signal write_regi : std_logic; 
     signal read_regi : std_logic;
     signal address_regi : std_logic_vector(7 downto 0);
     signal data_regi : std_logic_vector(7 downto 0);
    
     signal reg0_map : std_logic_vector(7 downto 0);
     signal reg1_map : std_logic_vector(7 downto 0);
     signal reg2_map : std_logic_vector(7 downto 0);
     signal reg3_map : std_logic_vector(7 downto 0);
     signal reg4_map : std_logic_vector(7 downto 0);
     signal trans_w  : std_logic;
     signal trans_r  : std_logic;
     signal trans_add  : std_logic_vector(7 downto 0);
     signal trans_data : std_logic_vector(7 downto 0);
    
     signal start_sig_load : std_logic;
     signal tx_data_load   : std_logic_vector(7 downto 0);
    
     signal tx_end         : std_logic;
     signal busy_end       : std_logic;
          
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
        
      
      sigstart_sig <= '1'when int_cnt = 500 else     --w
                      '1'when int_cnt = 11000 else   --sp
                      '1'when int_cnt = 21500 else   --0
                      '1'when int_cnt = 32000 else   --x
                      '1'when int_cnt = 42500 else   --address
                      '1'when int_cnt = 53000 else   --address
                      '1'when int_cnt = 63500 else   --sp
                      '1'when int_cnt = 74000 else   --0
                      '1'when int_cnt = 84500 else   --x
                      '1'when int_cnt = 95000 else   --data
                      '1'when int_cnt = 105500 else   --data
                      '1'when int_cnt = 116000 else   --enter 
                      
                      '1'when int_cnt = 130000 else   --r
                      '1'when int_cnt = 140500 else   --sp
                      '1'when int_cnt = 151000 else   --0
                      '1'when int_cnt = 161500 else   --x
                      '1'when int_cnt = 172000 else   --address
                      '1'when int_cnt = 182500 else   --address
                      '1'when int_cnt = 193000 else   --enter
                          
                      '0';
                      
      sigdata <= "01110111" when ((int_cnt > 450)and(int_cnt < 550)) else     --w
                 "00100000" when ((int_cnt > 10950)and(int_cnt <11050))else   --sp
                 "00110000" when ((int_cnt > 21450)and(int_cnt <21550))else   --0
                 "01111000" when ((int_cnt > 31950)and(int_cnt <32050))else   --x
                 "00110000" when ((int_cnt > 42450)and(int_cnt <42550))else   --address
                 "00110001" when ((int_cnt > 52950)and(int_cnt <53050))else   --address
                 "00100000" when ((int_cnt > 63450)and(int_cnt <63550))else   --sp
                 "00110000" when ((int_cnt > 73950)and(int_cnt <74050))else   --0
                 "01111000" when ((int_cnt > 84450)and(int_cnt <84550))else   --x
                 "00110000" when ((int_cnt > 94950)and(int_cnt <95050))else   --data
                 "00110010" when ((int_cnt > 105450)and(int_cnt <105550))else   --data
                 
                 "00001101" when ((int_cnt > 115950)and(int_cnt <116050))else   --enter
                 "01110010" when ((int_cnt > 129950)and(int_cnt < 130050)) else  --w
                 "00100000" when ((int_cnt > 140450)and(int_cnt < 140550))else   --sp
                 "00110000" when ((int_cnt > 150950)and(int_cnt < 151050))else   --0
                 "01111000" when ((int_cnt > 161450)and(int_cnt < 161550))else   --x
                 "00110000" when ((int_cnt > 171950)and(int_cnt < 172050))else   --address
                 "00110011" when ((int_cnt > 182450)and(int_cnt < 182550))else   --address
                 "00001101" when ((int_cnt > 192950)and(int_cnt < 193050))else   --enter
                 "00000000";
                 
       reg3_map <= "00010011" when int_cnt > 4000 else (others => '0');
       reg4_map <= "00010100" when int_cnt > 4000 else (others => '0');
       
       
  u_TB_UART_TX : UART_TX
  port map(
    nRst      => signRst,
    clk       => sigclk,
    start_sig => sigstart_sig, 
    data      => sigdata,
    tx        => sig_data,
    busy      => sigbusy); 
      
  u_TB_UART_RX : UART_RX
   port map (
    nRst      => signRst,
   clk       => sigclk,
   serialin  => sig_data,
    rx_data   => sigrx_data,
    valid     => sigvalid );
  
  u_TB_data_pasing :  data_parsing 
   port map(
      nRst      => signRst,
      clk       => sigclk,
      in_data   => sigrx_data,
      valid     => sigvalid,
      write_s   => write_regi,
      read_s    => read_regi,
      address   => address_regi,
      data      => data_regi);
   
   u_TB_register_map : register_map
    port map(
        nRst             => signRst,
        clk              => sigclk,
        
        uart_write       => write_regi,
        uart_read        => read_regi,
        uart_address     => address_regi,
        uart_data        => data_regi,
        
        trans_write      => trans_w,
        trans_read       => trans_r,
        trans_address    => trans_add,
        trans_data       => trans_data,
        
        reg0             => reg0_map,
        reg1             => reg1_map, 
        reg2             => reg2_map, 
        reg3             => reg3_map,
        reg4             => reg4_map);     
           
    u_TB_load_tx_data : load_tx_data
    port map(
        nRst             => signRst,
        clk              => sigclk,
        write            => trans_w,
        read             => trans_r,
        address          => trans_add,
        data             => trans_data,
        busy             => busy_end,
        start_sig        => start_sig_load,
        tx_data          => tx_data_load);
        
     u_TB_uart_tx_end : uart_tx
     port map(
        nRst             => signRst,
        clk              => sigclk,
        start_sig        => start_sig_load,
        data             => tx_data_load,
        tx               => tx_end,
        busy             => busy_end );
         
end BEH;
