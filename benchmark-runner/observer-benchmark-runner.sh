#!/bin/bash
export PATH=${PATH}:/media/sf_Documents/cbmc5.7/src/cbmc

status_output_file='output.txt'
synthesis_file='FWL_LTI.c'
nudge_file='FWL_LTI_NT.c'
width_check_file='width_LTI.c'
script_base_directory=`pwd`
spec_header_file='spec.h'
cbmc_log_file='cbmc-tmp.log'
solution_file='solution.log'
synth_type='observer'

function setup_benchmark_directory {
 mkdir -p "$1" 2>/dev/null
 cp ${script_base_directory}/AACegar/* ${working_directory}/ 2>/dev/null
 chmod +x ${working_directory}/axelerator
}

function echo_log {
 echo $1 | tee -a ${log_file}
}

function echo_success_message {
 start_time=$1
 end_time=$2
 runtime=$((end_time-start_time))
 echo_log 'SYNTHESIS SUCCESSFUL'
 echo_log "<control_synthesis_time>${runtime}</control_synthesis_time>"
}

function extract_spec_scalar {
 echo $1 | sed "s/.*$2 *= *\([^;]*\);.*/\1/"
}

function extract_spec_interval {
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

function extract_output_lower_bound {
 echo $1 | sed "s/.*outputs *= *\[ *\([^,]*\) *,.*/\1/"
}

function extract_output_upper_bound {
 echo $1 | sed "s/.*outputs *= *\[ *[^,]*,\([^]]*\).*/\1/"
}

function get_current_cpu_millis {
 cat ${time_tmp_file} >>${log_file}
 formula=$(sed -r 's/([0-9]+(\.[0-9]+)?)m([0-9]+)\.0*([0-9]+)?s/60000*\1+1000*\3+\4/g' ${time_tmp_file} | tr '\n' ' ' | sed -r 's/ /+/g' | sed -r 's/(.*)[+]$/\1/' | sed -r 's/(.*)[+]$/\1/' | sed -r 's/[+]+/+/')
 echo $((${formula}))
}

benchmark_base_dir=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/observer/')
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

 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/uscgtampa_ss/') #ok
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/ballmaglev_ss/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/pendulum_ss/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/flexbeam/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/chenhighorder/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/guidanceChen/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/acrobot/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/antenna/')
 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/linear/cstr/')

 #benchmark_dirs=('/media/sf_Documents/GitHub/control-synthesis/benchmarks/state-space/cruise_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/dcmotor_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/helicopter_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_cartpos_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/invpendulum_pendang_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/magsuspension_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/pendulum_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/suspension_ss/' '/users/pkesseli/documents/control-synthesis/benchmarks/state-space/tapedriver_ss/')
 #benchmark_dirs=("${script_base_directory}/../benchmarks/state-space/dcmotor_ss/")
else
 benchmark_dirs=("${benchmark_base_dir}$1/") #ok
 working_directory_base_suffix="$1"
 if [ -n "$2" ]; then
  synth_type="$2"
 fi
fi

working_directory_base="/tmp/control_synthesis-ss-${working_directory_base_suffix}"
mkdir -p ${working_directory_base} 2>/dev/null

for benchmark_dir in ${benchmark_dirs[@]}; do
 for benchmark in ${benchmark_dir}*.ss; do
  log_file="${benchmark%.ss}_accelerator-ss.log"
  time_tmp_file=/tmp/times${working_directory_base_suffix}.log
  times >${time_tmp_file}; start_time=$(get_current_cpu_millis)
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
  C=$(extract_spec_matrix "${spec_content}" 'C')
  input_lower_bound=$(extract_input_lower_bound "${spec_content}")
  input_upper_bound=$(extract_input_upper_bound "${spec_content}")
  output_lower_bound=$(extract_output_lower_bound "${spec_content}")
  output_upper_bound=$(extract_output_upper_bound "${spec_content}")
  sampling="\"$(extract_spec_interval "${spec_content}" 'sampling')\""
  speed=0.97
  options="-u -p -ii -cont -mpi 256 -fixedbv -synth ${synth_type} -params \"p=${num_states},q=${num_inputs},f=1,o=1,m=256:$((impl_int_bits+impl_frac_bits)):${impl_frac_bits},g=8\" -dynamics \"[${A}]\" -init \"[cube<.5]\" -oinit \"[cube<.5]\" -isense \"[${B}]\" -osense \"[${C}]\" -inputs \"[1>${input_lower_bound};1<${input_upper_bound}]\" -oguard \"[1>${output_lower_bound};1<${output_upper_bound}]\" -speed ${speed} -sample "
  #\"${sampling}:${delay}\""
  working_directory="${working_directory_base}/accelerator-ss"
  setup_benchmark_directory ${working_directory}
  cd ${working_directory}

  max_length=64
  #integer_width=8
  integer_width=$((2*impl_int_bits+4))
  radix_width=$((impl_frac_bits+4))
  #radix_width=$((impl_int_bits+impl_frac_bits))
  min_size_offset=$(((integer_width+radix_width)%16))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+16-min_size_offset))
  timeout_time=600
  kill_time=620
  echo_log "./axelerator $options $sampling -control \"[0]\""
  eval "./axelerator $options $sampling -control \"[0]\""
  out_content=`cat "output.txt"`
  sampling="\"$(extract_spec_interval "${out_content}" 'sampling')\""
  integer_width=$(extract_int_bits "${out_content}")
  radix_width=$(extract_frac_bits "${out_content}")
  echo_log "./axelerator $options $sampling -control \"[0]\""
  eval "./axelerator $options $sampling -control \"[0]\""
  
  while [ $((integer_width+radix_width)) -le ${max_length} ]; do
   echo_log "int: ${integer_width}, radix: ${radix_width}"
   solution_found=false
   nudge="-CNF"
   synthesis_in_progress=true
   while [ "${synthesis_in_progress}" = true ]; do
    if [ "${nudge}" = "-CNF" ]; then
      echo_log "cbmc -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} \"${working_directory}/${nudge_file}\" --stop-on-fail >${working_directory}/${cbmc_log_file}"
      timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cbmc -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} "${working_directory}/${nudge_file}" --stop-on-fail >${working_directory}/${cbmc_log_file} 2>&1
    else
      echo_log "cbmc -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} \"${working_directory}/${synthesis_file}\" --stop-on-fail >${working_directory}/${cbmc_log_file}"
      timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cbmc -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} "${working_directory}/${synthesis_file}" --stop-on-fail >${working_directory}/${cbmc_log_file} 2>&1
    fi
    if [ $? -eq 10 ]; then
     controller=$(grep 'controller_cbmc=' ${working_directory}/${cbmc_log_file} | sed 's/.*controller_cbmc={ *\([^}]*\) *}.*/\1/')
     if [ "${synth_type}" = "observer" ]; then
       observert=$(grep 'observer_cbmc=' ${working_directory}/${cbmc_log_file} | sed 's/.*observer_cbmc={ *\([^}]*\) *}.*/\1/')
       observer=${observert//,/;}
       echo_log "./axelerator $options $sampling -control \"[${controller}]\" -observe \"[${observer}]\" $nudge"
       eval "./axelerator $options $sampling -control \"[${controller}]\" -observe \"[${observer}]\" $nudge"
     else
       echo_log "./axelerator $options $sampling -control \"[${controller}]\" $nudge"
       eval "./axelerator $options $sampling -control \"[${controller}]\" $nudge"
     fi
     if grep --quiet 'SUCCESS' "${working_directory}/${status_output_file}"; then
      times >${time_tmp_file}; end_time=$(get_current_cpu_millis)
      echo_success_message ${start_time} ${end_time}
      echo_log "<controller>${controller}</controller>"
      if [ "${synth_type}" = "observer" ]; then
       echo_log "<observer>${observer}</observer>"
      fi
      echo_log "msg = '$(basename ${benchmark})'"
      echo "msg = '$(basename ${benchmark})'" >>${solution_file}
      out_content=`cat "output.txt"`
      final_controller=$(extract_spec_matrix "${out_content}" 'controller')
      final_observer=$(extract_spec_matrix "${out_content}" 'observer')
      echo_log "K = ${final_controller};"
      echo "K = ${final_controller};" >>${solution_file}
      echo_log "L = ${final_observer};"
      echo "L = ${final_observer};" >>${solution_file}
      echo_log "A = [ ${A} ];"
      echo "A = [ ${A} ];" >>${solution_file}
      echo_log "B = [ ${B} ];"
      echo "B = [ ${B} ];" >>${solution_file}
      echo_log "C = [ ${C} ];"
      echo "C = [ ${C} ];" >>${solution_file}
      echo_log "INPUT = [${input_lower_bound},${input_upper_bound}];"
      echo "INPUT = [${input_lower_bound},${input_upper_bound}];" >>${solution_file}
      echo_log "OUTPUT = [${output_lower_bound},${output_upper_bound}];"
      echo "OUTPUT = [${output_lower_bound},${output_upper_bound}];" >>${solution_file}
      echo_log "sampling = ${sampling};"
      echo "OUTPUT = ${sampling}" >>${solution_file}
      echo "" >>${solution_file}
      solution_found=true
      synthesis_in_progress=false
     else
      if grep --quiet 'DIVERGENT' "${working_directory}/system.h"; then
       solution_found=false
       synthesis_in_progress=false
       nudge=""
      else
       if grep --quiet 'NO_FEEDBACK' "${working_directory}/system.h"; then
        solution_found=false
        synthesis_in_progress=false
       else
        echo_log "<controller>${controller}</controller>"
        if [ "${synth_type}" = "observer" ]; then
         echo_log "<observer>${observer}</observer>"
        fi
        echo_log 'Refining abstraction...'
       fi       
      fi
     fi
    else
     synthesis_in_progress=false
    fi
   done
   if [ "${solution_found}" = true ]; then
    break
   fi
   integer_width=$((integer_width+8))
   radix_width=$((radix_width+8))
  done
  # All files are the same benchmark with increased sample frequency. Exit after first.
  if [ "${solution_found}" = true ]; then
    break
  fi
 done
done
