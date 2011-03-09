
ARRAY_SIZE=400000000

initial: initial.c
	gcc initial.c -o initial

firstOptimisation: firstOptimisation.c
	gcc firstOptimisation.c -o firstOptimisation

secondOptimisation: secondOptimisation.c
	gcc secondOptimisation.c -o secondOptimisation

thirdOptimisation: thirdOptimisation.c
	gcc thirdOptimisation.c -o thirdOptimisation

timeit: initial firstOptimisation secondOptimisation thirdOptimisation
	@echo Timing a array for an array of $(ARRAY_SIZE) int:
	@./initial $(ARRAY_SIZE)
	@./firstOptimisation $(ARRAY_SIZE)
	@./secondOptimisation $(ARRAY_SIZE)
	@./thirdOptimisation $(ARRAY_SIZE)


clean:
	rm -f initial firstOptimisation secondOptimisation thirdOptimisation
