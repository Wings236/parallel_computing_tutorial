# Project 6: GPU Acceleration with CUDA

## Requirements

1. Implement the expression **B** = *a* **A** + *b*, where *a* and *b* are scalars, **A** and **B** are matrices of the same size. You can implement it by modifying the example `matadd.cu`.

2. Compare the matrix multiplication by OpenBLAS on CPU with that by cuBLAS on GPU. cuBLAS is a GPU-accelerated library provided by NVIDIA. Do not use some huge matrics, and 4096x4096 should be large enough. We have a lot of students to share the server. Surely you can use your computer if you have an NVIDIA GPU.

3. (Optional) Something interesting on GPU.

## Tips

1. The function in cuBLAS is `cublasSgemm()`.

2. Our course server will be very busy in the last few days to the deadline.
