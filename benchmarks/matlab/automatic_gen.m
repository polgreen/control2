makebenchmarks

benchmarks_ss = load('benchmark_ss.mat');
benchmark_names_ss = fieldnames(benchmarks_ss);

benchmarks_tf = load('benchmark_tf.mat');
benchmark_names_tf = fieldnames(benchmarks_tf);

for i=1:length(benchmark_names_ss)
    system = benchmarks_ss.(benchmark_names_ss{i});
    parserss2ss(system, [1,-1], 8, 8, 1, -1, '', benchmark_names_ss{i})
end

for i=1:length(benchmark_names_tf)
    system = benchmarks_tf.(benchmark_names_tf{i});
    parsertf2c(system, 8, 8, 1, -1, benchmark_names_tf{i})
end

mkdir('benchmarks-ss');
movefile('*.ss','benchmarks-ss')

mkdir('benchmarks-tf');
movefile('*.c','benchmarks-tf')
