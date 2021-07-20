onerror {quit -f}
vlib work
vlog -work work eitbit_par_register.vo
vlog -work work eitbit_par_register.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.eitbit_par_register_vlg_vec_tst
vcd file -direction eitbit_par_register.msim.vcd
vcd add -internal eitbit_par_register_vlg_vec_tst/*
vcd add -internal eitbit_par_register_vlg_vec_tst/i1/*
add wave /*
run -all
