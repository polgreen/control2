#!/bin/bash

for benchmark_dir in /users/pkesseli/documents/control-synthesis/benchmarks/*/; do
 for benchmark_log in ${benchmark_dir}*bound_simple.log; do
  execution_time_and_date=`date -r ${benchmark_log}`
  benchmark_id=$(basename $(dirname ${benchmark_log}))/$(basename ${benchmark_log})
  if [ `grep -c CEGIS ${benchmark_log}` -ne 0 ]; then
   is_cegis=1
  else
   is_cegis=0
  fi
  if [ ${is_cegis} -eq 1 ]; then
   if [ `grep -c 'SYNTHESIS SUCCESSFUL' ${benchmark_log}` -ne 0 ]; then
    success=1
   else
    success=0
   fi
   runtime=`grep '<control_synthesis_time>' ${benchmark_log} | grep -Po '(\d)*'`
   if [ -z "${runtime}" ]; then
    runtime='0'
   fi
   echo -e "${benchmark_id}\t${success}\t${runtime}s\t${execution_time_and_date}"
  fi
 done
done
