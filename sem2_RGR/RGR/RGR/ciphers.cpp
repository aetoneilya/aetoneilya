#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

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

string playfair_encrypt(string message, string key) {

    //add block to lower case all
    transform(message.begin(), message.end(), message.begin(),
        [](unsigned char c) { return tolower(c); });

    string alphabet = { "abcdefghiklmnopqrstuvwxyz" };
    int str_len = key.size();
    int alphabet_len = key.size();
    // delete all q
    for (int i = 0; i < key.size(); i++) {
        if (key[i] == 'j')
            key.erase(i, 1);
    }
    //get rid of repetitions
    for (int i = 0; i < key.size(); i++) {

        for (int j = i + 1; j < key.size(); j++) {
            if (key[i] == key[j])
                key.erase(j, 1);
        }

        for (int j = 0; j < alphabet.size(); j++) {
            if (key[i] == alphabet[j])
                alphabet.erase(j, 1);
        }
    }

    //block to replace J with I and add X to the end in odd case and after repeating letters
    for (int i = 0; i < message.size(); i++) {
        if (message[i] == 'j')
            message.replace(i, 1, 1, 'i');
    }
    for (int i = 0; i < message.size(); i++) {
        if (message[i] < 65 || (message[i] > 90 && message[i] < 97) || message[i]>122)
            message.erase(i, 1);
    }

    for (int i = 1; i < message.size(); i++) {
        if ((message[i - 1] == message[i]) /*&& message[i] != 'x'*/) {
            message.insert(i, 1, 'x');
            message.insert(i + 2, 1, 'x');
            i += 2;
        }
    }
    if (message.size() % 2 == 1)
        message.append(1, 'x');

    //create and fill matrix
    char matrix[5][5];
    for (int i = 0; i < 25; i++) {
        if (i < key.size())
            matrix[i / 5][i % 5] = key[i];
        else matrix[i / 5][i % 5] = alphabet[i - key.size()];
    }

    //encription
    string result = "";
    int x_ind;
    for (int i = 0; i < 25; i++) {
        if (matrix[i / 5][i % 5] == 'x')
            x_ind = i;
    }
    for (int i = 0; i < message.size(); i += 2) {

        int first_ind, second_ind;
        for (int j = 0; j < 25; j++) {
            if (message[i] == matrix[j / 5][j % 5])
                first_ind = j;
            if (message[i + 1] == matrix[j / 5][j % 5])
                second_ind = j;
        }

        //both x
        if (first_ind == second_ind && first_ind == x_ind) {
            result += matrix[x_ind / 5][(x_ind + 1) % 5];
            result += matrix[x_ind / 5][(x_ind + 1) % 5];
        }
        //similar letters
        else if (first_ind == second_ind) {
            result += matrix[first_ind / 5][x_ind % 5];
            result += matrix[x_ind / 5][first_ind % 5];
            result += matrix[first_ind / 5][x_ind % 5];
            result += matrix[x_ind / 5][first_ind % 5];
        }
        // same row
        else if (first_ind / 5 == second_ind / 5) {
            result += matrix[first_ind / 5][(first_ind + 1) % 5];
            result += matrix[first_ind / 5][(second_ind + 1) % 5];
        }
        //same column
        else if (first_ind % 5 == second_ind % 5) {
            result += matrix[((first_ind + 5) / 5) % 5][first_ind % 5];
            result += matrix[((second_ind + 5) / 5) % 5][first_ind % 5];
        }
        //rectangular case
        else {
            result += matrix[first_ind / 5][second_ind % 5];
            result += matrix[second_ind / 5][first_ind % 5];
        }
    }

    return result;
}

string playfair_decrypt(string message, string key) {

    //add block to lower case all
    transform(message.begin(), message.end(), message.begin(),
        [](unsigned char c) { return std::tolower(c); });

    string alphabet = { "abcdefghiklmnopqrstuvwxyz" };
    int str_len = key.size();
    int alphabet_len = key.size();


    //get rid of repetitions
    for (int i = 0; i < key.size(); i++) {

        for (int j = i + 1; j < key.size(); j++) {
            if (key[i] == key[j])
                key.erase(j, 1);
        }

        for (int j = 0; j < alphabet.size(); j++) {
            if (key[i] == alphabet[j])
                alphabet.erase(j, 1);
        }
    }

    //create and fill matrix
    char matrix[5][5];
    for (int i = 0; i < 25; i++) {
        if (i < key.size())
            matrix[i / 5][i % 5] = key[i];
        else matrix[i / 5][i % 5] = alphabet[i - key.size()];
    }

    //decription
    string result = "";
    int x_ind;
    for (int i = 0; i < 25; i++) {
        if (matrix[i / 5][i % 5] == 'x')
            x_ind = i;
    }
    for (int i = 0; i < message.size(); i += 2) {

        int first_ind, second_ind;
        for (int j = 0; j < 25; j++) {
            if (message[i] == matrix[j / 5][j % 5])
                first_ind = j;
            if (message[i + 1] == matrix[j / 5][j % 5])
                second_ind = j;
        }

        //both x
        if (first_ind == second_ind && first_ind == x_ind) {
            result += matrix[x_ind / 5][(x_ind - 1) % 5];
            result += matrix[x_ind / 5][(x_ind - 1) % 5];
        }
        //similar letters
        else if (first_ind == second_ind) {
            result += matrix[first_ind / 5][x_ind % 5];
            result += matrix[x_ind / 5][first_ind % 5];
            result += matrix[first_ind / 5][x_ind % 5];
            result += matrix[x_ind / 5][first_ind % 5];
        }
        // same row
        else if (first_ind / 5 == second_ind / 5) {
            result += matrix[first_ind / 5][(first_ind - 1) % 5];
            result += matrix[first_ind / 5][(second_ind - 1) % 5];
        }
        //same column
        else if (first_ind % 5 == second_ind % 5) {
            result += matrix[((first_ind - 5) / 5) % 5][first_ind % 5];
            result += matrix[((second_ind - 5) / 5) % 5][first_ind % 5];
        }
        //rectangular case
        else {
            result += matrix[first_ind / 5][second_ind % 5];
            result += matrix[second_ind / 5][first_ind % 5];
        }
    }

    return result;
}

string gronsfeld_encrypt(string message, string key_s) {//Функция шифровки текста по ключу

    reverse(key_s.begin(), key_s.end());
    int keyLen = key_s.length();
    int key = stoi(key_s);

    for (int i = 0, t1; i < message.length(); i++) {
        t1 = pow(10, i % keyLen);
        message[i] += ((key / t1) % 10);
    }

    return message;
}

string gronsfeld_decrypt(string message, string key_s) {

    reverse(key_s.begin(), key_s.end());
    int keyLen = key_s.length();
    int key = stoi(key_s);

    for (int i = 0, t1, t2; i < message.length(); i++) {
        t1 = pow(10, i % keyLen);
        message[i] -= ((key / t1) % 10);
    }

    return message;
}

string cesar_encrypt(string message, string key_s)
{ //Функция шифровки текста по ключу

    int key = stoi(key_s);
    key = key % 26;

    for (int i = 0; i < message.length(); i++)
    {
        if (message[i] > 64 && message[i] < 91)
        {
            message[i] += key;
            if (message[i] > 90) message[i] -= 26;
        }
        else if (message[i] > 96 && message[i] < 123)
        {
            message[i] -= 32;
            message[i] += key;
            if (message[i] > 90) message[i] -= 26;
            message[i] += 32;
        }
    }

    return message;
}

string cesar_decrypt(string message, string key_s)
{
    int key = stoi(key_s);
    key = key % 26;

    for (int i = 0; i < message.length(); i++)
    {
        if (message[i] > 64 && message[i] < 91)
        {
            message[i] -= key;
            if (message[i] < 65) message[i] += 26;
        }
        else if (message[i] > 96 && message[i] < 123)
        {
            message[i] -= key;
            if (message[i] < 97) message[i] += 26;
        }
    }
    return message;
}