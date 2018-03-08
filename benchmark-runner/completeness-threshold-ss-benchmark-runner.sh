#!/bin/bash
export PATH=/users/elipol/cbmc-5.7/src/cegis:${PATH}: #cegis path
#export PATH=/users/pkesseli/software/cpp/z3/trunk/target/i686-linux/bin:${PATH} #z3 path
BENCHMARK_BASE_DIR="/users/elipol/control-synthesis/benchmarks/headerfiles"

CEGIS_ARGS="--round-to-minus-inf --cegis-control --cegis-statistics --cegis-max-size 1 --cegis-show-iterations -D CPROVER -D FIXEDBV"

NUMVARS=$#
if [ $NUMVARS -eq 0 ]; then
echo "USEAGE ERROR: provide DKR number. Optional: append arguments to CEGIS"
exit
fi

if [ $NUMVARS -eq 2 ]; then
CEGIS_ARGS=$CEGIS_ARGS$2
echo "using CEGIS args $CEGIS_ARGS"
fi

synthesis_file='safety_stability.c'
script_base_directory=`pwd`
spec_header_file='benchmark.h'
source_template_directory=${script_base_directory}/universalrunner
solution_file='solution.log'

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

function extract_scalar_definition {
 echo $1 | sed "s/.*#define *$2 *\([^ \d]\+\).*/\1/"
}

function extract_spec_matrix {
 echo $1 | sed "s/.*$2[^=]*= *\([^;]\+\);.*/\1/" | sed 's/} *, *{/;/g' | sed 's/interval/fxp/g' | sed 's/[{}]//g'
}

function extract_input {
 echo $1 | sed "s/.*#define *$2 *\((__plant_precisiont)\)\? *\([-0-9]\+\(\.[0-9e-]\+\)\?\).*/\2/"
}

function setup_benchmark_directory {
 mkdir -p "$1" 2>/dev/null
 cp ${benchmark} ${working_directory}/benchmark.h
 cp ${source_template_directory}/${synthesis_file} ${working_directory}/
 cp ${source_template_directory}/control_types.h ${working_directory}/
 cp ${source_template_directory}/operators.h ${working_directory}/
 cp ${source_template_directory}/intervals.h ${working_directory}/
 cp ${source_template_directory}/mpreal.h ${working_directory}/
 cp ${source_template_directory}/int_2Inverse.h ${working_directory}/
 cp ${source_template_directory}/int_3Inverse.h ${working_directory}/
 cp ${source_template_directory}/discrete_step_k_completeness_check.cpp ${working_directory}/
}

function compile_precision_check {
 cd ${working_directory}
 g++ -I . -I /usr/include/eigen3/ discrete_step_k_completeness_check.cpp -o discrete_step_k_completeness_check -lmpfr
 chmod +x discrete_step_k_completeness_check
 gcc -D INTERVAL safety_stability.c -o precision_check
 chmod +x precision_check
}

function get_current_cpu_millis {
 cat ${time_tmp_file} >>${log_file}
 formula=$(sed -r 's/([0-9]+(\.[0-9]+)?)m([0-9]+)\.0*([0-9]+)?s/60000*\1+1000*\3+\4/g' ${time_tmp_file} | tr '\n' ' ' | sed -r 's/ /+/g' | sed -r 's/(.*)[+]$/\1/' | sed -r 's/(.*)[+]$/\1/' | sed -r 's/[+]+/+/')
 echo $((${formula}))
}

working_directory_base_suffix="$1"
#dkr10
if [ "$1" == "dkr10" ]; then
 benchmark_dirs=(${BENCHMARK_BASE_DIR}/cruise/ ${BENCHMARK_BASE_DIR}/dcmotor/ ${BENCHMARK_BASE_DIR}/helicopter/ ) 
fi

#dkr11
if [ "$1" == "dkr11" ]; then
benchmark_dirs=(${BENCHMARK_BASE_DIR}/invpendulum_pendang/ ${BENCHMARK_BASE_DIR}/invpendulum_cartpos/ ) 
fi

#dkr12
if [ "$1" == "dkr12" ]; then
benchmark_dirs=(${BENCHMARK_BASE_DIR}/magneticpointer/ ${BENCHMARK_BASE_DIR}/magsuspension/ ${BENCHMARK_BASE_DIR}/satellite/ ) 
fi

#dkr13
if [ "$1" == "dkr13" ]; then
benchmark_dirs=(${BENCHMARK_BASE_DIR}/pendulum/ ${BENCHMARK_BASE_DIR}/tapedrive/ ${BENCHMARK_BASE_DIR}/suspension/  ) 
fi

working_directory_base="/tmp/control_synthesis-ss-${working_directory_base_suffix}"
mkdir -p ${working_directory_base} 2>/dev/null

for benchmark_dir in ${benchmark_dirs[@]}; do
  echo "benchmark dir $benchmark_dir"	
 time_tmp_file=/tmp/times${working_directory_base_suffix}.log
 times >${time_tmp_file}; start_time=$(get_current_cpu_millis)

 for benchmark in ${benchmark_dir}*.h; do
  log_file="${benchmark%.h}_completeness-threshold-ss.log"
  truncate -s 0 ${log_file}
  echo_log ${benchmark}
  echo_log 'completeness-threshold-ss'

  working_directory="${working_directory_base}/completeness-threshold-ss"
  setup_benchmark_directory ${working_directory}
  cd ${working_directory}
  compile_precision_check
  cbmc_log_file="${working_directory}/cbmc.log"

  spec_content=`cat ${benchmark}`
  num_states=$(extract_scalar_definition "${spec_content}" 'NSTATES')
  impl_int_bits=$(extract_scalar_definition "${spec_content}" 'INT_BITS')
  impl_frac_bits=$(extract_scalar_definition "${spec_content}" 'FRAC_BITS')
  A=$(extract_spec_matrix "${spec_content}" '_controller_A')
  B=$(extract_spec_matrix "${spec_content}" '_controller_B')
  input_upper_bound=$(extract_input "${spec_content}" 'INPUT_UPPERBOUND')
  input_lower_bound=$(extract_input "${spec_content}" 'INPUT_LOWERBOUND')

  max_length=64
  integer_width=${impl_int_bits}
  radix_width=$((impl_int_bits+impl_frac_bits))
  min_size_offset=$(((integer_width+radix_width)%8))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+8-min_size_offset))
  k_sizes=(10 20 30 50 75 100 200)
  k_size_index=0
  timeout_time=3600
  kill_time=3780
  while [ $((integer_width+radix_width)) -le ${max_length} ] && [ ${k_size_index} -lt ${#k_sizes[@]} ]; do
   k_size=${k_sizes[${k_size_index}]}
   echo_log "int: ${integer_width}, radix: ${radix_width}"
   solution_found=false
   echo_log "$CEGIS_ARGS -D _PLANT_TOTAL_BITS=$((integer_width+radix_width)) -D _PLANT_RADIX_BITS=${radix_width} -D NUMBERLOOPS=${k_size} ${synthesis_file}"
   timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cegis $CEGIS_ARGS -D _PLANT_TOTAL_BITS=$((integer_width+radix_width)) -D _PLANT_RADIX_BITS=${radix_width}} -D NUMBERLOOPS=${k_size} ${synthesis_file} 2>>${log_file} 1>${cbmc_log_file}
   cbmc_result=$?
   cat ${cbmc_log_file} >>${log_file}
   controller_items=$(grep '<item>' ${cbmc_log_file} | tail -n ${num_states})
   controller_params=$(echo "${controller_items}" | sed -r 's/<\/item> <item>/ /g' | sed -r 's/<item>//g' | sed -r 's/<\/item>//g' | tr '\n' ' ')
   if [ ${cbmc_result} -eq 0 ]; then
    echo_log "./discrete_step_k_completeness_check ${k_size} ${controller_params}"
    eval "./discrete_step_k_completeness_check ${k_size} ${controller_params}"
    k_check_result=$?
    echo_log "k_check_result: ${k_check_result}"
    if [ ${k_check_result} -eq 2 ]; then
     k_size_index=$((k_size_index+1))
    elif [ ${k_check_result} -eq 1 ]; then
     echo_log 'K check error occurred'
     break
    else
     echo_log "./precision_check ${k_size} ${controller_params}"
     ./precision_check ${k_size} ${controller_params}
     if [ $? -eq 0 ]; then
      times >${time_tmp_file}; end_time=$(get_current_cpu_millis)
      echo_success_message ${start_time} ${end_time}
      echo_log "<controller>${controller_params}</controller>"
      echo_log "msg = '$(basename ${benchmark})'"
      echo "msg = '$(basename ${benchmark})'" >>${solution_file}
      matlab_controller="[$(echo ${controller_items} | sed -r 's/(-?[0-9]+(\.[0-9e-]+)?)/fxp(\1)/g' | sed -r 's/<item>//g' | sed -r 's/<\/item>//g' | sed -r 's/\)/\), /g')]"
      matlab_controller="$(echo ${matlab_controller} | sed -r 's/, \]/ \]/g')"
      echo_log "K = ${matlab_controller};"
      echo "K = ${matlab_controller};" >>${solution_file}
      echo_log "A = [ ${A} ];"
      echo "A = [ ${A} ];" >>${solution_file}
      echo_log "B = [ ${B} ];"
      echo "B = [ ${B} ];" >>${solution_file}
      echo_log "INPUT = [${input_lower_bound},${input_upper_bound}];"
      echo "INPUT = [${input_lower_bound},${input_upper_bound}];" >>${solution_file}
      echo "run fixedpointcheck.m" >>${solution_file}
      echo "" >>${solution_file}
      solution_found=true
      break
     else
      integer_width=$((integer_width+4))
      radix_width=$((radix_width+4))
     fi
    fi
   else
    integer_width=$((integer_width+4))
    radix_width=$((radix_width+4))
   fi
  done
  # All files are the same benchmark with increased sample frequency. Exit after first success.
  if [ "${solution_found}" = true ]; then
    break
  fi
 done
done
