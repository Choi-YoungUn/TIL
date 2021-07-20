onerror {quit -f}
vlib work
vlog -work work sodavending_mechine.vo
vlog -work work sodavending_mechine.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.sodavending_mechine_vlg_vec_tst
vcd file -direction sodavending_mechine.msim.vcd
vcd add -internal sodavending_mechine_vlg_vec_tst/*
vcd add -internal sodavending_mechine_vlg_vec_tst/i1/*
add wave /*
run -all
