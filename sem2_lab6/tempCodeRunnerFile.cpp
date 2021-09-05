
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
            cout << B << endl;
        }
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
    }
    cout << "X = " << X << endl;
}
