#include <iostream>
#include <random>
#include <time.h>
#include <vector>

using namespace std;

struct number
{
    int value;
    int place;
};

int first_digit(int number)
{
    while (number > 9)
    {
        number /= 10;
    }
    return number;
}

void nums_order(vector<number> &numbers, int past_num, int num_in_seq, int &size)
{
    bool numAdded = false;

    for (int i = 0; i < size; i++)
    {
        if (past_num == -1 || (numbers[i].place == -1 && first_digit(numbers[i].value) == past_num % 10))
        {
            numbers[i].place = num_in_seq;
            nums_order(numbers, numbers[i].value, num_in_seq + 1, size);
            numbers[i].place = -1;
            numAdded = true;
        }
    }

    if (!numAdded && num_in_seq > 2)
    {
        for (int i = 0; i < num_in_seq; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (numbers[j].place == i)
                {
                    cout << numbers[j].value << " ";
                    break;
                }
            }
        }
        cout << endl;
    }
}

int main()
{

    int size = 9;
    vector<number> numbers(size);

    srand(time(0));

    cout << "Generated nums: ";
    for (int i = 0; i < size; i++)
    {
        numbers[i].value = rand() % 100;
        numbers[i].place = -1;
        cout << numbers[i].value << " ";
    }
    cout << "\n\n";
    cout << "Combinations: " << endl;
    nums_order(numbers, -1, 0, size);
}