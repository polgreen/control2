#!/bin/bash
export PATH=${PATH//cbmc-5190/cbmc-trunk-diffblue-control-synthesis}
export PATH=${PATH}:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis/src/cegis:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis-analyzer/src/goto-analyzer:/users/pkesseli/software/cpp/z3/trunk/target/i686-linux/bin

function setup_benchmark_directory {
 mkdir -p "$1" 2>/dev/null
 # TODO: cp source files and headers, and benchmark headers
}

function echo_log {
 echo $1 | tee -a ${log_file}
}

function echo_success_message {
 start_time=$1
 end_time=`date +%s`
 runtime=$((end_time-start_time))
 echo_log 'SYNTHESIS SUCCESSFUL'
 echo_log "<control_synthesis_time>${runtime}</control_synthesis_time>"
}

function extract_spec_scalar {
 echo $1 | sed "s/.*$2 *= *\([^;]*\);.*/\1/"
}

function extract_spec_matrix {
 echo $1 | sed "s/.*$2 *= *\[\([^]]*\)\].*/\1/"
}

function extract_int_bits {
 echo $1 | sed "s/.*implementation *< *\([^,]*\),.*/\1/"
}

function extract_frac_bits {
 echo $1 | sed "s/.*implementation *< *[^,]*,\([^> ]*\) *>.*/\1/"
}

status_output_file='output.txt'
synthesis_file='FWL_LTI.c'
width_check_file='width_LTI.c'
working_directory_base_suffix='-dkr10'
working_directory_base="/tmp/control_synthesis-ss${working_directory_base_suffix}"
mkdir -p ${working_directory_base} 2>/dev/null

if [ -z "$1" ]; then
 benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/dcmotor_ss/')
else
 benchmark_dirs=("$1")
fi

for benchmark_dir in ${benchmark_dirs[@]}; do
 for benchmark in ${benchmark_dir}*.ss; do
  log_file="${benchmark%.ss}_accelerator-ss.log"
  echo "log_file: $log_file"
  truncate -s 0 ${log_file}
  echo_log ${benchmark}
  echo_log 'accelerator-ss'

  spec_content=`cat ${benchmark}`
  impl_int_bits=$(extract_int_bits "${spec_content}")
  impl_frac_bits=$(extract_frac_bits "${spec_content}")
  num_states=$(extract_spec_scalar "${spec_content}" 'states')
  num_inputs=$(extract_spec_scalar "${spec_content}" 'inputs')
  num_outputs=$(extract_spec_scalar "${spec_content}" 'outputs')
  A=$(extract_spec_matrix "${spec_content}" 'A')
  B=$(extract_spec_matrix "${spec_content}" 'B')
  C=$(extract_spec_matrix "${spec_content}" 'C')
  D=$(extract_spec_matrix "${spec_content}" 'D')
  inputs=$(extract_spec_matrix "${spec_content}" 'inputs')
  exit 3

  working_directory="${working_directory_base}/accelerator-ss"
  setup_benchmark_directory ${working_directory}

  max_length=64
  integer_width=8
  radix_width=$((impl_int_bits+impl_frac_bits))
  min_size_offset=$(((integer_width+radix_width)%8))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+8-min_size_offset))
  timeout_time=3600
  kill_time=3780
  start_time=`date +%s`
  while [ $((integer_width+radix_width)) -le ${max_length} ]; do
   echo_log "int: ${integer_width}, radix: ${radix_width}"
   solution_found = false
   synthesis_in_progress = true
   while [ "${synthesis_in_progress}" = true ]; do
    #TODO: timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cbmc "${working_directory}/${synthesis_file}" >>${log_file} 2>&1
    if [ $? -eq 10 ]; then
     #TODO: grep controller from CBMC output
     candidate_solution="{ 1.0, 0.0, 0.5 }"
     #TODO: timeout --preserve-status --kill-after=${kill_time} ${timeout_time} accelerator-ss ${candidate_solution} >>${log_file} 2>&1
     if grep --quiet 'SUCCESS' "${working_directory}/${status_output_file}"; then
      $(echo_success_message ${start_time})
      solution_found = true
      synthesis_in_progress = false
     else
      #TODO: timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cbmc "${working_directory}/${width_check_file}" >>${log_file} 2>&1
      if [ $? -eq 10 ]; then
       continue
      else
       synthesis_in_progress = false
      fi
     fi
    fi
   done
   if [ "${solution_found}" = true ]; then
    break
   fi
   integer_width=$((integer_width+4))
   radix_width=$((radix_width+4))
  done
 done
 # All files are the same benchmark with increased sample frequency. Exit after first.
 exit 0
done
