function k = get_completeness(A, B, K)
angles = angle(eig(A - B*K));
k = max(abs(2*pi/angles));
end