all: tmc sample gmc mcmc

tmc: tmc.c
	gcc -std=c99 -pedantic -Wall tmc.c -lm -o tmc

sample: sample.c
	gcc -std=c99 -pedantic -Wall sample.c -lm -o sample

gmc: gmc.c
	gcc -std=c99 -pedantic -Wall gmc.c -lm -o gmc

mcmc: mcmc.c
	gcc -std=c99 -pedantic -Wall mcmc.c -lm -o mcmc

clean:
	rm tmc sample gmc mcmc