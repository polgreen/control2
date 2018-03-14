if [ -n $1 ];then
  ./float-multi-benchmark-runner.sh 'dcmotor2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'helicopter2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'magneticpointer2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'satellite2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'invpendulum_cartpos2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'suspension2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'tapedriver_ss2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'pendulum2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'cruise2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'magsuspension2_ss' CEGIS '-NNF' 1 10 "$1"
#  ./float-multi-benchmark-runner.sh 'invpendulum_pendang2_ss' CEGIS '-NNF' 1 10 "$1"
else
  ./float-multi-benchmark-runner.sh 'dcmotor2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'helicopter2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'magneticpointer2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'satellite2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'invpendulum_cartpos2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'suspension2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'tapedriver_ss2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'pendulum2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'cruise2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'magsuspension2_ss' CEGIS '-NNF'
#  ./float-multi-benchmark-runner.sh 'invpendulum_pendang2_ss' CEGIS '-NNF'
fi
