// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Communication.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------

Communication::Communication( )
{
	connectSocket_ = INVALID_SOCKET;
	result_ = NULL;
}

// ---------------------------------------------------------------------------
bool Communication::SendFile( std::wstring sourceFile )
{
	HANDLE FileHandle = 0;
	HANDLE tmpHandle = 0;
	int iResult;
	WIN32_FIND_DATA fInfo;

	// Узнаем имя файла и конвертируем его для передачи по сети
	tmpHandle = FindFirstFile( sourceFile.c_str( ), &fInfo );
	WideCharToMultiByte( CP_UTF8, 0, fInfo.cFileName, MAX_PATH, bufferFileName_,
		DEFAULT_FN, NULL, NULL );
	FindClose( tmpHandle );
	tmpHandle = NULL;
	// Открываем файл, имя которого передается в функцию
	FileHandle = CreateFileW( sourceFile.c_str( ), GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL );
	if ( FileHandle == 0 || FileHandle == INVALID_HANDLE_VALUE )
	{
		closesocket( connectSocket_ );
		WSACleanup( );
		return false;
	}

	// Затем отправляем имя файла, которое на принимается на сервере
	iResult = send( connectSocket_, bufferFileName_,
		sizeof( bufferFileName_ ), 0 );
	if ( iResult == SOCKET_ERROR )
	{
		closesocket( connectSocket_ );
		WSACleanup( );
		return false;
	}

	// Проверка приема, путем отправки имени в обратную сторону
	char tempBufferFileName[ DEFAULT_FN ];
	iResult = recv( connectSocket_, tempBufferFileName,
		sizeof( tempBufferFileName ), 0 );

	if ( !strncmp( tempBufferFileName, bufferFileName_, DEFAULT_FN ) == 0 )
	{
		closesocket( connectSocket_ );
		WSACleanup( );
		return false;
	}

	// Осуществляем передачу блоков файла до тех пор пока он не закончится

	int i = 0;
	DWORD BytesRead;
	while ( ReadBlock( i, DEFAULT_BUFLEN, FileHandle, bufferData_,
		&BytesRead ) )
	{

		iResult = send( connectSocket_, bufferData_, sizeof( bufferData_ ), 0 );
		if ( iResult == SOCKET_ERROR )
		{
			closesocket( connectSocket_ );
			WSACleanup( );
			return false;
		}
		i++ ;
	}

	// Производим разрыв соединения
	iResult = shutdown( connectSocket_, SD_BOTH );
	if ( iResult == SOCKET_ERROR )
	{
		closesocket( connectSocket_ );
		WSACleanup( );
		return false;
	}
	// Производим стандартную деинициализацию Winsock и закрытие файла

	CloseHandle( FileHandle );
	return true;
}

// ---------------------------------------------------------------------------
bool Communication::RecieveFile( std::wstring destinationPath )
{
	char bufferFileName[ DEFAULT_FN ];
	char bufferData[ DEFAULT_BUFLEN ];
	wchar_t bufferFileNameW[ MAX_PATH ];
	bool recievedFileName = false;
	HANDLE FileHandle;
	int iResult, iSendResult;
	// Осуществляем прием имени файла, которое отправляется первым делом отправляющим лицом
	iResult = recv( connectSocket_, bufferFileName,
		sizeof( bufferFileName ), 0 );
	if ( iResult > 0 )
	{
		// Отправляем принятое имя файла обратно отправителю
		iSendResult = send( connectSocket_, bufferFileName, iResult, 0 );
		if ( iSendResult == SOCKET_ERROR )
		{
			closesocket( connectSocket_ );
			WSACleanup( );
			return false;
		}
		recievedFileName = true;
	}
	else
	{
		if ( iResult != 0 )
		{
			int err = WSAGetLastError( );
			closesocket( connectSocket_ );

			WSACleanup( );
			return false;
		}
	}
	// Производим создание файла с заданным именем
	if ( recievedFileName )
	{

		MultiByteToWideChar( CP_UTF8, NULL, bufferFileName,
			sizeof( bufferFileName ), bufferFileNameW,
		sizeof( bufferFileNameW ) );

		if ( destinationPath.empty( ) || destinationPath.size( ) -
			1 == destinationPath.find_last_of( L"\\" ) )
		{
			destinationPath.append( bufferFileNameW );
		}
		else
		{
			destinationPath.append( L"\\" );
			destinationPath.append( bufferFileNameW );
		}

		FileHandle = CreateFileW( destinationPath.c_str( ), GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL );
		if ( FileHandle == 0 || FileHandle == INVALID_HANDLE_VALUE )
		{
			closesocket( connectSocket_ );
			WSACleanup( );
			return false;
		}
		// Затем начинаем принимать сам файл и записывать его в соданный файл
		int i = 0;
		DWORD BytesToWrite = DEFAULT_BUFLEN;
		DWORD BytesWrite;
		do
		{
			iResult = recv( connectSocket_, bufferData,
				sizeof( bufferData ), 0 );
			if ( iResult > 0 )
			{
				if ( !WriteBlock( i, sizeof( bufferData ), FileHandle,
					bufferData, &BytesWrite ) )
				{
					closesocket( connectSocket_ );
					WSACleanup( );
					return false;
				}
				i++ ;
			}
			else
			{
				if ( iResult != 0 )
				{
					closesocket( connectSocket_ );
					WSACleanup( );
					return false;
				}
			}
		}
		while ( iResult > 0 );
	}

	// Производим разрыв соединения
	/* iResult = shutdown( connectSocket_, SD_BOTH );
	 if ( iResult == SOCKET_ERROR )
	 {
	 closesocket( connectSocket_ );
	 WSACleanup( );
	 return false;
	 } */

	// Стандартная очистка
	CloseHandle( FileHandle );
	return true;
}

// ---------------------------------------------------------------------------
bool Communication::ReadBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	HANDLE    srcHandle,
	BYTE *    readBuffer,
	DWORD *   bytesRead )
{

	DWORD FileSize = GetFileSize( srcHandle, NULL );
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
	ULONGLONG CurrentPosition = SetFilePointer( srcHandle, FileOffset.LowPart,
		&FileOffset.HighPart, FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}
	memset( readBuffer, 0, blockSize );
	BYTE * innerBuffer = new BYTE[ BytesToRead ];
	bool ReadResult = ReadFile( srcHandle, innerBuffer, BytesToRead,
		&BytesRead, NULL );

	if ( !ReadResult || BytesRead != BytesToRead )
	{
		delete[ ]innerBuffer;
		return false;
	}
	memcpy_s( readBuffer, blockSize, innerBuffer, BytesToRead );
	*bytesRead = BytesRead;
	delete[ ]innerBuffer;
	return true;

}

// ---------------------------------------------------------------------------
bool Communication::WriteBlock(
	ULONGLONG numberBlock,
	DWORD     blockSize,
	HANDLE    destHandle,
	BYTE *    writeBuffer,
	DWORD *   bytesWrite )
{
	ULONGLONG StartOffset = blockSize * numberBlock;
	DWORD BytesToWrite = blockSize;
	DWORD BytesWrite;
	LARGE_INTEGER FileOffset;
	FileOffset.QuadPart = StartOffset;
	ULONGLONG CurrentPosition = SetFilePointer( destHandle, FileOffset.LowPart,
		&FileOffset.HighPart, FILE_BEGIN );
	if ( CurrentPosition != FileOffset.LowPart )
	{
		return false;
	}
	bool WriteResult = WriteFile( destHandle, writeBuffer, BytesToWrite,
		&BytesWrite, NULL );

	if ( !WriteResult || BytesWrite != BytesToWrite )
	{

		return false;
	}

	*bytesWrite = BytesWrite;
	return true;

}
// ---------------------------------------------------------------------------
