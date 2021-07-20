onerror {quit -f}
vlib work
vlog -work work eittothreeencoder.vo
vlog -work work eittothreeencoder.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.eittothreeencoder_vlg_vec_tst
vcd file -direction eittothreeencoder.msim.vcd
vcd add -internal eittothreeencoder_vlg_vec_tst/*
vcd add -internal eittothreeencoder_vlg_vec_tst/i1/*
add wave /*
run -all
