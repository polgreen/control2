makebenchmarks

benchmarks = load('benchmark_ss.mat');
benchmark_names = fieldnames(benchmarks);

for i=1:length(benchmark_names)
    system = benchmarks.(benchmark_names{i});
    parserss2ss(system, [1,-1], 8, 8, 1, -1, '', benchmark_names{i})
end

mkdir('benchmarks-ss');
movefile('*.ss','benchmarks-ss')
