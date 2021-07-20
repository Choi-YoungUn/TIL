library ieee;
  use ieee.std_logic_1164.all;
  use ieee.std_logic_arith.all;
  use ieee.std_logic_unsigned.all;
  
  entity data_latch is
  port(
      nRst : in std_logic;
		clk : in std_logic;
	   in_data : in std_logic_vector(7 downto 0);
		valid : in std_logic;
		out_data : out std_logic_vector(7 downto 0)
  );
  end data_latch;
  
  architecture beh of data_latch is
  begin
     process(nRst, clk)
	  begin 
	  if(nRst = '0')then
	    out_data <= (others => '0');
		 elsif rising_edge(clk) then
		 if(valid = '1') then --valid 중에 많은 클럭이 들어와서 변경되므로 별로 좋은 회로는 아니다.
		 out_data <= in_data;
		 end if;
		 
		 end if;
		 end process;
  
  end beh;