library ieee;
use ieee.std_logic_1164.all;

entity hamming_decoder is
port( aiput : in std_logic_vector(6 downto 0); --데이터 입력

       synput : out std_logic_vector(2 downto 0);--신드롬 출력
		 errorput : out std_logic_vector(6 downto 0)--에러코드 출력
		 );
		 end hamming_decoder;
		 architecture sample of hamming_decoder is
		
		component hamming_decoder_syn is   --신드롬 컴포넌트
       port( ai : in std_logic_vector(6 downto 0);
       syn : out std_logic_vector(2 downto 0)
		 );
		 end component;
		 
		 component hamming_decoder_error is   --에러코드 컴포넌트
       port(  syni : in std_logic_vector(2 downto 0);
		 error : out std_logic_vector(6 downto 0)
		 );
		 end component;
		 signal syntemp : std_logic_vector(2 downto 0); --신호 선언.
		 signal errortemp : std_logic_vector(6 downto 0);
		 
		 begin
		 ai_synput : hamming_decoder_syn --헤밍코드를 통한 신드롬 출력
		 port map (ai => aiput, syn => syntemp);
		 
		 syn_errorput : hamming_decoder_error 
		 port map (syni => syntemp, error => errorput);  --신드롬을 통한 에러코드 출력
		 synput <= syntemp;-- 신드롬 출력
		 end sample;