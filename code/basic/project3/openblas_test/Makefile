matmul: test_cblas.c ../src/matrix.c
	gcc -O3 test_cblas.c ../src/matrix.c -o test_cblas  -lopenblas -I../include

.PHONY: clean
clean:
	rm -f test_cblas