
%script to generate automatically the tf and ss files

makebenchmarks

benchmarks_ss = load('benchmark_ss.mat');
benchmark_names_ss = fieldnames(benchmarks_ss);

benchmarks_tf = load('benchmark_tf.mat');
benchmark_names_tf = fieldnames(benchmarks_tf);

INPUT_10 = {'ballmaglev','pendulum','satellite', 'usgtampa', 'invpendulum_pendang'};
INPUT_100 = {'magneticpointer', 'invpendulum_cartpos'};    
INPUT_1000 = {'magsuspension'};
INPUT_1000000 = {'suspension'};

for i=1:length(benchmark_names_ss)
    system = benchmarks_ss.(benchmark_names_ss{i});
    
     Name = strsplit(benchmark_names_ss{i},'_ss_disc');
        %get INPUT values
    if(getnameidx(INPUT_10,Name{1})~=0)
        INPUT=[-10,10];
    elseif (getnameidx(INPUT_100,Name{1})~=0 )
        INPUT=[-100,100];  
    elseif (getnameidx(INPUT_100,Name{1})~=0 )
        INPUT=[-100,100];  
    elseif (getnameidx(INPUT_1000,Name{1})~=0 )
        INPUT=[-1000,1000];  
   elseif (getnameidx(INPUT_1000000,Name{1})~=0 )
        INPUT=[-1000000,1000000];
    else
        INPUT=[-1, 1];
    end 
    parserss2ss(system, INPUT, 8, 8, 1, -1, '', benchmark_names_ss{i})
end

for i=1:length(benchmark_names_tf)
    system = benchmarks_tf.(benchmark_names_tf{i});
    parsertf2c(system, 8, 8, 1, -1, benchmark_names_tf{i})
end

mkdir('benchmarks-ss');
movefile('*.ss','benchmarks-ss')

mkdir('benchmarks-tf');
movefile('*.c','benchmarks-tf')
