Aext = D;

for k = 1 : n
 	for i = k + 1 : n
 		Aext(i, k) /= Aext(k, k);
 	endfor
 	for i = k + 1 : n
 		for j = k + 1 : n
 			Aext(i, j) -= Aext(i, k) * Aext(k, j);
 		endfor
 	endfor
 endfor

printf("Aext =\n\n");
disp(Aext);
