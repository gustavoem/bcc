C = A;
R1 = chol(A)
for i = 1:n
	for k = 1:i-1
		C(i, i) = C(i, i) - C(k, i) * C(k, i);
	endfor
	if C(i, i)  <= 0
		printf("A não é def. pos.\n");
	endif
	C(i, i) = sqrt(C(i, i));
	for j = i+1:n
		for k = 1:i-1
			C(i, j) = C(i, j) - C(k, i) * C(k, j);
		endfor
		C(i, j) = C(i, j) / C(i, i);
	endfor
endfor
Ccol = C;
Ccol
