import copy
import random
from itertools import cycle


def snake_print(matrix):
    M = len(matrix)
    N = len(matrix[0])

    for i in range(M):
        if i % 2 == 0:
            for j in range(N):
                print(matrix[i][j], end=" ")
        else:
            for j in range(N-1, 0, -1):
                print(matrix[i][j], end=" ")
        print()


def maxrow_mincolumn(matrix):
    M = len(matrix)
    N = len(matrix[0])
    rowsMax = []
    for i in range(M):
        maxValue = matrix[i][0]
        maxInd = 0
        for j in range(N):
            if matrix[i][j] > maxValue:
                maxValue = matrix[i][j]
                maxInd = j
        rowsMax.append(maxInd)

    columnsMin = []
    for j in range(N):
        minValue = matrix[0][j]
        minInd = 0
        for i in range(M):
            if matrix[i][j] < minValue:
                minValue = matrix[i][j]
                minInd = i
        columnsMin.append(minInd)

    results = []
    for i in range(M):
        if columnsMin[rowsMax[i]] == i:
            results.append(matrix[i][rowsMax[i]])
    return results


def gaus_solve(matrix, B):
    X = B[:]
    size = len(matrix)
    prev_step_matrix = matrix[:]

    for k in range(size):
        for i in range(k+1, size):
            B[i] = B[i] - prev_step_matrix[i][k] * \
                B[k] / prev_step_matrix[k][k]
            for j in range(k+1, size):
                matrix[i][j] = prev_step_matrix[i][j] - prev_step_matrix[i][k] * \
                    prev_step_matrix[k][j] / prev_step_matrix[k][k]
            print(B)
        prev_step_matrix = matrix[:]

    for i in range(1, size):
        for j in range(0, i):
            matrix[i][j] = 0

    print("matrix left : ")
    print_matrix(matrix)
    print("matrix right : ")
    print(B)

    for k in range(size - 1, -1, -1):
        sum = 0
        for j in range(k + 1, size):
            sum += matrix[k][j] * X[j]
        X[k] = (B[k] - sum) / matrix[k][k]

    print("X = ", end=" ")
    print(X)
    return(X)


def choise_gaus_solve(matrix, B):
    X = B[:]
    size = len(matrix)
    prev_step_matrix = copy.deepcopy(matrix)

    for k in range(size):
        max_ind = k
        for i in range(k, size):
            if (matrix[i][k] > matrix[max_ind][k]):
                max_ind = i
        temp = matrix[k]
        matrix[k] = matrix[max_ind]
        matrix[max_ind] = temp

        for i in range(k+1, size):
            B[i] = B[i] - prev_step_matrix[i][k] * \
                B[k] / prev_step_matrix[k][k]
            for j in range(k+1, size):
                matrix[i][j] = prev_step_matrix[i][j] - prev_step_matrix[i][k] * \
                    prev_step_matrix[k][j] / prev_step_matrix[k][k]
            print(B)
        prev_step_matrix = matrix[:]

    for i in range(1, size):
        for j in range(0, i):
            matrix[i][j] = 0

    print("matrix left : ")
    print_matrix(matrix)
    print("matrix right : ")
    print(B)

    for k in range(size - 1, -1, -1):
        sum = 0
        for j in range(k + 1, size):
            sum += matrix[k][j] * X[j]
        X[k] = (B[k] - sum) / matrix[k][k]

    print("X = ", end=" ")
    print(X)
    return(X)


def iteration(matrix_A, B, eps):

    size = len(matrix_A)
    matrix_f = copy.deepcopy(B)
    matrix_C = copy.deepcopy(matrix_A)

    for i in range(0, size):
        matrix_C[i][i] = 0

    for i in range(size):
        for j in range(size):
            matrix_C[i][j] = -1. * matrix_C[i][j] / matrix_A[i][i]

    for i in range(size):
        matrix_f[i] /= matrix_A[i][i]

    prev_X = matrix_f[:]
    X = copy.deepcopy(B)
    while(abs(max(X) - max(prev_X) > eps)):
        prev_X = copy.deepcopy(X)
        for i in range(size):
            sum = 0
            for j in range(size):
                sum += matrix_C[i][j] * prev_X[j]
            X[i] = matrix_f[i] + sum
    return X


def form_dict():
    return dict([(i, chr(i)) for i in range(128)])


def comparator(value, key):
    return dict([(idx, [ch[0], ch[1]])
                for idx, ch in enumerate(zip(value, cycle(key)))])


def encode_val(word):
    d = form_dict()
    return [k for c in word for k, v in d.items() if v == c]


def full_encode(value, key):
    d = comparator(value, key)
    l = len(form_dict())
    return [(v[0] + v[1]) % l for v in d.values()]


def decode_val(list_in):
    l = len(list_in)
    d = form_dict()
    return [d[i] for i in list_in if i in d]


def full_decode(value, key):
    d = comparator(value, key)
    l = len(form_dict())
    return [(v[0] - v[1]) % l for v in d.values()]


def vigenere_encrypt(text, key):
    return decode_val(full_encode(encode_val(text), encode_val(key)))


def help():
    print("1 - task 1")
    print("2 - task 2")
    print("3 - task 3")
    print("0 - exit")


def help_task1():
    print("1 - snake print")
    print("2 - delete row")
    print("3 - element max in row and min in column")
    print("0 - to main menu")


def help_task2():
    print("1 - encrypt text")
    print("2 - decrypt text")
    print("0 - to main menu")


def help_task3():
    print("1 - simple Gauss")
    print("2 - Gauss with main element choise")
    print("3 - simple iteration method")
    print("0 - to main menu")


def print_matrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(matrix[i][j], end='\t')
        print()

# matrix = [[2, 1, 1], [1, -1, 0], [3, -1, 2]]
# B = [2, -2, 2]
# print("X = ", iteration(matrix,B,0.001))


print("Lab #6:")
help()
control = int(input("Enter what do you want to see first : "))

while (control != 0):
    if control == 1:
        print("Generated matrix")

        M = N = 3
        matrix = []

        for i in range(M):
            row = []
            for j in range(N):
                row.append(random.randint(0, 100))
            matrix.append(row)

        print_matrix(matrix)
        print("Enter what do you want to do with it: ")
        help_task1()
        control_t1 = int(input())

        while control_t1 != 0:
            if control_t1 == 1:
                snake_print(matrix)
            elif control_t1 == 2:
                row = int(input())
                matrix.pop(row)
            elif control_t1 == 3:
                print("List of elements that max in row and min in column: " +
                      str(maxrow_mincolumn(matrix)))

            control_t1 = int(input("What is next in task 1 : "))

    elif control == 2:
        print("Vigenere cypher")
        help_task2()

        control_t2 = int(input())

        while control_t2 != 0:
            if control_t2 == 1:
                word = input("Enter word to encrypt : ")
                key = input("Enter key : ")

                print('word: ' + word)
                print('key: ' + key)

                key_encoded = encode_val(key)
                value_encoded = encode_val(word)

                shifre = full_encode(value_encoded, key_encoded)
                print('encrypted word =', ''.join(decode_val(shifre)))

            elif control_t2 == 2:
                word = input("Enter word to encrypt : ")
                key = input("Enter key : ")

                print('word: ' + word)
                print('key: ' + key)

                key_encoded = encode_val(key)
                value_encoded = encode_val(word)

                decoded = full_decode(value_encoded, key_encoded)
                decode_word_list = decode_val(decoded)
                print('decrypted word=', ''.join(decode_word_list))

            help_task2()
            control_t2 = int(input())

    elif control == 3:
        B = [2, -2, 2]
        matrix_A = [[2, 1, 1], [1, -1, 0], [3, -1, 2]]
        print("Equation solver ")
        help_task3()

        control_t3 = int(input())

        while control_t3 != 0:
            if control_t3 == 1:
                print("Gauss")
                gaus_solve(matrix_A, B)
            elif control_t3 == 2:
                print("Gauss with choise ")
                choise_gaus_solve(matrix_A, B)
            elif control_t3 == 3:
                print("Simple iteration")
                eps = float(input("Enter accuracy : "))
                iteration(matrix_A, B, eps)
            control_t3 = int(input("Next in task 3 : "))

    help()
    control = int(input("What is next : "))
