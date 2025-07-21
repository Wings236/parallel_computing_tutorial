CXX = gcc
TARGERT = matmul
OBJ = main.c ./src/matrix.c ./src/SIMD_matrix.c
CFLAG = 
# CFLAG = -O3
# CFLAG = -O3 -mavx2
INCLUDE = -I./include

$(TARGERT): $(OBJ)
	$(CXX) $(CFLAG) $(INCLUDE) -o $(TARGERT) $(OBJ)

.PHONY: clean
clean:
	rm -f matmul