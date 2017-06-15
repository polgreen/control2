%script to run all benchmarks for ase2017 experiments
clc
clear all
close all

makebenchmarks

benchmarks_ss = load('benchmark_ss.mat');
benchmark_names_ss = fieldnames(benchmarks_ss);

benchmarks_tf = load('benchmark_tf.mat');
benchmark_names_tf = fieldnames(benchmarks_tf);

for i=1:length(benchmark_names_ss)
    system = benchmarks_ss.(benchmark_names_ss{i});
    controllerSS(i).system = synthesize(system,8,8,1,-1);
end

for i=1:length(benchmark_names_tf)
    system = benchmarks_tf.(benchmark_names_tf{i});
    controllerTF(i).system = synthesize(system,8,8,1,-1);
end