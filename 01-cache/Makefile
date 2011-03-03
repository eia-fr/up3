
WIDTH=15000
HEIGHT=200
REPETITIONS=2000

good: good.c
	gcc good.c -o good
	
bad: bad.c
	gcc bad.c -o bad
	
timeit: good bad
	@echo Timing a $(WIDTH) x $(HEIGHT) sized matrix for $(REPETITIONS) times:
	@./bad $(WIDTH) $(HEIGHT) $(REPETITIONS)
	@./good $(WIDTH) $(HEIGHT) $(REPETITIONS)
	
measure: measure.c
	gcc measure.c -o measure

complex: complex.c
	gcc complex.c -o complex

clean:
	rm -f measure bad good complex *.out