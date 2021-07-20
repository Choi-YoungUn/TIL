onerror {quit -f}
vlib work
vlog -work work myrommemory.vo
vlog -work work myrommemory.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.myrommemory_vlg_vec_tst
vcd file -direction myrommemory.msim.vcd
vcd add -internal myrommemory_vlg_vec_tst/*
vcd add -internal myrommemory_vlg_vec_tst/i1/*
add wave /*
run -all
