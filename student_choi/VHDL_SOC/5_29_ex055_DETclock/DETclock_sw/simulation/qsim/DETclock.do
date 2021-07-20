onerror {quit -f}
vlib work
vlog -work work DETclock.vo
vlog -work work DETclock.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.DETclock_vlg_vec_tst
vcd file -direction DETclock.msim.vcd
vcd add -internal DETclock_vlg_vec_tst/*
vcd add -internal DETclock_vlg_vec_tst/i1/*
add wave /*
run -all
