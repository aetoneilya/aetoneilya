#include <vector>
#include <cmath>
#include "array_flow.h"

template <typename T>
int min_abs_el(std:: vector<T>& numbers) {
	T min = numbers[0];
	int  minInd = 0;
	for (int i = 0; i < numbers.size(); i++) {
		if (abs(numbers[i]) < min) {
			min = abs(numbers[i]);
			minInd = i;
		}
	}
	return minInd;
}

int sum_abs_after_neg(std::vector<double>& numbers) {
	int minIn = false;
	int sum = 0;
	
	//find minind
	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] < 0) {
			minIn = i;
			break;
		}
	}
	for (int i = minIn + 1; i < numbers.size(); i++) {
		sum += abs(numbers[i]);
	}
	return sum;
}

void del_values(std::vector<double>& numbers, double a, double b) {
	int lastZero = numbers.size() - 1 ;
	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] >= a && numbers[i] <= b) {
			//del_element(numbers, i);
			for (int j = i; j < numbers.size() - 1; j++) {
				numbers[j] = numbers[j + 1];
			}
			numbers[lastZero] = 0;
			lastZero--;
			i--;
			
		}
	}
}

int min_abs_el_arr(int *arr,int n) {
	double min = arr[0];
	int minInd = 0;
	for (int i = 0; i < n; i++) {
		if (abs(arr[i]) < min) {
			min = abs(arr[i]);
			minInd = i;
		}
	}
	return minInd;
}

int sum_abs_after_neg_arr(int* arr, int n) {
	int minIn = 0;
	bool negFind = false;
	int sum = 0;

	//find minind
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0) {
			minIn = i;
			negFind = true;
			break;
		}
	}
	if (negFind) {
		for (int i = minIn + 1; i < n; i++) {
			sum += abs(arr[i]);
		}
	}
	
	return sum;
}

void del_values_arr(int* arr, int n, double a, double b) {
	int lastZero = n - 1;
	for (int i = 0; i < n; i++) {
		if (arr[i] >= a && arr[i] <= b) {
			//del_element(numbers, i);
			//n--;
			for (int j = i; j < n - 1; j++) {
				arr[j] = arr[j + 1];
			}
			arr[lastZero] = 0;
			lastZero--;
			i--;

		}
	}
}