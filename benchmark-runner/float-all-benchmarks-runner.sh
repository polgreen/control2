#usage ./float-all-benchmarks precision implementation_bits
#precision in bits (16=half, 32=single, 64=double, 0=from_spec_file)
#implementation bits are added as exp,mantissa (eg 5,11 is half precision)
if [ -n $1 ];then
  precision=$1
else
  precision=0
fi
if [ -n $2 ];then
  ./float-multi-benchmark-runner.sh 'dcmotor' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'helicopter' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'magneticpointer' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'satellite' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'invpendulum_cartpos' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'suspension' CEGIS ${precision} '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'tapedriver' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'pendulum' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cruise' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'magsuspension' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'invpendulum_pendang' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'chen_ex1' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'chen_ex2' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'chen_ex3' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'chen_ex4' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'acrobot' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'antenna' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cstr' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cstrtemp' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'balmaglev' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'bioreact' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cruise' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cruiseHSCC' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'flexbeam' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'guidance_chen' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'regulator' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'steamdrum' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'spring_mass_damp' ${precision} CEGIS '-NNF' 1 10 "$2"
else
  ./float-multi-benchmark-runner.sh 'dcmotor2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'helicopter2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'magneticpointer2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'satellite2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'invpendulum_cartpos2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'suspension2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'tapedriver_ss2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'pendulum2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'cruise2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'magsuspension2_ss' ${precision} CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'invpendulum_pendang2_ss' ${precision} CEGIS '-NNF'
fi
