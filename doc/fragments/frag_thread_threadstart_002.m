0
a = threadnew;               % Create the thread
threadstart(a,'svd',3,A);    % Start a full decomposition 
[u1,s1,v1] = threadvalue(a); % Retrieve the function values
threadfree(a);