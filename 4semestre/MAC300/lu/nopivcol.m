Acol = D;

for k = 1 : n
	if Acol(k, k) == 0
		printf("Deu ruim\n");
	endif
	for i = k + 1 : n
		Acol(i, k) = Acol(i, k) / Acol(k, k);
	endfor
	for j = k + 1 : n
		for i = k + 1 : n
			Acol(i, j) -= Acol(k, j) * Acol(i, k);
		endfor
	endfor
endfor

C = triu(Acol, - 0);
printf("Acol =\n\n");
disp(Acol);
