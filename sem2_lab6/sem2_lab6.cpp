#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, vector<vector<T>> &matrix)
{
    int M = matrix.size();
    int N = matrix[0].size();
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, vector<T> vector)
{
    for (auto num : vector)
    {
        os << num << " ";
    }
    return os;
}

template <typename T>
T max_in_vector(vector<T> vector)
{
    int max_in = 0;

    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] > vector[max_in])
        {
            max_in = i;
        }
    }
    return (vector[max_in]);
}

template <typename T>
void snake_print(vector<vector<T>> &matrix)
{
    int M = matrix.size();
    int N = matrix[0].size();

    for (int i = 0; i < M; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < N; j++)
                cout << matrix[i][j] << ' ';
        }
        else
        {
            for (int j = N - 1; j >= 0; j--)
                cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

template <typename T>
void delete_row(vector<vector<T>> &matrix, int row_in)
{
    row_in--;
    matrix.erase(matrix.begin() + row_in);
}

template <typename T>
vector<T> maxrow_minclumn(vector<vector<T>> &matrix)
{
    int M = matrix.size();
    int N = matrix[0].size();
    vector<int> rowsMax(M);
    for (int i = 0; i < M; i++)
    {
        int maxValue = matrix[i][0];
        int maxInd = 0;
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] > maxValue)
            {
                maxValue = matrix[i][j];
                maxInd = j;
            }
        }
        rowsMax[i] = maxInd;
    }

    vector<int> columnsMin(N);
    for (int j = 0; j < N; j++)
    {
        int minValue = matrix[0][j];
        int minInd = 0;
        for (int i = 0; i < M; i++)
        {
            if (matrix[i][j] < minValue)
            {
                minValue = matrix[i][j];
                minInd = i;
            }
        }
        columnsMin[j] = minInd;
    }

    vector<T> results;
    for (int i = 0; i < M; i++)
    {
        if (columnsMin[rowsMax[i]] == i)
        {
            results.push_back(matrix[i][rowsMax[i]]);
        }
    }
    return results;
}

template <typename T>
void swap_row(vector<vector<T>> &matrix, int i, int j)
{
    vector<T> temp = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = temp;
}

template <typename T>
void gaus_solve(vector<vector<T>> matrix, vector<T> &X, vector<T> B)
{
    int size = matrix.size();
    vector<vector<T>> prev_step_matrix = matrix;

    for (int k = 0; k < size; k++)
    {
        for (int i = k + 1; i < size; i++)
        {
            B[i] = B[i] - prev_step_matrix[i][k] * B[k] / prev_step_matrix[k][k];
            for (int j = k + 1; j < size; j++) // кажеться здесь я исправил ошибку в алгоритме заменил j = i  на j = k + 1
            {
                matrix[i][j] = prev_step_matrix[i][j] - prev_step_matrix[i][k] * prev_step_matrix[k][j] / prev_step_matrix[k][k];
            }
        }
        cout << prev_step_matrix << endl;
        prev_step_matrix = matrix;
        
    }
    for (int i = 1; i < size; i++)
        for (int j = 0; j < i; j++)
            matrix[i][j] = 0;

    cout << "matrix left : \n"
         << matrix << endl
         << "matrix right : \n "
         << B << endl;

    for (int k = size - 1; k > -1; k--)
    {
        double sum = 0;
        for (int j = k + 1; j < size; j++)
        {
            sum += matrix[k][j] * X[j];
        }
        X[k] = (B[k] - sum) / matrix[k][k];
    }
    cout << "X = " << X << endl;
}

template <typename T>
void choise_gaus_solve(vector<vector<T>> matrix, vector<T> &X, vector<T> B)
{
    int size = matrix.size();
    vector<vector<T>> prev_step_matrix = matrix;

    for (int k = 0; k < size; k++)
    {
        int max_ind = k;
        for (int i = k; i < size; i++)
        {
            if (matrix[i][k] > matrix[max_ind][k])
            {
                max_ind = i;
            }
        }
        swap_row(matrix, k, max_ind);

        for (int i = k + 1; i < size; i++)
        {
            B[i] = B[i] - prev_step_matrix[i][k] * B[k] / prev_step_matrix[k][k];
            for (int j = k + 1; j < size; j++) // кажеться здесь я исправил ошибку в алгоритме заменил j = i  на j = k + 1
            {
                matrix[i][j] = prev_step_matrix[i][j] - prev_step_matrix[i][k] * prev_step_matrix[k][j] / prev_step_matrix[k][k];
            }
        }
        cout << prev_step_matrix << endl;
        prev_step_matrix = matrix;
    }

    for (int i = 1; i < size; i++)
        for (int j = 0; j < i; j++)
            matrix[i][j] = 0;

    cout << "matrix left : \n"
         << matrix << endl
         << "matrix right : \n "
         << B << endl;

    for (int k = size - 1; k > -1; k--)
    {
        double sum = 0;
        for (int j = k + 1; j < size; j++)
        {
            sum += matrix[k][j] * X[j];
        }
        X[k] = (B[k] - sum) / matrix[k][k];
    }
    cout << "X = " << X << endl;
}

template <typename T>
void iteration(vector<vector<T>> matrix_A, vector<T> &X, vector<T> B, double eps)
{
    vector<vector<T>> matrix_C = matrix_A;
    vector<T> matrix_f = B;
    int size = matrix_A.size();
    for (int i = 0; i < size; i++)
    {
        matrix_C[i][i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_C[i][j] = -1. * matrix_C[i][j] / matrix_A[i][i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        matrix_f[i] /= matrix_A[i][i];
    }

    vector<double> prev_X = matrix_f;

    while (abs(max_in_vector(X) - max_in_vector(prev_X)) > eps)
    {
        prev_X = X;
        for (int i = 0; i < size; i++)
        {
            double sum = 0;
            for (int j = 0; j < size; j++)
            {
                sum += matrix_C[i][j] * prev_X[j];
            }
            X[i] = matrix_f[i] + sum;
        }
        cout << prev_X << endl;
    }
    cout << "X = " << X << endl;
}

string vigenere_encrypt(string message, string key)
{
    int keyLen = key.size();

    for (int i = 0, j = 0; i < message.size(); i++)
    {
        if (message[i] > 64 && message[i] < 91)
        {
            message[i] += key[j % keyLen] - 'a';
            j++;
            if (message[i] > 90)
                message[i] -= 26;
        }
        else if (message[i] > 96 && message[i] < 123)
        {
            message[i] -= 32;
            message[i] += key[j % keyLen] - 'a';
            j++;
            if (message[i] > 90)
            {
                message[i] -= 26;
            }
            message[i] += 32;
        }
    }
    return message;
}

string vigenere_decrypt(string message, string key)
{
    int keyLen = key.size();
    for (int i = 0, j = 0; i < message.size(); i++)
    {
        if (message[i] > 64 && message[i] < 91)
        {
            message[i] -= key[j % keyLen] - 'a';
            j++;
            if (message[i] < 65)
                message[i] += 26;
        }
        else if (message[i] > 96 && message[i] < 123)
        {
            message[i] -= 32;
            message[i] -= key[j % keyLen] - 'a';
            j++;
            if (message[i] < 65)
                message[i] += 26;

            message[i] += 32;
        }
    }
    return message;
}

void vigenere_table(){
    string alphabet = "A B C D E F G H I K L M N O P Q R S T V X Y Z";
    string key_alphabet = "abcdefghiklmnoqrstvxyz";
    
    for (char letter : key_alphabet){
        string s = "";
        s = s + letter;
        cout << vigenere_encrypt(alphabet, s) << endl;
    }
}

void help()
{
    cout << "1 - task 1" << endl
         << "2 - task 2" << endl
         << "3 - task 3" << endl
         << "0 - exit" << endl;
}

void help_task1()
{
    cout << "1 - snake print" << endl
         << "2 - delete row" << endl
         << "3 - element max in row and min in column" << endl
         << "0 - to main menu" << endl;
}

void help_task2()
{
    cout << "1 - encrypt text" << endl
         << "2 - decrypt text" << endl
         << "0 - to main menu" << endl;
}

void help_task3()
{
    cout << "1 - simple Gauss" << endl
         << "2 - Gauss with main element choise" << endl
         << "3 - simple iteration method" << endl
         << "0 - to main menu" << endl;
}

int main()
{
    cout << "Lab #6:\n";
    help();
    cout << "Enter what do you want to see first : ";

    int control = 0;
    cin >> control;

    while (control != 0)
    {
        switch (control) //вся навигация просходит в свитч кейсе
        {
        case 1:
        {
            cout << "Generated matrix\n";

            int M = 3;
            int N = 3;
            srand(time(0));

            vector<vector<int>> matrix(M);
            for (int i = 0; i < M; i++)
            {
                vector<int> row(N);
                for (int j = 0; j < N; j++)
                {
                    row.at(j) = rand() % 100;
                }
                matrix.at(i) = row;
            }

            cout << matrix << endl;

            cout << "Enter what do you want to do with it: \n";
            help_task1();

            int control_t1 = 0;
            cin >> control_t1;

            while (control_t1 != 0)
            {
                switch (control_t1)
                {
                case 1:
                    snake_print(matrix);
                    break;
                case 2:
                {
                    cout << "What row do you want to delete : ";
                    int row = 0;
                    cin >> row;
                    delete_row(matrix, row);
                    cout << row << " row has been deleted" << endl
                         << "matrix : " << endl
                         << matrix;
                }
                case 3:
                    cout << "List of elements that max in row and min in column: " << maxrow_minclumn(matrix) << endl;
                default:
                    help_task1();
                    break;
                }
                cout << "Next in task 1: ";
                cin >> control_t1;
            }
            break;
        }
        case 2:
        {
            cout << "Vigenere cypher" << endl;
            help_task2();

            int control_t2 = 0;
            cin >> control_t2;

            while (control_t2 != 0)
            {
                switch (control_t2)
                {
                case 1:
                {
                    char message[256];
                    string keyWord;
                    cout << "Enter message to encrypt : ";
                    _flushall();
                    cin.getline(message, 256, ';');
                    _flushall();

                    cout << "Enter key word : ";
                    cin >> keyWord;
                    transform(keyWord.begin(), keyWord.end(), keyWord.begin(), [](char c) { return tolower(c); });

                    cout << "Message : " << message << endl
                         << "Key : " << keyWord << endl
                         << "Encrypted message : " << vigenere_encrypt(message, keyWord) << endl;
                    break;
                }
                case 2:
                {
                    char message[256];
                    string keyWord;
                    cout << "Enter message to decrypt : ";
                    _flushall();
                    cin.getline(message, 256, ';');
                    _flushall();

                    cout << "Enter key word : ";
                    cin >> keyWord;
                    transform(keyWord.begin(), keyWord.end(), keyWord.begin(), [](char c) { return tolower(c); });

                    cout << "Message : " << message << endl
                         << "Key : " << keyWord << endl
                         << "Decrypted message : " << vigenere_decrypt(message, keyWord) << endl;
                    break;
                }
                case 3:
                    vigenere_table();
                    cout << endl;
                    break;
                default:
                    help_task2();
                    break;
                }
                help_task2();
                cin >> control_t2;
            }
            break;
        }
        case 3:
        {
            double M = -0.88;
            double N = 0.1;
            double P = 0.91;

            /*
            vector<double> X(j);

            vector<double> B = {-1.24, -P, 2.56, M};

            vector<vector<double>> matrix_A = {{M, -0.04, 0.21, -18},
                                               {0.25, -1.23, N, -0.09},
                                               {-0.21, N, 0.8, -0.13},
                                               {0.15, -1.31, 0.06, P}};
        */
            vector<double> B = {2, -2, 2};
            vector<double> X(B.size());
            vector<vector<double>> matrix_A = {{2, 1, 1},
                                               {1, -1, 0},
                                               {3, -1, 2}};

            cout << matrix_A << endl;

            cout << "Equation solver " << endl;
            help_task3();

            int control_t3 = 0;
            cin >> control_t3;

            while (control_t3 != 0)
            {
                switch (control_t3)
                {
                case 1:
                    cout << "Gauss : \n";
                    gaus_solve(matrix_A, X, B);
                    break;
                case 2:
                    cout << "Gauss with choise : \n";
                    choise_gaus_solve(matrix_A, X, B);
                    break;
                case 3:
                    cout << "Simple iteration : \n";
                    double eps;
                    cout << "Enter accuracy : " << endl;
                    cin >> eps;
                    iteration(matrix_A, X, B, eps);
                    break;
                }
                cout << "Next in task 3 : ";
                cin >> control_t3;
            }
        }
        }
        cout << "Next task : ";
        cin >> control;
    }
}
