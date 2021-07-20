onerror {quit -f}
vlib work
vlog -work work cnt_60.vo
vlog -work work cnt_60.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.cnt_60_vlg_vec_tst
vcd file -direction cnt_60.msim.vcd
vcd add -internal cnt_60_vlg_vec_tst/*
vcd add -internal cnt_60_vlg_vec_tst/i1/*
add wave /*
run -all
