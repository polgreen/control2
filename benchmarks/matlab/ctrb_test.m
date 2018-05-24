% Script for controlability checking of benchmarks
% The struct benchmarks_nonctb_name contains the names of non-controllable
% benchmarks and benchmarks_ctb_name contains the names of controllable
% benchmarks
% Iury Bessa
% Manaus, 2018


makebenchmarks;
benchmarks_ss = load('benchmark_ss.mat');
benchmark_names_ss = fieldnames(benchmarks_ss);
ctb=0;
nonctb=0;
for i=1:length(benchmark_names_ss)
    ctbtest = rank(ctrb(benchmarks_ss.(benchmark_names_ss{i}).A,...
        benchmarks_ss.(benchmark_names_ss{i}).B)) == ...
        size(benchmarks_ss.(benchmark_names_ss{i}).A,1);
    if(ctbtest)
        ctb=ctb+1;
        benchmarks_ctb_name{ctb}=benchmark_names_ss{i};
    else
        nonctb =nonctb+1;
        benchmarks_nonctb_name{nonctb}=benchmark_names_ss{i};
    end
end