#!/bin/bash
#export PATH=${PATH//cbmc-5190/cbmc-trunk-diffblue-control-synthesis}
export PATH=${PATH}:/media/sf_Documents/GitHub/cbmc-master/src/cbmc
#export PATH=${PATH}:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis/src/cegis:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis-analyzer/src/goto-analyzer:/users/pkesseli/software/cpp/z3/trunk/target/i686-linux/bin

status_output_file='output.txt'
synthesis_file='FWL_LTI.c'
width_check_file='width_LTI.c'
working_directory_base_suffix='-dkr10'
working_directory_base="/tmp/control_synthesis-ss${working_directory_base_suffix}"
spec_header_file='spec.h'

function setup_benchmark_directory {
 mkdir -p "$1" 2>/dev/null
 cp ./AACegar/* ${working_directory}/
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

function extract_input_lower_bound {
 echo $1 | sed "s/.*inputs *= *\[ *\([^,]*\) *,.*/\1/"
}

function extract_input_upper_bound {
 echo $1 | sed "s/.*inputs *= *\[ *[^,]*,\([^]]*\).*/\1/"
}

function write_spec_header {
 header_file="${working_directory}/${spec_header_file}"
 echo "#define NSTATES ${num_states}" >${header_file}
 echo "#define NINPUTS ${num_inputs}" >>${header_file}
 echo "#define NOUTPUTS ${num_outputs}" >>${header_file}
 echo "#define INT_BITS ${impl_int_bits}" >>${header_file}
 echo "#define FRAC_BITS ${impl_frac_bits}" >>${header_file}
 A_value=$(echo $1 | sed -r 's/;/ }, { /g')
 echo "const __CPROVER_EIGEN_fixedbvt _controller_A[NSTATES][NSTATES] = { { ${A_value} } };" >>${header_file}
 B_value=$(echo $2 | sed -r 's/;/, /g')
 echo "const __CPROVER_EIGEN_fixedbvt _controller_B[NSTATES] = { ${B_value} };" >>${header_file}
 echo "#define INPUT_LOWERBOUND (__CPROVER_EIGEN_fixedbvt)$3" >>${header_file}
 echo "#define INPUT_UPPERBOUND (__CPROVER_EIGEN_fixedbvt)$4" >>${header_file}
}

mkdir -p ${working_directory_base} 2>/dev/null

if [ -z "$1" ]; then
 #benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/state-space/dcmotor_ss/'
 benchmark_dirs=('../benchmarks/state-space/dcmotor_ss/')
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
  options="-u -p -ii -mpi 256 -synth CEGIS -params \"p=${num_states},q=${num_inputs},f=1,m=256:$((impl_int_bits+impl_frac_bits)):${impl_frac_bits}\" -dynamics \"[${A}]\" -init \"[1,0,0<1;-1,0,0<1;0,1,0<1;0,-1,0<1;0,0,1<1;0,0,-1<1]\" -isense \"[${B}]\" -inputs \"[1>${input_lower_bound};1<${input_upper_bound}]\" -sguard \"[1,0,0<2;-1,0,0<2;0,1,0<2;0,-1,0<2;0,0,1<2;0,0,-1<2]\""

  working_directory="${working_directory_base}/accelerator-ss"
  setup_benchmark_directory ${working_directory}
  write_spec_header "$A" "$B" "$input_lower_bound" "$input_upper_bound"

  max_length=64
  integer_width=8
  radix_width=$((impl_int_bits+impl_frac_bits))
  min_size_offset=$(((integer_width+radix_width)%8))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+8-min_size_offset))
  timeout_time=3600
  kill_time=3780
  start_time=`date +%s`
  eval "./axelerator $options -control \"[0,0,0]\""
  while [ $((integer_width+radix_width)) -le ${max_length} ]; do
   exit 3
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