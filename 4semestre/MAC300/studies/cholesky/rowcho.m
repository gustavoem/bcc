C = A;
R1 = chol(A)
for j = 1:n
	for k = 1:j-1
		C(j, j) -= C(j, k) * C(j, k);
	endfor
	if C(j, j) <= 0
		printf("A não é def pos\n");
	endif
	C(j, j) = sqrt(C(j, j));
	for i = j + 1:n
		for k = 1:j - 1
			C(i,j) -= C(i, k) * C(j, k);
		endfor
		C(i, j) /= C(j, j);
	endfor
endfor
Crow = C;
Crow