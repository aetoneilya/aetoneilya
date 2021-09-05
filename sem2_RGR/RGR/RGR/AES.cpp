#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <wincrypt.h>
#include <bcrypt.h>
#include <string.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sstream>
#pragma warning(disable: 4018)


BYTE aBuf[512]; //буфер для данных (размер произвольный, кратный 16)
TCHAR szBuff[100];
DWORD dwBuflen; //длина буфера
TCHAR szPass[100]; //строка для пароля

typedef unsigned long type;

BCRYPT_ALG_HANDLE hAlg;
BCRYPT_HASH_HANDLE hHashB;
BCRYPT_KEY_HANDLE hKey;

CHAR pass[65];

using namespace std;

int aes_decode(string& out, vector<char> dataIn, char pass[]) {
	vector<char> data(dataIn.size() + 10240);

	for (int i = 0; i < dataIn.size(); i++)
		data[i] = dataIn[i];

	int razmer = 16;
	TCHAR* szpass = new TCHAR[razmer];

	type buffSize = data.size();
	BYTE* buffText = new BYTE[512];
	DWORD dwBuflen = 16;

	HCRYPTPROV hProv; //дескриптор криптопровайдера
	HCRYPTKEY hKey; //дескриптор ключа, созданного из хэш-кода
	HCRYPTHASH hHash; //дескриптор хэш-объекта
	HCRYPTPROV hCryptProv;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		std::cout << "Error AES\n";
		return 1;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
	{
		std::cout << "Error AES\n";
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptHashData(hHash, (BYTE*)pass, strlen(pass), 0))
	{
		std::cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptDeriveKey(hProv, CALG_AES_192, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		std::cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	// decoding 
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		std::cout << "Error AES\n";
		return 1;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
	{
		std::cout << "Error AES\n";
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptHashData(hHash, (BYTE*)pass, strlen(pass), 0))
	{
		std::cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptDeriveKey(hProv, CALG_AES_192, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		std::cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}


	DWORD datalen = dataIn.size();
	if (!CryptDecrypt(hKey, NULL, true, 0, reinterpret_cast<BYTE*>(data.data()), &datalen))
	{
		std::cout << "Wrong password\n";
		return 1;
	}
	else
	{
		stringstream ss;
		ss.write(data.data(), datalen);
		out = ss.str();
	}
	CryptDestroyHash(hHash);
	CryptDestroyKey(hKey);
	CryptReleaseContext(hProv, 0);

	return 0;
}

int aes_encode(vector<char> dataIn, char pass[], string& out) {
	vector<char> data(dataIn.size() + 10240);

	for (int i = 0; i < dataIn.size(); i++)
		data[i] = dataIn[i];

	int razmer = 16;
	TCHAR* szpass = new TCHAR[razmer];

	type buffSize = data.size();
	BYTE* buffText = new BYTE[512];
	DWORD dwBuflen = 16;

	HCRYPTPROV hProv; //дескриптор криптопровайдера
	HCRYPTKEY hKey; //дескриптор ключа, созданного из хэш-кода
	HCRYPTHASH hHash; //дескриптор хэш-объекта
	HCRYPTPROV hCryptProv;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		cout << "Error AES\n";
		return 1;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
	{
		cout << "Error AES\n";
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptHashData(hHash, (BYTE*)pass, strlen(pass), 0))
	{
		cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	if (!CryptDeriveKey(hProv, CALG_AES_192, hHash, CRYPT_EXPORTABLE, &hKey))
	{
		cout << "Error AES\n";
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return 1;
	}

	//encoding

	DWORD datalen = dataIn.size();
	if (!CryptEncrypt(hKey, NULL, true, 0, reinterpret_cast<BYTE*>(data.data()), &datalen, data.size()))
	{
		cout << "Error AES\n";
	}
	else
	{
		stringstream ss;
		ss.write(data.data(), datalen);
		out = ss.str();
	}

	CryptDestroyHash(hHash);
	CryptDestroyKey(hKey);
	CryptReleaseContext(hProv, 0);
	return 0;
}