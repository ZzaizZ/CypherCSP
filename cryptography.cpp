// ---------------------------------------------------------------------------
#pragma hdrstop

#include <iostream>
#include "cryptography.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

// ---------------------------------------------------------------------------
cryptography::cryptography( )
{
	inputHandle_ = 0;
	outputHandle_ = 0;
	keyHandle_ = 0;
	hSessionKey_ = NULL;
	hCryptProvider_ = NULL;
	BLOCK_LENGTH = 4096;
}

// ---------------------------------------------------------------------------
bool cryptography::open(
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
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( outputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::close( )
{
	CloseHandle( inputHandle_ );
	CloseHandle( outputHandle_ );
	CloseHandle( keyHandle_ );
	return true;
}
// ---------------------------------------------------------------------------

bool cryptography::readBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	BYTE *    readBuffer )
{
	if ( inputHandle_ == 0 || inputHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	DWORD FileSize = GetFileSize( inputHandle_, NULL );
	ULONGLONG StartOffset = blockSize * numberBlock;
	DWORD BytesToRead;
	if ( StartOffset + blockSize >= FileSize )
	{
		if ( StartOffset >= FileSize )
		{
			return false;
		}
		BytesToRead = FileSize - StartOffset;
	}
	else
	{
		BytesToRead = blockSize;
	}
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
	memset( readBuffer, 0, blockSize );
	bool ReadResult = ReadFile( inputHandle_, readBuffer, BytesToRead,
		&BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::writeBlock(
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
bool cryptography::encryptBlock(
	BYTE * bytes,
	CHAR * szPassword )
{
	if ( !generateKey( szPassword ) )
	{
		MessageBoxW( NULL, L"Ошибка генерации ключа", L"Error", MB_OK );
	}
	DWORD count = BLOCK_LENGTH;
	// memcpy_s( enc_bytes, count, bytes, BLOCK_LENGTH );
	if ( !CryptEncrypt( hSessionKey_, 0, true, 0, bytes, &count,
		BLOCK_LENGTH ) ) // Шифрование и вывод результата
	{
		MessageBoxW( NULL, L"Ошибка шифрования!", L"Error", MB_OK );
		return false;
	}
	else
	{
		// MessageBoxW( NULL, L"Шифрование успешно!", L"Error", MB_OK );
		// cout << "Encryption Success!!" << endl;
		// cout << enc_bytes << endl;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::decryptBlock(
	BYTE * enc_bytes,
	CHAR * szPassword )
{
	if ( !generateKey( szPassword ) )
	{
		MessageBoxW( NULL, L"Ошибка генерации ключа", L"Error", MB_OK );
	}
	DWORD count = BLOCK_LENGTH;
	// memcpy_s( dec_bytes, count, enc_bytes, BLOCK_LENGTH );
	if ( !CryptDecrypt( hSessionKey_, 0, true, 0, enc_bytes, &count ) )
		// Дешифровка и вывод результата
	{
		MessageBoxW( NULL, L"Ошибка дешифрования!", L"Error", MB_OK );
		return false;
	}
	else
	{
		// MessageBoxW( NULL, L"Дешифровка успешна", L"Error", MB_OK );
		// cout << "Decryption Success!!" << endl;
		// cout << dec_bytes << endl;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::saveKey( )
{
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::loadKey( )
{
	return true;
}

// ---------------------------------------------------------------------------
bool cryptography::generateKey( CHAR * szPassword )
{
	HCRYPTHASH hHash;
	DWORD dwLength = ( DWORD )strlen( szPassword );
	// --------------------------------------------------------------------
	// Получение дескриптора контекста криптографического провайдера.
	hProvType = PROV_GOST_2012_256;
	if ( CryptAcquireContext( &hCryptProvider_, NULL, NULL, hProvType,
		CRYPT_VERIFYCONTEXT ) )
	{
		printf( "A context has been acquired. \n" );
	}
	else
	{
		MessageBoxW( NULL, L"Ошибка инициализации криптопровайдера", L"Error",
			MB_OK );
		return false;
	}
	// --------------------------------------------------------------------
	// Создание пустого объекта хеширования.
	// Хеширование алгоритмом ГОСТ Р 34.11-2012

	if ( CryptCreateHash( hCryptProvider_, CALG_GR3411_2012_256, 0, 0,
		&hHash ) )
	{
		printf( "An empty hash object has been created. \n" );
	}
	else
	{
		MessageBoxW( NULL, L"Ошибка создания хэша", L"Error", MB_OK );
		return false;
	}
	// --------------------------------------------------------------------
	// Хеширование строки пароля.
	if ( CryptHashData( hHash, ( BYTE * )szPassword, dwLength, 0 ) )
	{
		printf( "The password has been hashed. \n" );
	}
	else
	{
		MessageBoxW( NULL, L"Ошибка хэширования", L"Error", MB_OK );
		return false;
	}
	// --------------------------------------------------------------------
	// Создание сессионного ключа, основанного на хеше, полученного из пароля.

	if ( CryptDeriveKey( hCryptProvider_, CALG_G28147, hHash, CRYPT_EXPORTABLE,
		&hSessionKey_ ) )
	{
		printf( "The key has been derived. \n" );
	}
	else
	{
		MessageBoxW( NULL, L"Ошибка создания ключа на основе хэша", L"Error",
			MB_OK );
		return false;
	}
	BYTE default_IV[ 8 ] =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	} ;
	if ( CryptSetKeyParam( hSessionKey_, KP_IV, default_IV, 0 ) )
	{
		printf( "New initialization vector is set.\n" );
	}
	else
	{
		MessageBoxW( NULL, L"Ошибка создания вектора инициализации", L"Error",
			MB_OK );
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
void cryptography::HandleError( char * s )
{
	printf( "An error occurred in running the program.\n" );
	printf( "%s\n", s );
	printf( "Error number %x\n.", GetLastError( ) );
	printf( "Program terminating.\n" );
}
// ---------------------------------------------------------------------------
