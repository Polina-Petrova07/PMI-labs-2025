#!/usr/bin/env bash
set -uo pipefail

outdir='/tmp/taylor_result'

function run {
    ./taylor 2>/dev/null > "$outdir/$4$5.csv" # Print header
    ./taylor "$1" "$2" "$3" "$4" "$5" | tr '\036\037' '\n,' >> "$outdir/$4$5.csv"
}

trig_start=-2
trig_end=2
trig_step=0.1

exp_start=-2
exp_end=2.5
exp_step=0.1

ln1p_start=-0.95
ln1p_end=1.05
ln1p_step=0.05

mkdir "$outdir" || exit

for terms in 4 10; do
    run $trig_start $trig_end $trig_step sin  $terms
    run $trig_start $trig_end $trig_step cos  $terms
    run $exp_start  $exp_end  $exp_step  exp  $terms
done

for terms in 4 32; do
    run $ln1p_start $ln1p_end $ln1p_step ln1p $terms
done
