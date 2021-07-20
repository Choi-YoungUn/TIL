onerror {quit -f}
vlib work
vlog -work work sec_gen.vo
vlog -work work sec_gen.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.sec_gen_vlg_vec_tst
vcd file -direction sec_gen.msim.vcd
vcd add -internal sec_gen_vlg_vec_tst/*
vcd add -internal sec_gen_vlg_vec_tst/i1/*
add wave /*
run -all
