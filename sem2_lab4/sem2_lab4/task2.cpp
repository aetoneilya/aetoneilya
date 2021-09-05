#include <vector>
#include <cmath>
#include "array_flow.h"


void shakerSort_fromto(std::vector <double>& vector, int l, int r) {
	
	l--;
	r--;

	while (r > l) {
		for (int i = l; i < r; i++) {
			if (vector[i] > vector[i + 1]) { 
				double tmp = vector[i];
				vector[i] = vector[i + 1];
				vector[i + 1] = tmp; }
		}
		r--;
		for (int i = r; i > l; i--) {
			if (vector[i] < vector[i - 1]) {
				double tmp = vector[i];
				vector[i] = vector[i - 1];
				vector[i - 1] = tmp;
			}
		}
		l++;
	}
}