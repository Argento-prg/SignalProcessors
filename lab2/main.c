#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define FILEPATH "Image2.dat"
#define FILEPATH_OUTPUT "outputImage.dat"
#define MAX_BUFFER 5
#define BLOCK_LENGTH 8
#define PI 3.141592653589793
#define LIMIT 13

int readFileBlock(FILE* file, float* arr, int lengthBuffer);
void dctMatrixGenerate(float* arr, int size);
void transposeMatrix(float* arr, float* out, int size);
void matrixProduct(float* arrA, float* arrB, float* output, int size);
void compress(float* arr, int lengthBuffer, int limit);

void main() {
	FILE* file = fopen(FILEPATH, "r");
    FILE* outputFile = fopen(FILEPATH_OUTPUT, "w");
    int count = 1;
    int i = 0;
    float arr[BLOCK_LENGTH * BLOCK_LENGTH];
    float dctMatrix[BLOCK_LENGTH * BLOCK_LENGTH];
    float dctMatrixTrans[BLOCK_LENGTH * BLOCK_LENGTH];
    float outputTemp[BLOCK_LENGTH * BLOCK_LENGTH];
    float output[BLOCK_LENGTH * BLOCK_LENGTH];

    dctMatrixGenerate(dctMatrix, BLOCK_LENGTH);
    transposeMatrix(dctMatrix, dctMatrixTrans, BLOCK_LENGTH);

    while(count > 0) {
        count = readFileBlock(file, arr, BLOCK_LENGTH * BLOCK_LENGTH);
        matrixProduct(dctMatrix, arr, outputTemp, BLOCK_LENGTH);
        matrixProduct(outputTemp, dctMatrixTrans, output, BLOCK_LENGTH);
        //compress image
        compress(output, BLOCK_LENGTH * BLOCK_LENGTH, LIMIT);
        //reverse
        matrixProduct(dctMatrixTrans, output, outputTemp, BLOCK_LENGTH);
        matrixProduct(outputTemp, dctMatrix, output, BLOCK_LENGTH);
        for(i = 0; i < BLOCK_LENGTH * BLOCK_LENGTH; i++) {
            fprintf(outputFile, "%d\n", (int)(output[i] + 128));
        }
    }
    fclose(outputFile);
	fclose(file);
}

int readFileBlock(FILE* file, float* arr, int lengthBuffer) {
    int count = 0;
    while(count != lengthBuffer) {
        arr[count] = 0;
        int err = fscanf(file, "%f\n", &arr[count]);
        if(err == EOF) {
            break;
        }
        arr[count] -= 128;
        count++;
    }
    return count;
}

void dctMatrixGenerate(float* arr, int size) {
    int row;
    int col;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            if(row == 0) {
                arr[row * size + col] = 1 / sqrt(size);
                arr[row * size + col] *= cos((2 * col + 1) * row * PI / (2 * size));
            } else {
                arr[row * size + col] = sqrt(2.0 / size);
                arr[row * size + col] *= cos((2 * col + 1) * row * PI / (2 * size));
            }
        }
    }
}

void transposeMatrix(float* arr, float* out, int size) {
    int row;
    int col;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            out[col * size + row] = arr[row * size + col];
        }
    }
}

void matrixProduct(float* arrA, float* arrB, float* output, int size) {
    int row;
    int col;
    int k;
    for(row = 0; row < size; row++) {
        for(col = 0; col < size; col++) {
            output[row * size + col] = 0;
            for(k = 0; k < size; k++) {
                output[row * size + col] += arrA[row * size + k] * arrB[k * size + col];
            }
        }
    }
}

void compress(float* arr, int lengthBuffer, int limit) {
    int count;
    for(count = limit; count < lengthBuffer; count++) {
        arr[count] = 0;
    }
}