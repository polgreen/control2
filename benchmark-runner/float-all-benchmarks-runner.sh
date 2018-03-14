#usage ./float-all-benchmarks precision implementation_bits
if [ -n $1 ];then
  precision=$1
else
  precision=0
fi
if [ -n $2 ];then
  ./float-multi-benchmark-runner.sh 'dcmotor2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'helicopter2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'magneticpointer2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'satellite2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'invpendulum_cartpos2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'suspension2_ss' CEGIS ${precision} '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'tapedriver_ss2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'pendulum2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'cruise2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'magsuspension2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
#  ./float-multi-benchmark-runner.sh 'invpendulum_pendang2_ss' ${precision} CEGIS '-NNF' 1 10 "$2"
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
