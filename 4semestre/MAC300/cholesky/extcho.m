C = A;
R1 = chol(A)
for k = 1:n
	if (C(k, k) <= 0)
		printf("A não é definida positiva\n");
	endif
	C(k, k) = sqrt(C(k, k));
	for i = k+1:n
		C(i, k) /= C(k, k);
	endfor
	for i = k+1:n
		for j = k+1:i
			C(i, j) -= C(i, k) * C(j, k);
		endfor
	endfor
endfor
Cext = C;
Cext