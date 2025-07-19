CXX = gcc
TARGERT = matmul
OBJ = main.c ./src/matrix.c
INCLUDE = -I./include

$(TARGERT): $(OBJ)
	$(CXX) -o $(TARGERT) $(OBJ) $(INCLUDE)

.PHONY: clean
clean:
	rm -f matmul