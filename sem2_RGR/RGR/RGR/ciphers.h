#pragma once
#include <string>

std::string vigenere_encrypt(std::string message, std::string key);
std::string vigenere_decrypt(std::string message, std::string key);

std::string playfair_encrypt(std::string message, std::string key);
std::string playfair_decrypt(std::string message, std::string key);

std::string gronsfeld_encrypt(std::string stringInp, std::string key);
std::string gronsfeld_decrypt(std::string stringInp, std::string key);

std::string cesar_encrypt(std::string message, std::string key_s);
std::string cesar_decrypt(std::string stringInp, std::string key_s);