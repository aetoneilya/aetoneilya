#pragma once
#include <vector>
#include <string>


int aes_decode(std::string& out, std::vector<char> dataIn, char pass[]);
int aes_encode(std::vector<char> dataIn, char pass[], std::string& out);