onerror {quit -f}
vlib work
vlog -work work half_adder.vo
vlog -work work half_adder.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.half_adder_vlg_vec_tst
vcd file -direction half_adder.msim.vcd
vcd add -internal half_adder_vlg_vec_tst/*
vcd add -internal half_adder_vlg_vec_tst/i1/*
add wave /*
run -all
