#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include "AES.h"
#include "ciphers.h"

using namespace std;

enum class commands {
    VGN, PLF, GRN, CES, AES, DECODE, FROM_FILE, HELP, CLS, NONE, EXIT
};

istream& operator>>(istream& is, commands& command)
{
    string input;
    is >> input;
    if (input == "VGN")
        command = commands::VGN;
    else if (input == "PLF")
        command = commands::PLF;
    else if (input == "GRN")
        command = commands::GRN;
    else if (input == "CES")
        command = commands::CES;
    else if (input == "AES")
        command = commands::AES;
    else if (input == "DECODE")
        command = commands::DECODE;
    else if (input == "FROM_FILE")
        command = commands::FROM_FILE;
    else if (input == "EXIT")
        command = commands::EXIT;
    else if (input == "HELP")
        command = commands::HELP;
    else if (input == "CLS")
        command = commands::CLS;
    else 
        command = commands::NONE;
    return is;
}

int AES(commands source)
{
    char pass[128];
    cin >> pass;

    string message;
    if (source == commands::NONE) {
        _flushall();
        char input[256];
        cin.getline(input, 256, ';');
        _flushall();
        message = input;
        if (message[0] == ' ') {
            message.erase(0, 1);
        }
    }
    else if (source == commands::FROM_FILE) {
        char filein[256];
        cin >> filein;
        ifstream ifs(filein);
        if (!ifs) {
            cout << "Error: file " << filein << " can't be open";
            return 1;
        }
        ifs.seekg(0, ifs.end);
        int len = ifs.tellg();
        ifs.seekg(0);
        vector<char> data(len);
        ifs.read(data.data(), len);
        ifs.close();
        string input(data.begin(), data.end());
        message = input;
    }

    vector<char> data(message.begin(), message.end());
    string encrypted;
    aes_encode(data, pass, encrypted);

    cout << "Encrypted string : " << encrypted << endl
        << "S - save it to file\nN - do nothing\n";
    string cmd;
    cin >> cmd;

    if (cmd == "S") {
        char fileout[256];
        cout << "Enter path to file to store encoded text: ";
        cin >> fileout;
        ofstream fout;
        fout.open(fileout);
        fout << encrypted;
        fout.close();
    }

    return 0;

}
int DECODE_AES(commands source)
{
    char pass[65];
    cin >> pass;

    string message_encoded;
    if (source == commands::NONE) {
        _flushall();
        char input[256];
        cin.getline(input, 256, ';');
        _flushall();
        message_encoded = input;
        if (message_encoded[0] == ' ') {
            message_encoded.erase(0, 1);
        }
    }
    else if (source == commands::FROM_FILE) {
        char filein[256];
        cin >> filein;
        ifstream ifs(filein);
        if (!ifs) {
            cout << "Error: file " << filein << " can't be open";
            return 1;
        }
        ifs.seekg(0, ifs.end);
        int len = ifs.tellg();
        ifs.seekg(0);
        vector<char> data(len);
        ifs.read(data.data(), len);
        ifs.close();
        string input(data.begin(), data.end());
        message_encoded = input;
    }

    string out;
    vector<char> data(message_encoded.begin(), message_encoded.end());
    if (aes_decode(out, data, pass)) return 1;

    stringstream ss(out);

    commands cmd3;
    ss >> cmd3;
    string keyWord;
    ss >> keyWord;

    string word, message;
    while (ss >> word) {
        message += word;
        message += ' ';
    }

    string decrypted;
    string codeName;
    switch (cmd3)
    {
    case commands::VGN:
        decrypted = vigenere_decrypt(message, keyWord);
        codeName = "Vigenere";
        break;
    case commands::PLF:
        decrypted = playfair_decrypt(message, keyWord);
        codeName = "Playfair";
        break;
    case commands::GRN:
        decrypted = gronsfeld_decrypt(message, keyWord);
        codeName = "Gronsfield";
        break;
    case commands::CES:
        decrypted = cesar_decrypt(message, keyWord);
        codeName = "Cesar";
        break;

    case commands::NONE:
        decrypted = ss.str();
        break;
    default:
        cout << "Incorrect file";
        return 1;
        break;
    }

    if (cmd3 != commands::NONE) {
        cout << "Code: " << codeName << endl
            << "Password: " << keyWord << endl;
    }

    cout << "Decoded string: " << decrypted
        << "\nS - save it to file \nN - do nothing\n";

    string cmd4;
    cin >> cmd4;
    if (cmd4 == "S") {
        char fileout[256];
        cout << "Enter path to file to store encoded text:";
        cin >> fileout;
        ofstream fout;
        fout.open(fileout);
        fout << decrypted;
        fout.close();
        return 0;
    }
}

int encode(commands source,commands cipherName) {
    if (cipherName == commands::AES) {
        AES(source);
        return 0;
    }

    string keyWord;
    cin >> keyWord;
    transform(keyWord.begin(), keyWord.end(), keyWord.begin(), [](char c) { return tolower(c); });

    string message;
    if (source == commands::NONE) {
        _flushall();
        char input[256];
        cin.getline(input, 256, ';');
        _flushall();
        message = input;
        if (message[0] == ' ') {
            message.erase(0, 1);
        }
    }
    else if (source == commands::FROM_FILE) {
        char filein[256];
        cin >> filein;
        ifstream ifs(filein);
        if (!ifs) {
            cout << "Error: file " << filein << " can't be open";
            return 1;
        }
        ifs.seekg(0, ifs.end);
        int len = ifs.tellg();
        ifs.seekg(0);
        vector<char> data(len);
        ifs.read(data.data(), len);
        ifs.close();
        string input(data.begin(), data.end());
        message = input;
    }

    string encrypted;
    string cipherCode;
    switch (cipherName)
    {
    case commands::VGN:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 65 || (keyWord[i] > 90 && keyWord[i] < 97) || keyWord[i]>122) {
                cout << endl << "Error: the key must contain only Latin letters" << endl << endl;
                return 0;
            }
        }
        encrypted = vigenere_encrypt(message, keyWord);
        cipherCode = "VGN";
        break;
    case commands::PLF:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 65 || (keyWord[i] > 90 && keyWord[i] < 97) || keyWord[i]>122) {
                cout << endl << "Error: The key must contain only Latin letters" << endl << endl;
                return 0;
            }
        }
        encrypted = playfair_encrypt(message, keyWord);
        cipherCode = "PLF";
        break;
    case commands::GRN:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 48 || keyWord[i]>57) {
                cout << endl << "Error: the key must contain only numbers" << endl << endl;
                return 0;
            }
        }
        encrypted = gronsfeld_encrypt(message, keyWord);
        cipherCode = "GRN";
        break;
    case commands::CES:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 48 || keyWord[i]>57) {
                cout << endl << "Error: the key must contain only numbers" << endl << endl;
                return 1;
            }
        }
        encrypted = cesar_encrypt(message, keyWord);
        cipherCode = "CES";
        break;
    default:
        cout << "Error: incorrect cipher name" << endl;
        return 1;
        break;
    }

    cout << "Encrypted string : " << encrypted << endl
        << "S - save it to file\nSA - save it to file using AES\nN - do nothing\n";
    string cmd;
    cin >> cmd;

    if (cmd == "S") {
        char fileout[256];
        cout << "Enter path to file to store encoded text: ";
        cin >> fileout;
        ofstream fout;
        fout.open(fileout);
        fout << encrypted;
        fout.close();
    }
    else if (cmd == "SA") {
        string format = cipherCode + ' ' + keyWord + " " + encrypted;
        vector<char> data(format.begin(), format.end());

        char pass[128];
        cout << "Enter password for AES: ";
        cin >> pass;

        aes_encode(data, pass, encrypted);

        char fileout[256];
        cout << "Enter path to file to store encoded text: ";
        cin >> fileout;
        ofstream fout;
        fout.open(fileout);
        fout << encrypted;
        fout.close();
    }
    return 0;
}

int decode(commands source, commands cipherName) {
    if (cipherName == commands::AES) {
        DECODE_AES(source);
        return 0;
    }

    string keyWord;
    cin >> keyWord;
    transform(keyWord.begin(), keyWord.end(), keyWord.begin(), [](char c) { return tolower(c); });

    string message;
    if (source == commands::NONE) {
        _flushall();
        char input[256];
        cin.getline(input, 256, ';');
        _flushall();
        message = input;
        if (message[0] == ' ') {
            message.erase(0, 1);
        }
    }
    else if (source == commands::FROM_FILE) {
        char filein[256];
        cin >> filein;
        ifstream ifs(filein);
        if (!ifs) {
            cout << "Error: file " << filein << " can't be open";
            return 1;
        }
        ifs.seekg(0, ifs.end);
        int len = ifs.tellg();
        ifs.seekg(0);
        vector<char> data(len);
        ifs.read(data.data(), len);
        ifs.close();
        string input(data.begin(), data.end());
        message = input;
    }
    
    string decrypted;

    switch (cipherName)
    {
    case commands::VGN:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 65 || (keyWord[i] > 90 && keyWord[i] < 97) || keyWord[i]>122) {
                cout << endl << "Error: the key must contain only Latin letters" << endl << endl;
                return 0;
            }
        }
        decrypted = vigenere_decrypt(message, keyWord);
        break;
    case commands::PLF:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 65 || (keyWord[i] > 90 && keyWord[i] < 97) || keyWord[i]>122) {
                cout << endl << "Error: The key must contain only Latin letters" << endl << endl;
                return 0;
            }
        }
        decrypted = playfair_decrypt(message, keyWord);
        break;
    case commands::GRN:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 48 || keyWord[i]>57) {
                cout << endl << "Error: the key must contain only numbers" << endl << endl;
                return 0;
            }
        }
        decrypted = gronsfeld_decrypt(message, keyWord);
        break;
    case commands::CES:
        for (int i = 0; i < keyWord.length(); i++) {
            if (keyWord[i] < 48 || keyWord[i]>57) {
                cout << endl << "Error: the key must contain only numbers" << endl << endl;
                return 1;
            }
        }
        decrypted = cesar_decrypt(message, keyWord);
        break;
    case commands::AES:
        break;
    default:
        cout << "Error: incorrect cipher name" << endl;
        return 1;
        break;
    }

    cout << "Decoded string: " << decrypted
        << "\nS - save it to file \nN - do nothing\n";
    string cmd3;
    cin >> cmd3;
    if (cmd3 == "S") {
        char fileout[256];
        cout << "Enter path to file to store encoded text:";
        cin >> fileout;
        ofstream fout;
        fout.open(fileout);
        fout << decrypted;
        fout.close();
    }
    return 0;
}



void help() {
    cout << endl << "There are 5 ciphers you can use in this program:" << endl <<endl
        << "Vigenere cipher - VGN\nPlayfair cipher - PLF\nGronsfeld Cipher - GRN\nCesar cipher - CES\nAdvanced Encryption Standard - AES" << endl << endl
        << "To encode text use command VGN/PLF/GRN/CES/AES then add password (word for VGN and PLF and number for GRN)" << endl
        << "For example -  VGN keyword your secret message; ';' on the end is nessecery to mark the end of the message" << endl
        << "If you want to read text from file add 'FROM_FILE' to beging - for example FROM_FILE VGN keyword addres.txt" << endl
        << "To decode use DECODE (FROM_FILE) VGN/PLF/GRN/CES keyword (fileaddress.txt or encrypted text) to decode AES use DECODE AES password text.txt" << endl
        << "Use EXIT to exit and CLS to erase everything from screen" << endl;
}

int main() {
    cout << "Welcome to the cipher machine" << endl << "If you are new use HELP\n";
    commands cmd;
    while (true){
        cin >> cmd;
        switch (cmd)
        {
        case commands::FROM_FILE: 
        {
            commands cmd2;
            cin >> cmd2;
            encode(commands::FROM_FILE, cmd2);
            break; 
        }
        case commands::DECODE: 
        {
            commands cmd2;
            cin >> cmd2;
            if (cmd2 == commands::FROM_FILE) {
                commands cmd3;
                cin >> cmd3;
                decode(commands::FROM_FILE, cmd3);
            }
            else decode(commands::NONE, cmd2);
            break;
        }
        case commands::HELP:
            help();
            break;
        case commands::CLS:
            system("cls");
            break;
        case commands::EXIT:
            return 0;
            break;
        case commands::NONE:
            cout << "Error: incorrect input" << endl;
            break;
        default:
            encode(commands::NONE, cmd);
            break;
        }
    }
}