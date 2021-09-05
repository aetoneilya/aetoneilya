#include <vector>

//hi-square
double hi_square(std::vector<int>& ranNum) {
	double Vexp = ranNum.size() / 100.;
	int values[100] = { 0 };
	for (auto num : ranNum) {
		values[num - 1]++;
	}
	 
	double sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += (values[i] - Vexp) * (values[i] - Vexp) / Vexp;
	}
	return sum;
}

double math_exp(std::vector<int>& ranNum) {
	double sum = 0;
	for (int i = 0; i < ranNum.size(); i++) {
		sum += ranNum[i];
	}
	return (sum / ranNum.size());
}

double gen_dispersion(std::vector<int>& ranNum) {
	double sum = 0;
	double average = math_exp(ranNum);
	for (int i = 0; i < ranNum.size(); i++) {
		sum += (ranNum[i] - average)*(ranNum[i] - average);
	}
	return (sum / ranNum.size());
}
