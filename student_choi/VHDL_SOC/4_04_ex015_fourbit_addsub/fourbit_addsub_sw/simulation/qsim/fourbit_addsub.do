onerror {quit -f}
vlib work
vlog -work work fourbit_addsub.vo
vlog -work work fourbit_addsub.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.fourbit_addsub_vlg_vec_tst
vcd file -direction fourbit_addsub.msim.vcd
vcd add -internal fourbit_addsub_vlg_vec_tst/*
vcd add -internal fourbit_addsub_vlg_vec_tst/i1/*
add wave /*
run -all
