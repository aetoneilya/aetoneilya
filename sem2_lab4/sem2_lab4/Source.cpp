#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <fstream>
#include "array_flow.h"
#include "task1.h" 
#include "task2.h" 
#include "task3.h" 
#include "task4.h" 

//questions :
//what do i have tot do to make templates work in functions that exist outside of Source.cpp?

using namespace std;


//ostream& operator<<(ostream& os, int  array[]) {
//
//	return os;
//}

template <typename T>
ostream& operator<<(ostream& os, vector<T> vector) {
	for (auto num : vector) {
		os << num << " " ;
	}
	return os;
}


template <typename T>
istream& operator>>(istream& is, vector<T> &vector)  {
	for (int i = 0; i < vector.size(); i++) {
		is >> vector.at(i);
	}
	return is;
}

template <typename T>
ifstream& operator>>(ifstream& input, vector<T>& vector)
{
	for (int i = 0; i < vector.size(); i++) {
		input >> vector.at(i);
	}
	return input;
}

void instruction() {
	cout << "Enter task number from 1 up to 4\n0 to exit" << endl;
}

int main() {
	ifstream in("text.txt");
	cout << "You are welcome at the lab 4" << endl;
	
	int control = 10;
	while (control) {
		switch (control)
		{
		case 10:
			cout << "1 - task 1\n2 - task 2\n3 - task 4\n4 - task 4\n5 - vector in memory\n0 - break\n";
			break;
		case 1: {
			cout << "task 1\n";
			int n = 0;
			cout << "Enter array size: ";
			cin >> n;
			while (n < 1) {
				cout << "The number of elements must be greater than 0." << endl;
				cout << "Enter it again: " << endl;
			}
			//vector <double> numbers(n);

			//scan_double(numbers,n); 
		//	cin >> numbers;

			//add switch
			//cout << "minimum modulo element index: " << min_abs_el(numbers) << endl;
			//cout << "sum of modulo elements after negative number: " << sum_abs_after_neg(numbers) << endl;
			//add input 3 6.5
			//del_values(numbers, 3, 6.5);
			int* arr = new int[n];
			for (int i = 0; i < n; i++) {
				cin >> arr[i];
			}
			cout << "Minimum modulo element index: " << min_abs_el_arr(&arr[0], n) << endl;
			cout << "Sum of modulo elements after negative number: " << sum_abs_after_neg_arr(&arr[0], n) << endl;

			cout << "Deleting numbers between a and b.\n";

			double a, b;
			cout << "Enter a: ";
			cin >> a;
			while (a < 0) {
				cout << "Incorrect input, a must be greater than 0" << endl;
				cout << "Enter it again: " << endl;
				cin >> a;
			}
			cout << "Enter b: ";
			cin >> b;
			while (b < a) {
				cout << "Incorrect input, b must be greater than a" << endl;
				cout << "Enter it again: " << endl;
				cin >> b;
			}

			del_values_arr(&arr[0], n, a, b);

			for (int i = 0; i < n; i++) {
				cout << arr[i] << ' ';
			}
			cout << endl;
			break;
		}
		case 2: {
			cout << "Sort vector from a to b:\n";
			int n = 0;
			cout << "Enter array size: ";
			cin >> n;
			while (n < 1) {
				cout << "The number of elements must be greater than 0." << endl;
				cout << "Enter it again: " << endl;
				cin >> n;
			}

			vector <double> numbers(n);
			mt19937_64 ran(time(0));
			cout << "1 - values fills randomly\n2 - values fills manualy\n3 - values fills from file text.txt\n";
			int choise;
			cin >> choise;

			if (choise == 1) {
				for (int i = 0; i < n; i++) numbers[i] = ran() % 20000 / 100. - 100;
			}
			if (choise == 2) {
				cout << "Enter " << n << " values:\n";
				cin >> numbers;
			}
			else {
				in >> numbers;
			}
			int a, b;
			cout << "Enter a: ";
			cin >> a;
			while (a < 1) {
				cout << "Incorrect input, a must be greater than 1" << endl;
				cout << "Enter it again: " << endl;
				cin >> a;
			}
			cout << "Enter b: ";
			cin >> b;
			while (b < a || b > n) {
				cout << "Incorrect input" << endl;
				cout << "Enter it again: " << endl;
				cin >> b;
			}
			//shakerSort_fromto(numbers, a, b);
			auto f = [](vector <double>& vector, int lhs, int rhs) {

				lhs--;
				rhs--;

				while (rhs > lhs) {
					for (int i = lhs; i < rhs; i++) {
						if (vector[i] > vector[i + 1]) {
							double tmp = vector[i];
							vector[i] = vector[i + 1];
							vector[i + 1] = tmp;
						}
					}
					rhs--;
					for (int i = rhs; i > lhs; i--) {
						if (vector[i] < vector[i - 1]) {
							double tmp = vector[i];
							vector[i] = vector[i - 1];
							vector[i - 1] = tmp;
						}
					}
					lhs++;
				}};
			f(numbers, a, b);
			cout << numbers << endl;
			break;
		} 
		case 3: {
			vector <int>  fifty(50);
			vector <int>  hundred(100);
			vector <int> thousand(1000);

			mt19937_64 ran(time(0));
			for (int i = 0; i < 50; i++) fifty[i] = (ran() % 100) + 1;
			for (int i = 0; i < 100; i++) hundred[i] = (ran() % 100) + 1;
			for (int i = 0; i < 1000; i++) thousand[i] = (ran() % 100) + 1;
			
			cout << "Numerical characteristics for fifty" << endl;
				cout << "\tHi-square: " << hi_square(fifty) << endl;
				cout << "\tMath exp: " << math_exp(fifty) << endl;
				cout << "\tGeneral dispersion: " << gen_dispersion(fifty) << endl;
			cout << "Numerical characteristics for hundred" << endl;
				cout << "\tHi-square: " << hi_square(hundred) << endl;
				cout << "\tMath exp: " << math_exp(hundred) << endl;
				cout << "\tGeneral dispersion: " << gen_dispersion(hundred) << endl;
			cout << "Numerical characteristics for thousand" << endl;
				cout << "\tHi-square: " << hi_square(thousand) << endl;
				cout << "\tMath exp: " << math_exp(thousand) << endl;
				cout << "\tGeneral dispersion: " << gen_dispersion(thousand) << endl;
			break;
		}
		case 4:
			int g, y, p;
			cout << "This part of code solves y = g^x (mod p)\n";
			cout << "Enter g : ";
			cin >> g;
			cout << "Enter y : ";
			cin >> y;
			cout << "Enter p : ";
			cin >> p;
			cout << "X = " << baby_giant_step(g, y, p) << endl;
			break;
		case 5: {
			cout << endl;
			vector<int> vect(10);
			cout << "Created vector of 10 ints\n";
			vector<int>* p = &vect;
			
			cout << "Vector located at " << p << endl;
			
			cout << "vector elements address:\n";
			for (int i = 0; i < vect.size(); i++) {
				cout << "&a[" << i << "] = " << &vect.at(i) << endl;
			}

			cout << "Push back element" << endl;
			vect.push_back(1);
			
			cout << "Vector located at " << p << endl;
			cout << "vector elements address:\n";
			for (int i = 0; i < vect.size(); i++) {
				cout << "&a[" << i << "] = " << &vect.at(i) << endl;
			}

			break; }
		default:
			cout << "Incorrect input, please repeat\n" << endl;
			instruction();
			break;
		}
		cout << "What do you want to see? : ";
		cin >> control;
	}

}
