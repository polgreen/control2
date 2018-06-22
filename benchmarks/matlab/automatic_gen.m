
%script to generate automatically the tf and ss files

makebenchmarks

benchmarks_ss = load('benchmark_ss.mat');
benchmark_names_ss = fieldnames(benchmarks_ss);

benchmarks_tf = load('benchmark_tf.mat');
benchmark_names_tf = fieldnames(benchmarks_tf);


for i=1:length(benchmark_names_ss)
    system = benchmarks_ss.(benchmark_names_ss{i});
    
    Name = strsplit(benchmark_names_ss{i},'_ss_disc');
    INPUT=get_inputs(Name{1});
    parserss2ss(system, INPUT, 8, 8, 1, -1, '', benchmark_names_ss{i})
    mkdir(strcat('benchmarks-ss/',benchmark_names_ss{i}(1:end-9)));
    movefile('*.ss',strcat('benchmarks-ss/',benchmark_names_ss{i}(1:end-9)));

end

for i=1:length(benchmark_names_tf)
    system = benchmarks_tf.(benchmark_names_tf{i});
    parsertf2c(system, 8, 8, 1, -1, benchmark_names_tf{i})
end


mkdir('benchmarks-tf');
movefile('*.c','benchmarks-tf')
