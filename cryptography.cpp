// ---------------------------------------------------------------------------
#pragma hdrstop

#include <iostream>
#include "Cryptography.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

// ---------------------------------------------------------------------------
Cryptography::Cryptography( )
{
	inputHandle_ = 0;
	outputHandle_ = 0;
	keyHandle_ = 0;
    hSessionKey_ = NULL;
	hCryptProvider_ = NULL;
}
// ---------------------------------------------------------------------------
bool Cryptography::open(
	std::wstring inputPath,
	std::wstring outputPath )
{
	inputHandle_ = CreateFileW( inputPath.c_str( ), GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( inputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	outputHandle_ = CreateFileW( outputPath.c_str( ), GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( outputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::close( )
{
	CloseHandle( inputHandle_ );
	CloseHandle( outputHandle_ );
	CloseHandle( keyHandle_ );
	return true;
}
// ---------------------------------------------------------------------------

bool Cryptography::readBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	BYTE *    readBuffer )
{
	if ( inputHandle_ == 0 || inputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	ULONGLONG StartOffset = blockSize * numberBlock;
	DWORD BytesToRead = blockSize;
	DWORD BytesRead;
	LARGE_INTEGER FileOffset;
	FileOffset.QuadPart = StartOffset;
	ULONGLONG CurrentPosition =
		SetFilePointer( inputHandle_, FileOffset.LowPart, &FileOffset.HighPart,
		FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}

	bool ReadResult = ReadFile( inputHandle_, readBuffer, BytesToRead,
		&BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		return false;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::writeBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	BYTE *    writeBuffer )
{
	if ( outputHandle_ == 0 || outputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	ULONGLONG StartOffset = blockSize * numberBlock;
	DWORD BytesToWrite = blockSize;
	DWORD BytesWrite;
	LARGE_INTEGER FileOffset;
	FileOffset.QuadPart = StartOffset;
	ULONGLONG CurrentPosition = SetFilePointer( outputHandle_,
		FileOffset.LowPart, &FileOffset.HighPart, FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}

	bool WriteResult = WriteFile( outputHandle_, writeBuffer, BytesToWrite,
		&BytesWrite, NULL );

	if ( !WriteResult || BytesWrite != BytesToWrite )
	{
		return false;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::encyptBlock(
	BYTE *      bytes,
    BYTE *      enc_bytes,
    CHAR *szPassword )
{
	generateKey(szPassword);
	DWORD count=BLOCK_LENGTH;
    memcpy(enc_bytes, bytes, BLOCK_LENGTH);
	if(!CryptEncrypt(hSessionKey_,0,true,0,enc_bytes,&count,BLOCK_LENGTH))                       //Шифрование и вывод результата
	{
		HandleError("Error CryptEncrypt");
		return false;
	}
	else
	{
        cout << "Encryption Success!!" << endl;
	    cout << enc_bytes << endl;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::decryptBlock(
	BYTE *      enc_bytes,
    BYTE *      dec_bytes,
    CHAR *szPassword )
{
	generateKey(szPassword);
	DWORD count=BLOCK_LENGTH;
	memcpy(dec_bytes, enc_bytes, BLOCK_LENGTH);
	if(!CryptDecrypt(hSessionKey_,0,true,0,dec_bytes,&count))                       //Дешифровка и вывод результата
	{
		HandleError("Error CryptEncrypt");
		return false;
	}
	else
	{
	    cout << "Decryption Success!!" << endl;
		cout << dec_bytes << endl;
	}
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::saveKey( )
{
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::loadKey( )
{
	return true;
}
// ---------------------------------------------------------------------------
bool Cryptography::generateKey( CHAR *szPassword )
{
    HCRYPTHASH hHash;
	DWORD dwLength = (DWORD)strlen(szPassword);
	//--------------------------------------------------------------------
	// Получение дескриптора контекста криптографического провайдера.
	hProvType = PROV_GOST_2012_256;
	if(CryptAcquireContext(
			&hCryptProvider_,
			NULL,
			NULL,
			hProvType,
			CRYPT_VERIFYCONTEXT))
	{
		printf("A context has been acquired. \n");
	}
	else
	{
		HandleError("Error during CryptAcquireContext!");
		return false;
	}
	//--------------------------------------------------------------------
	// Создание пустого объекта хеширования.
	// Хеширование алгоритмом ГОСТ Р 34.11-2012

	if(CryptCreateHash(
			hCryptProvider_,
			CALG_GR3411_2012_256,
			0,
			0,
			&hHash))
	{
		printf("An empty hash object has been created. \n");
	}
	else
	{
		HandleError("Error during CryptCreateHash!");
		return false;
	}
	//--------------------------------------------------------------------
	// Хеширование строки пароля.
	if(CryptHashData(
			hHash,
			(BYTE *)szPassword,
			dwLength,
			0))
	{
		printf("The password has been hashed. \n");
	}
	else
	{
		HandleError("Error during CryptHashData!");
		return false;
	}
	//--------------------------------------------------------------------
	// Создание сессионного ключа, основанного на хеше, полученного из пароля.

	if(CryptDeriveKey(
			hCryptProvider_,
			CALG_G28147,
			hHash,
			CRYPT_EXPORTABLE,
			&hSessionKey_))
	{
		printf("The key has been derived. \n");
	}
	else
	{
		HandleError("Error during CryptDeriveKey!");
		return false;
	}
	BYTE default_IV[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	if(CryptSetKeyParam(hSessionKey_,KP_IV,default_IV,0))
	{
		printf("New initialization vector is set.\n");
	}
	else
	{
		HandleError("The new IV was not set.");
		return false;
	}
	return true;
}
// ---------------------------------------------------------------------------
void Cryptography::HandleError(char *s)
{
	printf("An error occurred in running the program.\n");
	printf("%s\n",s);
	printf("Error number %x\n.",GetLastError());
	printf("Program terminating.\n");
}
// ---------------------------------------------------------------------------
