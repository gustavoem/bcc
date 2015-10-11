all:
	gcc -o  sol1 lab3_prob1sol1.c
	gcc -o  sol2 lab3_prob1sol2.c
	gcc -o  sol3 lab1_prob4_framework.c

run: sol1 sol2
	./sol1 < input.txt > output.txt
	./sol2 < input.txt >> output.txt
	./sol3 < input.txt >> output.txt
	cat output.txt
