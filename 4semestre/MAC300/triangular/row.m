n = 2000;
A = tril(rand(n), 0);
b = randn(n,1);
x = b;
i = 0;
j = 0;

starttime = time;
for i = 1:n
	for j = 1:i-1
		x(i) = x(i) - A(i,j) * x(j);
	endfor
	if (A(i,i) == 0)
		disp("I can't deal with divisions by zero:(\n");
	else
		x(i) = x(i) / A(i,i);
	endif
endfor
totaltime = time - starttime;
disp(totaltime);		
%disp(x);

%{
printf("The matrices:\n");
printf("A:\n");
disp(A);
printf("b:\n");
disp(b);
printf("solved x:\n");
%}