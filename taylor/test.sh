#!/usr/bin/env bash
function run {
    ./taylor "$1" "$2" "$3" "$4" "$5" | tr '\036\037' '\n,'
}

trig_start=-6.28
trig_end=6.28
trig_step=0.2

exp_start=-2
exp_end=2.5
exp_step=0.15

ln1p_start=-0.9
ln1p_end=1
ln1p_step=0.1

./taylor # Print header
for terms in 4 32; do
    run $trig_start $trig_end $trig_step sin  $terms
    run $trig_start $trig_end $trig_step cos  $terms
    run $exp_start  $exp_end  $exp_step  exp  $terms
    run $ln1p_start $ln1p_end $ln1p_step ln1p $terms
done