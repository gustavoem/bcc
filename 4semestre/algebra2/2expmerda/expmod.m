x = 1;
for i = 1 : n
	x = mod(x * 2, 100);
	printf("2 ^ %d =  %d mod 100\n", i, x);
endfor
