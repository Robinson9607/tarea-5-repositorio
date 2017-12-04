all: Resultados_hw5.pdf clean

Resultados_hw5.pdf : modelo.png
	pdflatex Resultados_hw5.tex

modelo.png : modelo.txt
	python Plots.py

modelo.txt : CurvasRotacion.c
	cc -o a.o CurvasRotacion.c -lm
	./a.o
	
clean:
	-rm modelo.png modelo.txt rta.txt a.o Resultados_hw5.aux Resultados_hw5.log Resultados_hw5.out
