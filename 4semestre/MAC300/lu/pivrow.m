Arow = D;
for k = 1 : n
	iMax = k;
	for i = k + 1 : n
		if Arow(i, k) > Arow(iMax, k)
			iMax = i;
		endif
	endfor
	if iMax != k
		temp = Arow(k, :);
		Arow(k, : ) = Arow(iMax, : );
		Arow(iMax, : ) = temp;
	endif
	p(k) = iMax;
	for i = k + 1 : n
		Arow(i, k) = Arow(i, k) / Arow(k, k );
		for j = k + 1 : n
			Arow(i, j) -= Arow(k, j) * Arow(i, k);
		endfor
	endfor
endfor
disp(Arow);

brow = b;
%b' = Pb
for i = 1 : n
	if i != p(i)
		temp = brow(i);
		brow(i) = brow(p(i));
		brow(p(i)) = temp;
	endif
endfor

%Ly = b
for k = 1 : n
	for j = 1 : k - 1
		brow(k) -= Arow(k, j) * brow(j);
	endfor
endfor

%Ux = y
for k = fliplr(1 : n) 
    for j = fliplr(k + 1 : n)
        brow(k) -= brow(j) * Arow(k, j);
    endfor
    b(k) = b(k) / Arow(k, k);
endfor
disp(brow);


