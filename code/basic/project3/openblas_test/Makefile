CXX = gcc
TARGERT = matmul

matmul: test_cblas.c ../src/matrix.c
	gcc test_cblas.c ../src/matrix.c -o test_cblas  -lopenblas -I../include