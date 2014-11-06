j1 = ones(5,1)
j2 = 1:.5:3;
j2 = j2';
A = [j1 j2];
b = [1.1, 1.2, 1.3, 1.3, 1.4];
b = b';
x = A \ b
px = polyout(x, 'x')
plot(j2, b);

