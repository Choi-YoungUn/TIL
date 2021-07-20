library ieee;
   use ieee.std_logic_1164.all;
   use ieee.std_logic_arith.all;
   use ieee.std_logic_unsigned.all;
   
 entity data_parsing is
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
 end data_parsing;
 
 architecture beh of data_parsing is
   
    function data_decode(in_data : std_logic_vector(7 downto 0))return
                                   std_logic_vector is
                                   variable return_data : std_logic_vector(3 downto 0);
       begin
         case in_data is
         when "00110000" => return_data := "0000";   --0 0x30
         when "00110001" => return_data := "0001";   --1 0x31
         when "00110010" => return_data := "0010";   --2 0x32
         when "00110011" => return_data := "0011";   --3 0x33
         when "00110100" => return_data := "0100";   --4 0x34
         when "00110101" => return_data := "0101";   --5 0x35
         when "00110110" => return_data := "0110";   --6 0x36
         when "00110111" => return_data := "0111";   --7 0x37
         when "00111000" => return_data := "1000";   --8 0x38
         when "00111001" => return_data := "1001";   --9 0x39
         when "01100001" => return_data := "1010";   --a 0x61
         when "01101010" => return_data := "1011";   --b 0x62
         when "01100011" => return_data := "1100";   --c 0x63
         when "01100100" => return_data := "1101";   --d 0x64
         when "01100101" => return_data := "1110";   --e 0x65
         when "01100110" => return_data := "1111";   --f 0x66
         when "01000001" => return_data := "1010";   --A 0x41
         when "01000010" => return_data := "1011";   --B 0x42
         when "01000011" => return_data := "1100";   --C 0x43
         when "01000100" => return_data := "1101";   --D 0x44
         when "01000101" => return_data := "1110";   --E 0x45
         when "01000110" => return_data := "1111";   --F 0x46
         when others     => return_data := "0000";
         end case;
       return(return_data);
  end data_decode;
  
  signal temp_data : std_logic_vector(7 downto 0);
  signal data_0    : std_logic_vector(7 downto 0);
  signal data_1    : std_logic_vector(7 downto 0);
  signal data_2    : std_logic_vector(7 downto 0);
  signal data_3    : std_logic_vector(7 downto 0);
  signal data_4    : std_logic_vector(7 downto 0);
  signal data_5    : std_logic_vector(7 downto 0);
  signal data_6    : std_logic_vector(7 downto 0);
  signal data_7    : std_logic_vector(7 downto 0);
  signal data_8    : std_logic_vector(7 downto 0);
  signal data_9    : std_logic_vector(7 downto 0);
  signal data_10   : std_logic_vector(7 downto 0);
  signal data_11   : std_logic_vector(7 downto 0);
  signal valid_d   : std_logic;
  signal valid_det   : std_logic;
  signal valid_det_d   : std_logic;
  signal valid_det_d2   : std_logic;
  
begin
  process(nRst, clk)
    begin
      if(nRst = '0')then
         valid_d <= '0';
         valid_det <= '0';
         valid_det_d <= '0';
         valid_det_d2 <= '0';
   elsif(rising_edge(clk)) then
         valid_d <= valid;
         valid_det_d <= valid_det;
         valid_det_d2 <= valid_det_d;
         if(valid_d = '0') and (valid = '1')then
         valid_det <= '1';
       else
         valid_det <= '0';
       end if;
     end if;
   end process;
   
   process(nRst, clk)
     begin
       if(nRst = '0')then
       temp_data <= (others => '0');
       data_0    <= (others => '0');
       data_1    <= (others => '0');
       data_2    <= (others => '0');
       data_3    <= (others => '0');
       data_4    <= (others => '0');
       data_5    <= (others => '0');
       data_6    <= (others => '0');
       data_7    <= (others => '0');
       data_8    <= (others => '0');
       data_9    <= (others => '0');
       data_10   <= (others => '0');
       data_11   <= (others => '0');
       address   <= (others => '0');
       data      <= (others => '0');
       write_s   <= '0';
       read_s    <= '0';
     elsif (rising_edge(clk))then
       temp_data <= in_data;
       if(valid_det = '1')then
         data_0 <= temp_data;  --enter     enter
         data_1 <= data_0;     --data_lsb  data_lsb
         data_2 <= data_1;     --data msb  data_msb
         data_3 <= data_2;     --x         x
         data_4 <= data_3;     --0         0
         data_5 <= data_4;     --sp        sp
         data_6 <= data_5;     --add lsb   r
         data_7 <= data_6;     --add msb   
         data_8 <= data_7;     --x
         data_9 <= data_8;     --0
         data_10 <= data_9;    --sp
         data_11 <= data_10;   --w
       end if;
       
       if(data_0 = x"0D") then  --enter
		 --if(data_0 = x"20") then --space
		          --  w                    sp                0
          if((data_11 = x"77")and(data_10 = x"20")and (data_9 = x"30")
			           --x                   sp               0               x
          and(data_8 = x"78")and(data_5 = x"20")and(data_4 = x"30")and(data_3 = x"78"))then
            write_s <= valid_det_d2;
            address <= data_decode(data_7) & data_decode(data_6);
            data    <= data_decode(data_2) & data_decode(data_1);
          end if;
          --        r                sp                    0                 x               
          if((data_6 = x"72")and(data_5 = x"20")and (data_4 = x"30")and(data_3 = x"78"))then
            read_s <= valid_det_d2;
            address <= data_decode(data_2) & data_decode(data_1);
            data    <= (others => '0');
          end if;
          
        end if;
      end if;
    end process;
  end beh;