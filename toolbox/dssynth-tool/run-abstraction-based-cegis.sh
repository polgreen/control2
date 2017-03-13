#!/bin/bash
export experiment_base_directory=`dirname $(readlink -f $0)`
export cbmc_directory="${experiment_base_directory}/cbmc"
export PATH="${PATH}:/${cbmc_directory}/src/cbmc:/${cbmc_directory}/src/cegis"

# Run experiments
benchmark_runner_directory="${experiment_base_directory}/benchmark-runner"
cd "${benchmark_runner_directory}"
chmod +x accelerator-ss-benchmark-runner.sh
./accelerator-ss-benchmark-runner.sh dkr10
./accelerator-ss-benchmark-runner.sh dkr11
./accelerator-ss-benchmark-runner.sh dkr12
./accelerator-ss-benchmark-runner.sh dkr13
