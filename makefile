build-table:
	gcc -o ignore/table table.c

run-table:
	./ignore/table

all-table : build-table run-table

build-counter:
	gcc -o ignore/counter counter.c

run-counter:
	./ignore/counter

all-counter : build-counter run-counter
