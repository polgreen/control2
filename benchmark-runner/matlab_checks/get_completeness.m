function k = get_completeness(A, B, K)
angles = angle(eig(A - B*K));
k=0;
if (angles==0)
    k=0;
else
    for i=1:size(angles,1)
        if(angles(i)~=0)
            temp_k = abs(2*pi/angles(i));    
            if(temp_k>k)
                k=temp_k;
            end
        end   
    end    
end
end