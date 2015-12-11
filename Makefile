all: sequencia beamsearch branchbound skewheap trab3 doc

all-nodoc: sequencia beamsearch branchbound skewheap trab3

sequencia: sequencia.c
	gcc -Wall -c sequencia.c
	
beamsearch: beamsearch.c
	gcc -Wall -c beamsearch.c

branchbound: branchbound.c
	gcc -Wall -c branchbound.c
	
skewheap: skewheap.c
	gcc -Wall -c skewheap.c

trab3: sequencia.o beamsearch.o branchbound.o skewheap.o main.c
	gcc -Wall -o trab3 sequencia.o beamsearch.o branchbound.o skewheap.o main.c

doc: doc.tex
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode" -use-make doc.tex

clean-nodoc:
	rm *.o trab3

clean: 
	rm *.o trab3 doc.pdf doc.log doc.fls doc.aux doc.fdb_latexmk
	

