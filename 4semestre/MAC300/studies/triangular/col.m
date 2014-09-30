y = b;
b2 = b;
starttime = time;
for j = 1 : n
	if (A(j, j) != 0)
		b2(j) = b2(j) / A(j, j);
	endif
	for i = j + 2 : n
		b2(i) = b2(i) - A(i, j) * b2(j);
	endfor
endfor
totaltime = time - starttime;
disp(totaltime);		