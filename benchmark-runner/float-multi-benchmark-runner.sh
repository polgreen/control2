#!/bin/bash
script_base_directory=`pwd`
synth_type='observer'

benchmark_base_dir=("${PWD}/../benchmarks/automatica/")
if [ -z "$1" ]; then
 #dkr10
 #benchmark_dirs=("${benchmark_base_dir}cruise_ss/")
 benchmark_dirs=("${benchmark_base_dir}dcmotor_ss/") #ok
 #benchmark_dirs=("${benchmark_base_dir}helicopter_ss/")
 #benchmark_dirs=("${benchmark_base_dir}magsuspension_ss/")
 #benchmark_dirs=("${benchmark_base_dir}magneticpointer_ss/")
 #benchmark_dirs=("${benchmark_base_dir}satellite_ss/")
 #benchmark_dirs=("${benchmark_base_dir}invpendulum_pendang_ss/")
 #benchmark_dirs=("${benchmark_base_dir}invpendulum_cartpos_ss/")
 #benchmark_dirs=("${benchmark_base_dir}suspension_ss/")
 #benchmark_dirs=("${benchmark_base_dir}tapedriver_ss/")
 #benchmark_dirs=("${benchmark_base_dir}pendulum_ss/") #ok
else
 benchmark_dirs=("${benchmark_base_dir}$1/") #ok
 working_directory_base_suffix="$1"
 if [ -n "$2" ]; then
  synth_type="$2"
 fi
fi

working_directory_base="/tmp/control_synthesis-ss-${working_directory_base_suffix}"
mkdir -p ${working_directory_base} 2>/dev/null

max=10000
for benchmark_dir in ${benchmark_dirs[@]}; do
 if [ -z $4 ]; then
  min=1
 else
  min=$4
 fi
 if [ -z $5 ]; then
  max=10000
 else
  max=$5
 fi
 current=0
 for benchmark in ${benchmark_dir}*.ss; do
  ((current++))
  if [ $current -gt $max ]; then
   break
  fi
  echo $PWD
  if [ $current -ge $min ]; then
   if [ -n "$3" ]; then
    if [ -n "$7" ]; then
     (time "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $synth_type $3 $6 $7) >>"${working_directory_base_suffix}-$3.log" 2>&1
    elif [ -n "$6" ]; then
     (time "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $synth_type $3 $6) >>"${working_directory_base_suffix}-$3.log" 2>&1
    else
     (time "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $synth_type $3) >>"${working_directory_base_suffix}-$3.log" 2>&1
    fi
   else
    (time "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $synth_type) >>"${working_directory_base_suffix}.log" 2>&1
   fi
  fi
 done
done
