// ttypes.cu - CUDA Optimized T81 Arithmetic
#include "ttypes.h"
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_81 81
#define THREADS_PER_BLOCK 256

// **CUDA Kernel: BigInt Addition**
__global__ void t81bigint_add_cuda(int* a, int* b, int* result, int n) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < n) {
        result[idx] = (a[idx] + b[idx]) % BASE_81;
    }
}

// **CUDA Kernel: BigInt Multiplication**
__global__ void t81bigint_mul_cuda(int* a, int* b, int* result, int n) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < n) {
        result[idx] = (a[idx] * b[idx]) % BASE_81;
    }
}

// **CUDA Kernel: Matrix Multiplication**
__global__ void matrix_mult_cuda(int* A, int* B, int* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        int sum = 0;
        for (int k = 0; k < N; k++) {
            sum += (A[row * N + k] * B[k * N + col]) % BASE_81;
        }
        C[row * N + col] = sum % BASE_81;
    }
}

// **CUDA Wrapper for BigInt Add**
void t81bigint_add_gpu(int* h_a, int* h_b, int* h_result, int n) {
    int *d_a, *d_b, *d_result;
    size_t size = n * sizeof(int);
    
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_result, size);
    
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);
    
    int blocks = (n + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;
    t81bigint_add_cuda<<<blocks, THREADS_PER_BLOCK>>>(d_a, d_b, d_result, n);
    
    cudaMemcpy(h_result, d_result, size, cudaMemcpyDeviceToHost);
    
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);
}

// **CUDA Wrapper for Matrix Multiplication**
void t81matrix_multiply_gpu(int* h_A, int* h_B, int* h_C, int N) {
    int *d_A, *d_B, *d_C;
    size_t size = N * N * sizeof(int);
    
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);
    
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((N + 15) / 16, (N + 15) / 16);
    matrix_mult_cuda<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, N);
    
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

// **Main Function for Testing**
int main() {
    printf("CUDA T81 Ternary System - GPU Accelerated\n");

    // Test BigInt Add
    int h_a[4] = {10, 20, 30, 40};
    int h_b[4] = {5, 15, 25, 35};
    int h_result[4];
    
    t81bigint_add_gpu(h_a, h_b, h_result, 4);
    printf("BigInt Add (GPU): %d %d %d %d\n", h_result[0], h_result[1], h_result[2], h_result[3]);

    // Test Matrix Multiplication
    int N = 4;
    int h_A[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int h_B[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int h_C[16];

    t81matrix_multiply_gpu(h_A, h_B, h_C, N);
    printf("Matrix Multiply (GPU): %d %d %d %d ...\n", h_C[0], h_C[1], h_C[2], h_C[3]);

    return 0;
}
