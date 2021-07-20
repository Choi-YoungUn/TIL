onerror {quit -f}
vlib work
vlog -work work demux1x8.vo
vlog -work work demux1x8.vt
vsim -novopt -c -t 1ps -L cycloneii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.demux1x8_pack_proce_vlg_vec_tst
vcd file -direction demux1x8.msim.vcd
vcd add -internal demux1x8_pack_proce_vlg_vec_tst/*
vcd add -internal demux1x8_pack_proce_vlg_vec_tst/i1/*
add wave /*
run -all
