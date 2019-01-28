#!/bin/bash
NUMVARS=$#
if [ $NUMVARS -eq 0 ]; then
echo "USEAGE ERROR: provide DKR number. Optional: append arguments to CEGIS"
exit
fi


if [ "$1" == "dkr10" ]; then
 benchmarks=(acrobot antenna ballmaglev bioreact chen_ex1 chen_ex2) 
fi

#dkr11
if [ "$1" == "dkr11" ]; then
benchmarks=(chen_ex3 chen_ex4 cruise cruiseHSCC cstr cstrtemp ) 
fi

#dkr12
if [ "$1" == "dkr12" ]; then
benchmarks=(dcmotor flexbeam guidance_chen helicopter invpendulum_cartpos invpendulum_pendang) 
fi

#dkr13
if [ "$1" == "dkr13" ]; then
benchmarks=(magneticpointer magsuspension pendulum regulator springmassdamperHSCC steamdrum suspension tapedriver uscgtampa) 
fi

for benchmark in ${benchmarks[@]}; do
echo "BENCHMARK: $benchmark"
 timeout 18000 ./completeness-threshold-float-benchmark-runner.sh $benchmark $2

if [ $? -ne 0 ]; then
 echo "timeout $benchmark" > /users/elipol/control-synthesis/benchmark-runner/float_timeouts.txt
fi

done
