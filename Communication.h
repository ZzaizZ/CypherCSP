// ---------------------------------------------------------------------------

#ifndef CommunicationH
#define CommunicationH
// ---------------------------------------------------------------------------
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
// ---------------------------------------------------------------------------
#define REQ_WINSOCK_VER MAKEWORD(2,2)
#define DEFAULT_BUFLEN 1024
#define DEFAULT_FN 520
#define DEFAULT_PORT "4444"

// ---------------------------------------------------------------------------
class Communication
{
public:
	Communication( );
	bool SendFile( std::wstring sourceFile );
	bool RecieveFile( std::wstring destinationPath );

protected:
	WSADATA wsaData_;
	SOCKET connectSocket_;

	struct addrinfoW * result_;
	struct addrinfoW hints_;

	char bufferFileName_[ DEFAULT_FN ];
	char bufferData_[ DEFAULT_BUFLEN ];

	bool ReadBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		HANDLE    srcHandle,
		BYTE *    readBuffer,
		DWORD *   BytesRead );
	bool WriteBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		HANDLE    destHandle,
		BYTE *    writeBuffer,
		DWORD *   bytesWrite );
} ;

#endif
