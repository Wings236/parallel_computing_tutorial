CXX = nvcc
TARGERT = matmul
OBJ = main.c ./src/matrix.c ./src/SIMD_matrix.c ./src/thread_matrix.c ./src/cuda_matrix.cu
# CFLAG =
# CFLAG = -O3 -fopenmp
CFLAG = -O3
# CFLAG = -O3 -mavx2
INCLUDE = -I./include

$(TARGERT): $(OBJ) $(CUDA_OBJ)
	$(CXX) $(CFLAG) $(INCLUDE) -o $(TARGERT) $(OBJ) $(CUDA_OBJ)


.PHONY: clean
clean:
	rm -f matmul