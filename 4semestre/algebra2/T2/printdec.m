function printdec(n, depth)
	meio = floor(n / 2);
	i = n;
	while (i >= meio)
		printf("\n");
		printf("%d ", i);
		%for j = 1:depth
		%	printf(" ");
		%endfor
		printdec(n - i, depth + 1)
		i -= 1;
	endwhile
endfunction