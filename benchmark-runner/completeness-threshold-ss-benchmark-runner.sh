#!/bin/bash
export PATH=${PATH//cbmc-5190/cbmc-trunk-diffblue-control-synthesis}
export PATH=${PATH}:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis/src/cegis:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis-analyzer/src/goto-analyzer:/users/pkesseli/software/cpp/z3/trunk/target/i686-linux/bin

synthesis_file='safety_stability.c'
working_directory_base_suffix='-dkr10'
working_directory_base="/tmp/control_synthesis-ss${working_directory_base_suffix}"
script_base_directory=`pwd`
spec_header_file='benchmark.h'
source_template_directory=${script_base_directory}/universalrunner

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

function extract_input_lower_bound {
 echo $1 | sed "s/.*inputs *= *\[ *\([^,]*\) *,.*/\1/"
}

function extract_input_upper_bound {
 echo $1 | sed "s/.*inputs *= *\[ *[^,]*,\([^]]*\).*/\1/"
}

function setup_benchmark_directory {
 mkdir -p "$1" 2>/dev/null
 cp ${source_template_directory}/${synthesis_file} ${working_directory}/
 cp ${source_template_directory}/control_types.h ${working_directory}/
 cp ${source_template_directory}/operators.h ${working_directory}/
 cp ${source_template_directory}/mpreal.h ${working_directory}/
 cp ${source_template_directory}/discrete_step_k_completeness_check.cpp ${working_directory}/
}

function write_spec_header {
 header_file="${working_directory}/${spec_header_file}"
 echo "#define INT_BITS ${impl_int_bits}" >${header_file}
 echo "#define FRAC_BITS ${impl_frac_bits}" >>${header_file}
 echo '#include "control_types.h"' >>${header_file}
 echo '' >>${header_file}
 echo "#define NSTATES ${num_states}" >>${header_file}
 echo "#define NINPUTS ${num_inputs}" >>${header_file}
 echo "#define NOUTPUTS ${num_outputs}" >>${header_file}
 echo "#define INPUT_LOWERBOUND (__plant_typet)${input_lower_bound}" >>${header_file}
 echo "#define INPUT_UPPERBOUND (__plant_typet)${input_upper_bound}" >>${header_file}
 A_value=$(echo ${A} | sed -r 's/;/ }, { /g')
 A_value=$(echo ${A_value} | sed -r 's/([0-9]+(\.[0-9e-]+)?)/interval(\1)/g')
 echo "const __plant_typet _controller_A[NSTATES][NSTATES] = { { ${A_value} } };" >>${header_file}
 B_value=$(echo ${B} | sed -r 's/;/, /g')
 B_value=$(echo ${B_value} | sed -r 's/([0-9]+(\.[0-9e-]+)?)/interval(\1)/g')
 echo "const __plant_typet _controller_B[NSTATES] = { ${B_value} };" >>${header_file}

 g++ -I . -I /usr/include/eigen3/ discrete_step_k_completeness_check.cpp -o discrete_step_k_completeness_check -lmpfr
 chmod +x discrete_step_k_completeness_check
}

mkdir -p ${working_directory_base} 2>/dev/null

if [ -z "$1" ]; then
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/cruise_ss/') #ok
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/dcmotor_ss/') #ok
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/helicopter_ss/') #unsat
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_cartpos_ss/') #unsat
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_pendang_ss/') #unsat
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/magsuspension_ss/') #unsat
 benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/pendulum_ss/') #unsat
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/suspension_ss/') #ok
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/tapedriver_ss/') #ok
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/cruise_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/dcmotor_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/helicopter_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_cartpos_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_pendang_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/magsuspension_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/pendulum_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/suspension_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/tapedriver_ss/')
 #benchmark_dirs=("${script_base_directory}/../benchmarks/state-space/dcmotor_ss/")
else
 benchmark_dirs=("$1")
fi

for benchmark_dir in ${benchmark_dirs[@]}; do
 for benchmark in ${benchmark_dir}*.ss; do
  start_time=`date +%s`
  log_file="${benchmark%.ss}_completeness-threshold-ss.log"
  truncate -s 0 ${log_file}
  echo_log ${benchmark}
  echo_log 'completeness-threshold-ss'

  spec_content=`cat ${benchmark}`
  impl_int_bits=$(extract_int_bits "${spec_content}")
  impl_frac_bits=$(extract_frac_bits "${spec_content}")
  controller_fixedbv_type_width=$((impl_int_bits+impl_frac_bits))
  width_offset=$((controller_fixedbv_type_width%8))
  [ ${width_offset} -ne 0 ] && impl_int_bits=$((impl_int_bits+8-width_offset))
  num_states=$(extract_spec_scalar "${spec_content}" 'states')
  num_inputs=$(extract_spec_scalar "${spec_content}" 'inputs')
  num_outputs=$(extract_spec_scalar "${spec_content}" 'outputs')
  A=$(extract_spec_matrix "${spec_content}" 'A')
  B=$(extract_spec_matrix "${spec_content}" 'B')
  input_lower_bound=$(extract_input_lower_bound "${spec_content}")
  input_upper_bound=$(extract_input_upper_bound "${spec_content}")

  working_directory="${working_directory_base}/completeness-threshold-ss"
  setup_benchmark_directory ${working_directory}
  cd ${working_directory}
  write_spec_header
  cbmc_log_file="${working_directory}/cbmc.log"

  max_length=64
  integer_width=${impl_int_bits}
  #integer_width=8
  #integer_width=${impl_int_bits}
  radix_width=$((impl_int_bits+impl_frac_bits))
  #radix_width=${impl_frac_bits}
  min_size_offset=$(((integer_width+radix_width)%8))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+8-min_size_offset))
  k_sizes=(10 20 30 50 75 100 200)
  k_size_index=0
  timeout_time=3600
  kill_time=3780
  while [ $((integer_width+radix_width)) -le ${max_length} ] && [ ${k_size_index} -lt ${#k_sizes[@]} ]; do
   k_size=${k_sizes[${k_size_index}]}
   echo_log "int: ${integer_width}, radix: ${radix_width}"
   timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cegis --round-to-minus-inf --cegis-control --cegis-statistics --cegis-max-size 1 --cegis-show-iterations -D CPROVER -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} -D NUMBERLOOPS=${k_size} ${synthesis_file} 2>>${log_file} 1>${cbmc_log_file}
   cbmc_result=$?
   controller_items=$(grep '<item>' ${cbmc_log_file} | tail -n ${num_states})
   controller_params=$(echo "${controller_items}" | sed -r 's/<\/item> <item>/ /g' | sed -r 's/<item>//g' | sed -r 's/<\/item>//g' | tr '\n' ' ')
   if [ ${cbmc_result} -eq 0 ]; then
    echo_log "./discrete_step_k_completeness_check ${k_size} ${controller_params}"
    eval "./discrete_step_k_completeness_check ${k_size} ${controller_params}"
    k_check_result=$?
    if [ ${k_check_result} -eq 2 ]; then
      k_size_index=$((k_size_index+1))
    elif [ ${k_check_result} -eq 1 ]; then
      echo_log 'K check error occurred'
      break
    else
      # TODO: Check interval
      echo_success_message ${start_time}
      echo_log "<controller>${controller_params}</controller>"
      break
    fi
   else
    integer_width=$((integer_width+4))
    radix_width=$((radix_width+4))
   fi
  done

  break # TODO: Replace this if sampling rate check is introduced
 done
done
