function INPUT = get_inputs(Name)

INPUT_10 = {'ballmaglev','pendulum','satellite', 'usgtampa', 'invpendulum_pendang','bioreact'};
INPUT_100 = {'magneticpointer', 'invpendulum_cartpos','steamdrum','cstrtemp'};    
INPUT_1000 = {'magsuspension'};
INPUT_1000000 = {'suspension'};

INPUT=[-10000,10000];
%     if(getnameidx(INPUT_10,Name)~=0)
%         INPUT=[-10,10];
%     elseif (getnameidx(INPUT_100,Name)~=0 )
%         INPUT=[-100,100];  
%     elseif (getnameidx(INPUT_100,Name)~=0 )
%         INPUT=[-100,100];  
%     elseif (getnameidx(INPUT_1000,Name)~=0 )
%         INPUT=[-1000,1000];  
%    elseif (getnameidx(INPUT_1000000,Name)~=0 )
%         INPUT=[-1000000,1000000];
%     else
%         INPUT=[-1, 1];
%     end 
end