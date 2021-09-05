#include <cmath>
#include <map>
#include <iostream>


template <typename T>
//template <typename D>
std::ostream& operator<<(std::ostream& os, std::map<T, T> map) {
    for (auto pair : map) {
        os << pair.first << " " << pair.second << "\n" ;
    }
    return os;
}

int mod_compare(int num, int pow, int mod) {

    pow = pow % (mod - 1);
    num %= mod;

    int result = 1;
    for (int i = 1; i <= pow; i++) {
        result *= num;
        result %= mod;
    }
    return(result);
}

int baby_giant_step(int g, int h, int p) {
	int N = sqrt(p - 1);
    std::cout << "N = " << N << std::endl;

    //baby steps
	std::map <int, int> baby_step;
	for (int i = 0; i < N; i++) {
        baby_step[mod_compare(g, i, p)] = i;
	}
    //std::cout << "Baby steps:\n";
    //std::cout << baby_step << std::endl;

    //little ferma theorem
    int c = mod_compare(g, N * (p - 2), p);
    
    //giant steps
    for (int i = 0; i < N; i++) {
        int y = h * mod_compare(c, i, p) % p;
        for (std::pair <int, int> item : baby_step) {
            if (y == item.first) {
                return (i * N + baby_step[y]);
            }
        }
    }
    return 0;
}