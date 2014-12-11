n = 10;
m = 5;
A = rand(n, m);

for k = 1 : m
    %calcula norma inf da coluna
    inf_nomr = 0;
    for i = k : n
        if A(i, k) > inf_norm
            inf_norm = A(i, k);
        end
    end
    if inf_norm == 0
        gama(k) = 0;
    else
        sigma(k) = 0
        for i = k : n
            A(i, k) = A(i, k) / inf_norm;
            sigma(k) = sigma(k) + A(i, k) * A(i, k);
        end
        if A(k, k) < 0
            sigma(k) = sigma(k) * -1
        end
        A(k, k) = A(k, k) + sigma(k)
        gama(k) = 1 / sigma(k) * A(k, k)
        sigma(k) = sigma(k) * inf_norm
    end
    %now we can multiply Q_k by A
    %Q_k = I - uu^t
    %u = A(ki)
    for j = k + 1 : m
        
end
