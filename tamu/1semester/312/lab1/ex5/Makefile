all:
	gcc -o prob54 lab1_prob54_framework.c -lrt; 
	gcc -o prob53 lab1_prob53_framework.c -lrt
	

run: prob54 prob53
	./prob54 < input4.txt > output4.txt; 
	./prob53 < input3.txt > output3.txt


clean:
	rm prob53;
	rm prob54;
