#include <iostream>
#include <vector>


void swap(double& a, double& b) {
	double tmp = a;
	a = b;
	b = tmp;
}

void scan_double(std::vector <double>& vector, int n) {
		for (int i = 0; i < n; i++) {
		std::cin >> vector.at(i);
	}
}

void del_element(std::vector <double>& vector, int del_id) {
	for (int i = del_id; i < vector.size() - 1; i++) {
		vector[i] = vector[i + 1];
	}
	for (int i = vector.size() - 1; i > 0; i--) {
		if (vector[i] != 0) {
			vector[i] = 0;
			break;
		}
	}
}

void shakerSort(std::vector <double>& vector){
	int N = vector.size();
	int l = 0;
	int r = N - 1;
	while (r > l) {
		for (int i = l; i < r; i++) {
			if (vector[i] > vector[i + 1]) { swap(vector[i], vector[i + 1]); }
		}
		r--;
		for (int i = r; i > l; i--) {
			if (vector[i] < vector[i - 1]) { swap(vector[i], vector[i - 1]); }
		}
		l++;
	}
}
