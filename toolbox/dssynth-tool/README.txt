Directory structure
 * benchmark-runner: experiment scripts
 * benchmarks: benchmark set
 * cbmc: CBMC/CEGIS source directory

"compile-cbmc.sh"                compiles CBMC/CEGIS. Needs to be run before running any of the benchmark scripts.
"run-abstraction-based-cegis.sh" Runs the full experiment set with abstraction-based CEGIS.
"run-multi-staged-cegis.sh"      Runs the full experiment set with multi-staged CEGIS.

To run all experiments use the following commands:
chmod +x *.sh
./compile-cbmc.sh
./run-abstraction-based-cegis.sh
./run-multi-staged-cegis.sh


The benchmarks store controllers and runtime as well as status information in a log file per benchmark with the same name in the benchmark directory.
