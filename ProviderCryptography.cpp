// ---------------------------------------------------------------------------
#pragma hdrstop

#include <iostream>
#include "ProviderCryptography.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

// ---------------------------------------------------------------------------
ProviderCryptography::ProviderCryptography( DWORD hProvType )
{
	hSessionKey_ = NULL;
	hCryptProvider_ = NULL;
	hProvType_ = hProvType;
	sourceHandle_ = 0;
	destinationHandle_ = 0;
}

ProviderCryptography::~ProviderCryptography( )
{
	if ( hCryptProvider_ )
	{
		CryptReleaseContext( hCryptProvider_, 0 );
	}
	if ( hSessionKey_ )
	{
		CryptDestroyKey( hSessionKey_ );
	}
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::Open(
	std::wstring sourceFile,
	std::wstring destinationFile )
{
	sourceHandle_ = CreateFileW( sourceFile.c_str( ), GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( sourceHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	destinationHandle_ = CreateFileW( destinationFile.c_str( ), GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( destinationHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::Close( )
{
	CloseHandle( sourceHandle_ );
	CloseHandle( destinationHandle_ );
	return true;
}
// ---------------------------------------------------------------------------

bool ProviderCryptography::ReadBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	BYTE *    readBuffer )
{
	if ( sourceHandle_ == 0 || sourceHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	DWORD FileSize = GetFileSize( sourceHandle_, NULL );
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
	ULONGLONG CurrentPosition = SetFilePointer( sourceHandle_,
		FileOffset.LowPart, &FileOffset.HighPart, FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}
	memset( readBuffer, 0, blockSize );
	BYTE * innerBuffer = new BYTE[ BytesToRead ];
	bool ReadResult = ReadFile( sourceHandle_, innerBuffer, BytesToRead,
		&BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		delete[ ]innerBuffer;
		return false;
	}
	memcpy_s( readBuffer, blockSize, innerBuffer, BytesToRead );
	delete[ ]innerBuffer;
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::WriteBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	BYTE *    writeBuffer )
{
	if ( destinationHandle_ == 0 || destinationHandle_ == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	ULONGLONG StartOffset = blockSize * numberBlock;
	DWORD BytesToWrite = blockSize;
	DWORD BytesWrite;
	LARGE_INTEGER FileOffset;
	FileOffset.QuadPart = StartOffset;
	ULONGLONG CurrentPosition = SetFilePointer( destinationHandle_,
		FileOffset.LowPart, &FileOffset.HighPart, FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}

	bool WriteResult = WriteFile( destinationHandle_, writeBuffer, BytesToWrite,
		&BytesWrite, NULL );

	if ( !WriteResult || BytesWrite != BytesToWrite )
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::EncryptBlock(
	BYTE * bytes,
	DWORD  blockSize )
{
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
	if ( !CryptSetKeyParam( hSessionKey_, KP_IV, default_IV, 0 ) )
	{
		MessageBoxW( NULL, L"Ошибка создания вектора инициализации", L"Error",
			MB_OK );
		return false;
	}
	DWORD count = blockSize;
	if ( !CryptEncrypt( hSessionKey_, 0, true, 0, bytes, &count,
		blockSize ) ) // Шифрование и вывод результата
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::DecryptBlock(
	BYTE * enc_bytes,
	DWORD  blockSize )
{
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
	if ( !CryptSetKeyParam( hSessionKey_, KP_IV, default_IV, 0 ) )
	{
		MessageBoxW( NULL, L"Ошибка создания вектора инициализации", L"Error",
			MB_OK );
		return false;
	}
	DWORD count = blockSize;
	if ( !CryptDecrypt( hSessionKey_, 0, true, 0, enc_bytes, &count ) )
		// Дешифровка и вывод результата
	{
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::SaveKey( std::wstring keyFile )
{
	if ( hSessionKey_ )
	{
		HCRYPTHASH hHash = 0;
		if ( !CryptCreateHash( // Создаем объект хэша
			hCryptProvider_, CALG_GR3411_2012_256, 0, 0, &hHash ) )
		{
			return false;
		}
		int length = password_.size( ); // Длина пароля

		if ( !CryptHashData( // Хэшируем пароль
			hHash, password_.c_str( ), length, 0 ) )
		{
			return false;
		}

		BYTE * Hash;
		DWORD HashLength;
		if ( !CryptGetHashParam( // Узнаем длину хэша
			hHash, HP_HASHVAL, NULL, &HashLength, 0 ) )
		{
			return false;
		}
		Hash = new BYTE[ HashLength ];
		if ( !CryptGetHashParam( // Читаем значение хэша
			hHash, HP_HASHVAL, Hash, &HashLength, 0 ) )
		{
			return false;
		}

		HANDLE KeyHandle = CreateFileW( // Открываем файл назначения
			keyFile.c_str( ), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( KeyHandle == INVALID_HANDLE_VALUE )
		{
			return false;
		}

		DWORD BytesWrite = 0;

		bool WriteResult = WriteFile( KeyHandle, Hash, HashLength,
			&BytesWrite, NULL );
		if ( !WriteResult || BytesWrite != HashLength )
		{
			return false;
		}

		if ( hHash )
		{
			CryptDestroyHash( hHash );
		} // Уничтожаем объект хэша
		CloseHandle( KeyHandle );
		delete[ ]Hash;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::GenerateKey( CHAR * password )
{

	HCRYPTHASH hHash;
	DWORD dwLength = ( DWORD )strlen( password );
	password_ = password;
	// Получение дескриптора контекста криптографического провайдера.

	if ( !CryptAcquireContext( &hCryptProvider_, NULL, NULL, hProvType_,
		CRYPT_VERIFYCONTEXT ) )
	{
		MessageBoxW( NULL, L"Ошибка инициализации криптопровайдера", L"Error",
			MB_OK );
		return false;
	}
	// Создание пустого объекта хеширования.
	// Хеширование алгоритмом ГОСТ Р 34.11-2012

	if ( !CryptCreateHash( hCryptProvider_, CALG_GR3411_2012_256, 0, 0,
		&hHash ) )
	{
		MessageBoxW( NULL, L"Ошибка создания хэша", L"Error", MB_OK );
		return false;
	}
	// Хеширование строки пароля.
	if ( !CryptHashData( hHash, ( BYTE * )password, dwLength, 0 ) )
	{
		MessageBoxW( NULL, L"Ошибка хэширования", L"Error", MB_OK );
		return false;
	}
	// Создание сессионного ключа, основанного на хеше, полученного из пароля.

	if ( !CryptDeriveKey( hCryptProvider_, CALG_G28147, hHash, CRYPT_EXPORTABLE,
		&hSessionKey_ ) )
	{
		MessageBoxW( NULL, L"Ошибка создания ключа на основе хэша", L"Error",
			MB_OK );
		return false;
	}

	if ( hHash )
	{
		CryptDestroyHash( hHash );
	}
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::GenerateKey( std::wstring keyFile )
{

	HCRYPTHASH hHash;
	if ( !CryptAcquireContext( // Создаем контейнер
		&hCryptProvider_, NULL, NULL, hProvType_, CRYPT_VERIFYCONTEXT ) )
	{
		MessageBoxW( NULL, L"Ошибка инициализации криптопровайдера", L"Error",
			MB_OK );
		return false;
	}
	if ( !CryptCreateHash( // Создаем объект хэша
		hCryptProvider_, CALG_GR3411_2012_256, 0, 0, &hHash ) )
	{
		MessageBoxW( NULL, L"Ошибка создания хэша", L"Error", MB_OK );
		return false;
	}
	DWORD HashLength = 0;
	if ( !CryptGetHashParam( // Узнаем длину хэша
		hHash, HP_HASHVAL, NULL, &HashLength, 0 ) )
	{
		MessageBoxW( NULL, L"Ошибка распознавания длины хэша", L"Error",
		MB_OK );
		return false;
	}

	HANDLE KeyHandle = CreateFileW( // Открываем файл источника
		keyFile.c_str( ), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( KeyHandle == INVALID_HANDLE_VALUE )
	{
		return false;
	}

	LARGE_INTEGER offset; // Смещение в файле источника
	offset.QuadPart = 0;

	BYTE * Hash = new BYTE[ HashLength ]; // Значение хэша
	DWORD BytesRead = 0;
	bool ReadResult = ReadFile( // Читаем хэш из файла
		KeyHandle, Hash, HashLength, &BytesRead, NULL );
	if ( !ReadResult || BytesRead != HashLength )
	{
		return false;
	}
	if ( !CryptSetHashParam( // Устанавливаем хэш
		hHash, HP_HASHVAL, Hash, 0 ) )
	{
		return false;
	}
	if ( !CryptDeriveKey( // Создаем ключ на основе хэша пароля
		hCryptProvider_, CALG_G28147, hHash, CRYPT_EXPORTABLE, &hSessionKey_ ) )
	{
		MessageBoxW( NULL, L"Ошибка создания ключа на основе хэша", L"Error",
			MB_OK );
		return false;
	}
	if ( hHash )
	{
		CryptDestroyHash( hHash );
	} // Уничтожаем объект хэша

	delete[ ]Hash;
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::EncryptFile(
	std::wstring sourceFile,
	std::wstring destinationFile )
{
	BYTE buffer[ BLOCK_LENGTH ];
	int i = 0;
	bool sucsess = true;
	if ( !Open( sourceFile, destinationFile ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
		return false;
	}
	else
	{
		while ( ReadBlock( i, BLOCK_LENGTH, buffer ) )
		{
			if ( !EncryptBlock( buffer, BLOCK_LENGTH ) )
			{
				sucsess = false;
				break;
			}
			WriteBlock( i, BLOCK_LENGTH, buffer );
			i++ ;
		}
		Close( );
		if ( sucsess )
		{
			MessageBoxW( NULL, L"Файл зашифрован", L"Готово", MB_OK );
			return true;
		}
	}
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::DecryptFile(
	std::wstring sourceFile,
	std::wstring destinationFile )
{
	BYTE buffer[ BLOCK_LENGTH ];
	int i = 0;
	bool sucsess = true;
	if ( !Open( sourceFile, destinationFile ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
		return false;
	}
	else
	{
		while ( ReadBlock( i, BLOCK_LENGTH, buffer ) )
		{
			if ( !DecryptBlock( buffer, BLOCK_LENGTH ) )
			{
				sucsess = false;
				break;
			}
			WriteBlock( i, BLOCK_LENGTH, buffer );
			i++ ;
		}
		Close( );
		if ( sucsess )
		{
			MessageBoxW( NULL, L"Файл расшифрован", L"Готово", MB_OK );
			return true;
		}
	}
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
bool ProviderCryptography::GenKeyPair(
	const wchar_t * containerName,
	wchar_t *       pkPath )
{
	if ( !CryptAcquireContext( &keyPairProvider_, containerName, NULL,
		hProvType_, CRYPT_NEWKEYSET ) )
	{
		MessageBoxW( NULL, L"Ошибка инициализации криптопровайдера", L"Error",
			MB_OK );
		return false;
	}
	else
	{
		if ( !CryptGenKey( keyPairProvider_, AT_KEYEXCHANGE, CRYPT_EXPORTABLE,
			&keypair_ ) )
		{
			MessageBoxW( NULL, L"Ошибка генерации ключевой пары", L"Error",
				MB_OK );
			return false;
		}
	}
	MessageBoxW( NULL, L"Ключи сгенерированы", L"Информация", MB_OK );
	ExportPublicKeyToFile( pkPath );
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::LoadKeyPair( const wchar_t * containerName )
{
	if ( !CryptAcquireContext( &keyPairProvider_, L"MyContainerName", NULL,
		hProvType_, 0 ) )
	{
		MessageBoxW( NULL, L"Указанный криптоконтейнер не существует", L"Error",
			MB_OK );
		return false;
	}
	if ( !CryptGetUserKey( keyPairProvider_, AT_KEYEXCHANGE, &keypair_ ) )
	{
		MessageBoxW( NULL, L"Ошибка экспорта ключа", L"Error", MB_OK );
		long e = GetLastError( );
		return false;
	}
	MessageBoxW( NULL, L"Ключи загружены!", L"Информация", MB_OK );
	return true;
}

// ---------------------------------------------------------------------------
bool ProviderCryptography::ExportPublicKeyToFile( const wchar_t * path )
{
	// Определение размера BLOBа открытого ключа и распределение памяти.
	DWORD cbKeyBlob;
	CryptExportKey( keypair_, 0, PUBLICKEYBLOB, 0, NULL, & cbKeyBlob );
	// указатель на ключевой BLOB
	BYTE * pbKeyBlob = new BYTE[ cbKeyBlob ];
	long error = GetLastError( );
	// Экспортирование открытого ключа в BLOB открытого ключа.
	if ( !CryptExportKey( keypair_, 0, PUBLICKEYBLOB, 0, pbKeyBlob,
		&cbKeyBlob ) )
	{
		MessageBoxW( NULL, L"Ошибка при экспорте открытого ключа в BLOB",
			L"Error", MB_OK );
		long error = GetLastError( );
		return false;
	}
	HANDLE keyPairHandle = 0;
	if ( !( keyPairHandle = CreateFileW( path, GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL ) ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
		long error = GetLastError( );
		return false;
	}

	DWORD dwBytesWritten;
	if ( !WriteFile( keyPairHandle, // open file handle
		pbKeyBlob, // start of data to write
		cbKeyBlob, // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL ) )
	{
		MessageBoxW( NULL, L"Ошибка записи открытого ключа в файл", L"Error",
			MB_OK );
		long error = GetLastError( );
		return false;
	}
	MessageBoxW( NULL, L"Открытый ключ экспортирован успешно!", L"Информация",
		MB_OK );
	return true;
}
// ---------------------------------------------------------------------------
