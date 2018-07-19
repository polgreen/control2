#usage ./float-multi-benchmark-runner.sh benchmark_dir precision synth_type formal_form from to implementation_bits max_output
#precision in bits (16=half, 32=single, 64=double, 0=from_spec_file)
#synth_type =CEGIS for controller, observer for controller with observer
#formal form '-NNF' for regular processing (see axelerator for other options)
#from to indicates the index of the files to be processed in the folder, if unknown from=1 to=number_of_files
#implementation bits are added as exp,mantissa
#max output overrides the output safety specification with +/- this value as a limit
script_base_directory=`pwd`
synth_type='observer'
timeout_time=7200
kill_time=7210

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
 if [ -n "$3" ]; then
  synth_type="$3"
 fi
fi

working_directory_base="/tmp/control_synthesis-ss-${working_directory_base_suffix}"
mkdir -p ${working_directory_base} 2>/dev/null

max=10000
for benchmark_dir in ${benchmark_dirs[@]}; do
 if [ -z $5 ]; then
  min=1
 else
  min=$5
 fi
 if [ -z $6 ]; then
  max=10000
 else
  max=$6
 fi
 current=0
 for benchmark in ${benchmark_dir}*.ss; do
  ((current++))
  if [ $current -gt $max ]; then
   break
  fi
  echo $PWD
  if [ $current -ge $min ]; then
   if [ -n "$4" ]; then
    if [ -n "$8" ]; then
     (time timeout --kill-after=${kill_time} ${timeout_time} "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $2 $synth_type $4 $7 $8) >>"${working_directory_base_suffix}-$4-$2.log" 2>&1
    elif [ -n "$7" ]; then
     (time timeout --kill-after=${kill_time} ${timeout_time} "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $2 $synth_type $4 $7) >>"${working_directory_base_suffix}-$4-$2.log" 2>&1
    else
     (time timeout --kill-after=${kill_time} ${timeout_time} "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $2 $synth_type $4) >>"${working_directory_base_suffix}-$4-$2.log" 2>&1
    fi
   elif [ -n "$2" ]; then
    (time timeout --kill-after=${kill_time} ${timeout_time} "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark $2 $synth_type) >>"${working_directory_base_suffix}-$2.log" 2>&1
   else
    (time timeout --kill-after=${kill_time} ${timeout_time} "${PWD}/float-benchmark-individual-runner.sh" $1 $benchmark) >>"${working_directory_base_suffix}.log" 2>&1
   fi
  fi
 done
 if [ -n "$4" ]; then
  cat "${working_directory_base_suffix}-$4-$2.log" | grep "/automatica/\|SYNTHESIS SUCCESSFUL\|real"
 else
 cat "${working_directory_base_suffix}-$2.log" | grep "/automatica/\|SYNTHESIS SUCCESSFUL\|real"
 fi
done
