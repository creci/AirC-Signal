all: run

resampler.o: resampler.c resampler.h cmn_defs.h
	gcc -c resampler.c

generator.o: generator.c generator.h cmn_defs.h
	gcc -c generator.c

file.o: file.c file.h cmn_defs.h
	gcc -c file.c

setting.o: setting.c setting.h cmn_defs.h resampler.h
	gcc -c setting.c

menu.o: menu.c menu.h generator.h
	gcc -c menu.c

main.o: main.c menu.h
	gcc -c main.c

run: main.o generator.o file.o setting.o menu.o resampler.o
	gcc -o run main.o generator.o file.o setting.o menu.o resampler.o -lm
clean:
	rm -rf run *.o
