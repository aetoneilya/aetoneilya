#include <iostream>
#include <random>
#include <time.h>

using namespace std;

struct number { int value, use; };

void order(number *numbers, int prev, int you, int size)
{
    char c,s[10];
    if (prev >= 0) c = numbers[prev].value % 10 + '0';
    int was = 0;

    for (int i = 0; i < size; i++)
        if ( numbers[i].use < 0 && (prev < 0 || c == *itoa(numbers[i].value, s, 10)))
        {
            numbers[i].use = you;
            order(numbers, i, you + 1, size);
            numbers[i].use =- 1;
            was = 1;
        }

    if (!was && you > 2)
    {
        for (int i = 0; i < you; i++)
            for (int k = 0; k < size; k++)
                if ( numbers[k].use == i )
                {
                    cout << numbers[k].value <<" ";
                    break;
                }
        cout << endl;
    }
}


int main ()			 //int argc, char **argv)
{
    int size = 10;
    number *numbers = new number[size];

    srand(time(0));

    for (int i=0; i < size; i++)
    {
        numbers[i].value = rand()%100;
        numbers[i].use =- 1;
        cout << numbers[i].value <<  " " ;
    } 

    cout << "\n\n";
	cout << "Combinations: " << endl;
    order(numbers, -1, 0, size);
	int n;
	cin >> n;
    delete[] numbers;
	return 0;
}