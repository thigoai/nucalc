#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Raizes {
	float* arr;
	int size;
};

// needs a < b
struct Raizes isolar_raizes(float a, float b, float h, float (*f)(float)) {
	float* raizes = malloc(sizeof(float) * 100);
	int size = 0;
	float curr = a;

	while (curr < b) {
		if (f(curr) * f(curr + h) < 0) {
			raizes[size] = curr;
			raizes[size + 1] = curr + h;
			size+= 2;
		}

		curr += h;
	}

	struct Raizes r;
	r.arr = raizes;
	r.size = size;

	return r;
}

float func(float x) {
	return 2 * (x * x * x * x) + 4 * (x * x * x) + 3 * (x * x) - 10 * x - 15;
}

int main() {
	printf("Isolando as raizes...\n");
	struct Raizes r = isolar_raizes(-10, 10, 1, func);
	printf("Raizes isoladas\n");
	for (int i = 0; i < r.size; i+= 2) {
		printf("lower: %f, upper: %f\n", r.arr[i], r.arr[i+1]);
	}
	return 0;

}
