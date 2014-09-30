Arow = D;

for k = 1 : n
	if Arow(k, k) == 0
		printf("Deu ruim\n");
	endif
	for i = k + 1 : n
		Arow(i, k) = Arow(i, k) / Arow(k, k);
		for j = k + 1 : n
			Arow(i, j) -= Arow(k, j) * Arow(i, k);
		endfor
	endfor
endfor

printf("Arow =\n\n");
disp(Arow);

