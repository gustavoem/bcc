function retval = countIsoGroups(n)
	starttime = time;
	endtime = time
	sum = 1;
	meio = floor(n / 2)
	for i = 1:meio
		sum += countIsoGroups(n-i)
	endfor
	retval = sum
	
	printf("Numero de grupos isomorfos: %d\n", retval);
	printf("Tempo de execucao: %.5f segundos\n", endtime - starttime);
endfunction
