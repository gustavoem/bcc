%not working
Ahr = D;

for k = 1 : n
	for j = 1 : k - 1
		for a = 1 : j - 1
			Ahr(k, j) -= Ahr(k, a) * Ahr(a, j);
		endfor
		Ahr(k, j) /= Ahr(k, k);
	endfor
	for j = k + 1 : n
		for a = 1 : k - 1
			Ahr(k, j) -= Ahr(k, a) * Ahr(a, j);
		endfor
	endfor
endfor

printf("Ahr =\n\n");
disp(Ahr);
