#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 128
#define PI 3.141592653589793
#define N 20

float inBuffer[MAX_SIZE] = {A_ARRAY};
float outBuffer[MAX_SIZE];

struct complex {
	float real;
	float image;
};

struct complex dft(float* x, int n, int k) {
	int i = 0;
	float resReal = 0;
	float resImage = 0;
	struct complex result;
	result.real = 0;
	result.image = 0;
	for(i = 0; i < n; i++) {
		resReal += (x[i] * cos(2 * PI * i * k / n));
		resImage -= (x[i] * sin(2 * PI * i * k / n));
	}
	result.real = resReal;
	result.image = resImage;
	return result;
}
//dop functionality
struct complex complexMul(struct complex a, struct complex b) {
	struct complex result;
	result.real = a.real * b.real - a.image * b.image;
	result.image = a.real * b.image + a.image * b.real;
	return result;
}
//dop functionality
struct complex complexAdd(struct complex a, struct complex b) {
	struct complex result;
	result.real = a.real + b.real;
	result.image = a.image + b.image;
	return result;
}
//dop functionality
float idft(struct complex* x, int n, int k) {
	float result = 0;
	struct complex temp;
	struct complex resTemp;
	int i = 0;
	resTemp.real = 0;
	resTemp.image = 0;
	for(i = 0; i < n; i++) {
		temp.real = cos(2 * PI * i * k / n);
		temp.image = sin(2 * PI * i * k /n);
		temp = complexMul(x[i], temp);
		resTemp = complexAdd(resTemp, temp);
	}
	result = resTemp.real + resTemp.image;
	result /= n;
	return result;
}
//achx of spectr
float curve(struct complex x) {
	return sqrt(x.real * x.real + x.image * x.image);
}

//rectangle window
void rect(float* inputData, float* outputData, int n) {
	int i = 0;
	for(i = 0; i < n; i++) {
		if(i < N) {
			outputData[i] = 1;
		} else {
			outputData[i] = 0;
		}
		outputData[i] *= inputData[i];
	}
}
//hamming window
void hamming(float* inputData, float* outputData, int n) {
	int i = 0;
	for(i = 0; i < n; i++) {
		if(i < N) {
			outputData[i] = (0.54 + 0.46 * cos(2 * PI * (i - (N - 1) / 2) / (N - 1)));
		} else {
			outputData[i] = 0;
		}
		outputData[i] *= inputData[i];
	}
}
//nattol window
void nattol(float* inputData, float* outputData, int n) {
	float arr[4] = {
		0.3636,
		0.4892,
		0.1366,
		0.0106
	};
	int i = 0;
	int j = 0;
	for(i = 0; i < n; i++) {
		outputData[i] = 0;
		if(i < N) {
			for(j = 0; j < 4; j++) {
	                outputData[i] += arr[j] * cos(2 * PI * j * (i - (N - 1) / 2) / (N - 1));
			}
		}
		outputData[i] *= inputData[i];
	}
}

void main() {
	int k = 0;
	struct complex spectrSignal;
	float arrToShow[MAX_SIZE];

	//spectr of input signal
	for(k = 0; k < MAX_SIZE; k++) {
		spectrSignal = dft(inBuffer, MAX_SIZE, k);
		arrToShow[k] = curve(spectrSignal);
	}
	//for normal view
	arrToShow[MAX_SIZE - 1] += 1;
	arrToShow[MAX_SIZE - 1] -= 1;

	k++;//for breakpoint

	//rectangle window
	rect(inBuffer, outBuffer, MAX_SIZE);
	//spectr of signal with window
	for(k = 0; k < MAX_SIZE; k++) {
		spectrSignal = dft(outBuffer, MAX_SIZE, k);
		arrToShow[k] = curve(spectrSignal);
	}
	//for normal view
	arrToShow[MAX_SIZE - 1] += 1;
	arrToShow[MAX_SIZE - 1] -= 1;

	k++;//for breakpoint

	//hamming window
	hamming(inBuffer, outBuffer, MAX_SIZE);
	//spectr of signal with window
	for(k = 0; k < MAX_SIZE; k++) {
		spectrSignal = dft(outBuffer, MAX_SIZE, k);
		arrToShow[k] = curve(spectrSignal);
	}
	//for normal view
	arrToShow[MAX_SIZE - 1] += 1;
	arrToShow[MAX_SIZE - 1] -= 1;


	k++;//for breakpoint
	
	//nattol window
	nattol(inBuffer, outBuffer, MAX_SIZE);
	//spectr of signal with window
	for(k = 0; k < MAX_SIZE; k++) {
		spectrSignal = dft(outBuffer, MAX_SIZE, k);
		arrToShow[k] = curve(spectrSignal);
	}
	//for normal view
	arrToShow[MAX_SIZE - 1] += 1;
	arrToShow[MAX_SIZE - 1] -= 1;

	k++;//for breakpoint
}
