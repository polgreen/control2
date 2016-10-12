#!/bin/bash
export PATH=${PATH//jdk1.7.0_75/jdk1.8.0_20}
export PATH=${PATH//cbmc-5190/cbmc-trunk-diffblue-control-synthesis}
export PATH=${PATH}:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis/src/cegis:/users/pkesseli/software/cpp/cbmc/cbmc-trunk-diffblue-control-synthesis-analyzer/src/goto-analyzer:/users/pkesseli/software/cpp/z3/trunk/target/i686-linux/bin

function extract_variable {
 echo $1 | sed "s/.*$2 *= *\([^,]*\),.*/\1/"
}

function extract_array {
 pattern=".$2 *= *{ *\("
 i=0
 while [ ${i} -lt $3 ]; do
  pattern="${pattern} *[^, ]* *,"
  i=$((i+1))
 done
 pattern="${pattern%?}\)"
 echo $1 | sed "s/.*${pattern}.*/\1/"
}

function extend_array {
 missing_elements=`grep -o ',' <<< "$1" | grep -c .`
 missing_elements=$((missing_elements + 1))
 missing_elements=$(($2 - missing_elements))
 result="$1"
 i=0
 while [ ${i} -lt ${missing_elements} ]; do
  result="${result}, 0.000000"
  i=$((i+1))
 done
 echo ${result}
}

function write_success_message {
 start_time=$1
 log_file=$2
 end_time=`date +%s`
 runtime=$((end_time-start_time))
 echo 'SYNTHESIS SUCCESSFUL' >>${log_file}
 echo "<control_synthesis_time>${runtime}</control_synthesis_time>" >>${log_file}
}

function setup_benchmark {
 mkdir -p "$1" 2>/dev/null
 cp simplified_noise.c simplified_noiseQ.c "$1" 2>/dev/null
 echo "#define __PLANT_DEN_SIZE ${plant_a_size}" >"$1/${sizes_header_file}"
 echo "#define __PLANT_NUM_SIZE ${plant_b_size}" >>"$1/${sizes_header_file}"
 echo "#define __CONTROLLER_DEN_SIZE ${controller_a_size}" >>"$1/${sizes_header_file}"
 echo "#define __CONTROLLER_NUM_SIZE ${controller_b_size}" >>"$1/${sizes_header_file}"
 echo "#define SOLUTION_DEN_SIZE ${struct_a_size}" >>"$1/${sizes_header_file}"
 echo "#define SOLUTION_NUM_SIZE ${struct_b_size}" >>"$1/${sizes_header_file}"
 echo "struct anonymous3 plant={ .den={ ${plant_a} }, .den_uncertainty={ ${plant_a_uncertainty} }, .den_size=${plant_a_size}, .num={ ${plant_b} }, .num_uncertainty={ ${plant_b_uncertainty} }, .num_size=${plant_b_size} };" >"$1/${plant_header_file}"
 echo "struct anonymous3 controller={ .den={ ${controller_a} }, .den_uncertainty={ ${controller_a_uncertainty} }, .den_size=${controller_a_size}, .num={ ${controller_b} }, .num_uncertainty={ ${controller_b_uncertainty} }, .num_size=${controller_b_size} };" >"$1/${controller_header_file}"
}

contains_element () {
  local e
  for e in "${@:2}"; do [[ "$e" == "$1" ]] && return 0; done
  return 1
}

sizes_header_file='sizes.h'
plant_header_file='plant.h'
controller_header_file='controller.h'
working_directory_base='/tmp/control_synthesis'
mkdir -p ${working_directory_base} 2>/dev/null

#benchmarks_base='/users/pkesseli/documents/control-synthesis/benchmarks'
#solved_benchmarks=("${benchmarks_base}/CruiseControl/CruiseControl02.c" "${benchmarks_base}/example-a/example-a_PLANT1_SCHEMA2_IMPL1.c" "${benchmarks_base}/example-a/example-a_PLANT1_SCHEMA3_IMPL1.c" "${benchmarks_base}/example-a/example-a_PLANT1_SCHEMA3_IMPL2.c" "${benchmarks_base}/example-a/example-a_PLANT1_SCHEMA3_IMPL3.c" "${benchmarks_base}/example-a/example-a_PLANT1_SCHEMA4_IMPL2.c")

#benchmark='/users/pkesseli/documents/control-synthesis/benchmarks/example-a/example-a_PLANT1_SCHEMA3_IMPL3.c'
#benchmark='/users/pkesseli/documents/control-synthesis/benchmarks/CruiseControl/CruiseControl02.c'
#benchmark_dir='/users/pkesseli/documents/control-synthesis/benchmarks/SpringMassDamper/'

benchmark_dirs=('/users/pkesseli/documents/control-synthesis/benchmarks/CruiseControl/' '/users/pkesseli/documents/control-synthesis/benchmarks/Satellite/' '/users/pkesseli/documents/control-synthesis/benchmarks/SpringMassDamper/' '/users/pkesseli/documents/control-synthesis/benchmarks/example-a/' '/users/pkesseli/documents/control-synthesis/benchmarks/example-a_uncertainty/')
#for benchmark_dir in /users/pkesseli/documents/control-synthesis/benchmarks/*/; do
for benchmark_dir in ${benchmark_dirs[@]}; do
 for benchmark in ${benchmark_dir}*.c; do
  #$(contains_element "${benchmark}" "${solved_benchmarks[@]}") && continue

  impl_decl=`grep -Pzo '.*impl *=.*(\n.*?)*?;' ${benchmark}`
  impl_int_bits=$(extract_variable "${impl_decl}" 'int_bits')
  impl_frac_bits=$(extract_variable "${impl_decl}" 'frac_bits')

  controller_decl=`grep -Pzo '.*controller *=.*(\n.*?)*?;' ${benchmark}`
  controller_a_size=$(extract_variable "${controller_decl}" 'a_size')
  controller_b_size=$(extract_variable "${controller_decl}" 'b_size')
  controller_a=$(extract_array "${controller_decl}" 'a' "${controller_a_size}")
  controller_b=$(extract_array "${controller_decl}" 'b' "${controller_b_size}") 
  controller_a_uncertainty=$(extract_array "${controller_decl}" 'a_uncertainty' "${controller_a_size}")
  controller_b_uncertainty=$(extract_array "${controller_decl}" 'b_uncertainty' "${controller_b_size}")
  controller_sample_time=$(extract_variable "${controller_decl}" 'sample_time')

  plant_decl=`grep -Pzo '.*plant *=.*(\n.*?)*?;' ${benchmark}`
  plant_a_size=$(extract_variable "${plant_decl}" 'a_size')
  plant_b_size=$(extract_variable "${plant_decl}" 'b_size')
  plant_a=$(extract_array "${plant_decl}" 'a' "${plant_a_size}")
  plant_b=$(extract_array "${plant_decl}" 'b' "${plant_b_size}") 
  plant_a_uncertainty=$(extract_array "${plant_decl}" 'a_uncertainty' "${plant_a_size}")
  plant_b_uncertainty=$(extract_array "${plant_decl}" 'b_uncertainty' "${plant_b_size}")
  plant_sample_time=$(extract_variable "${plant_decl}" 'sample_time')

  struct_a_size=$(( plant_a_size >= controller_a_size ? plant_a_size : controller_a_size ))
  struct_b_size=$(( plant_b_size >= controller_b_size ? plant_b_size : controller_b_size ))
  plant_a=$(extend_array "${plant_a}" "${struct_a_size}")
  plant_a_uncertainty=$(extend_array "${plant_a_uncertainty}" "${struct_a_size}")
  plant_b=$(extend_array "${plant_b}" "${struct_b_size}")
  plant_b_uncertainty=$(extend_array "${plant_b_uncertainty}" "${struct_b_size}")
  controller_a=$(extend_array "${controller_a}" "${struct_a_size}")
  controller_a_uncertainty=$(extend_array "${controller_a_uncertainty}" "${struct_a_size}")
  controller_b=$(extend_array "${controller_b}" "${struct_b_size}")
  controller_b_uncertainty=$(extend_array "${controller_b_uncertainty}" "${struct_b_size}")

  max_length=64
  integer_width=8
  radix_width=$((impl_int_bits+impl_frac_bits))
  min_size_offset=$(((integer_width+radix_width)%8))
  [ ${min_size_offset} -ne 0 ] && integer_width=$((integer_width+8-min_size_offset))
  start_time=`date +%s`

 if [ "$1" != 'range' ]; then
  if [ "$1" != 'simple' ]; then
   simple_switch='-D __CHECK_FP'
   working_directory="${working_directory_base}/bound"
   log_file="${benchmark%.c}_bound.log"
   timeout_time=14400s
   kill_time=14460s
  else
   working_directory="${working_directory_base}/bound_simple"
   log_file="${benchmark%.c}_bound_simple.log"
   timeout_time=7200s
   kill_time=7260s
  fi
  $(setup_benchmark ${working_directory})
  cd ${working_directory}

  echo ${benchmark} | tee ${log_file}
  echo "CEGIS" | tee -a ${log_file}
  while [ $((integer_width+radix_width)) -le ${max_length} ]; do
   echo "int: ${integer_width}, radix: ${radix_width}" | tee -a ${log_file}
   timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cegis -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} -D _CONTROLER_INT_BITS=${impl_int_bits} -D _CONTROLER_FRAC_BITS=${impl_frac_bits} ${simple_switch} --fixedbv --round-to-minus-inf --cegis-control --cegis-statistics --cegis-genetic --cegis-max-size 1 --cegis-show-iterations simplified_noise.c >>${log_file} 2>&1
   if [ $? -eq 0 ]; then
    solution_decl=`grep -Pzo '  controller=.*(\n.*?)*?} \(' ${log_file}`
    solution_a=$(extract_array "${solution_decl}" 'den' "${struct_a_size}")
    solution_b=$(extract_array "${solution_decl}" 'num' "${struct_b_size}")
    echo "struct anonymous3 controller={ .den={ ${solution_a} }, .den_uncertainty={ ${controller_a_uncertainty} }, .den_size=${controller_a_size}, .num={ ${solution_b} }, .num_uncertainty={ ${controller_b_uncertainty} }, .num_size=${controller_b_size} };" >${controller_header_file}
    gcc -std=c99 -D _CONTROLER_INT_BITS=${impl_int_bits} -D _CONTROLER_FRAC_BITS=${impl_frac_bits} simplified_noiseQ.c -o simplified_noiseQ
    ./simplified_noiseQ >>${log_file}
    if [ $? -eq 0 ]; then
     $(write_success_message ${start_time} ${log_file})
     break
    else
     echo 'SYNTHESIS FAILED' >>${log_file}
    fi
   fi
   integer_width=$((integer_width+4))
   radix_width=$((radix_width+4))
  done

 else

  working_directory="${working_directory_base}/range"
  log_file="${benchmark%.c}_range.log"
  timeout_time=28800s
  kill_time=28860s
  $(setup_benchmark ${working_directory})
  cd ${working_directory}

  echo ${benchmark} | tee ${log_file}
  echo "CBMC" | tee -a ${log_file}
  while [ $((integer_width+radix_width)) -le ${max_length} ]; do
   echo "int: ${integer_width}, radix: ${radix_width}" | tee -a ${log_file}
   timeout --preserve-status --kill-after=${kill_time} ${timeout_time} cbmc -D __CPROVER -D _FIXEDBV -D _CONTROL_FLOAT_WIDTH=$((integer_width+radix_width)) -D _CONTORL_RADIX_WIDTH=${radix_width} -D _CONTROLER_INT_BITS=${impl_int_bits} -D _CONTROLER_FRAC_BITS=${impl_frac_bits} --fixedbv --stop-on-fail --round-to-minus-inf simplified_noiseQ.c >>${log_file} 2>&1
   if [ $? -eq 10 ]; then
    $(write_success_message ${start_time} ${log_file})
    break
   fi
   integer_width=$((integer_width+4))
   radix_width=$((radix_width+4))
  done
 fi

 done
done
