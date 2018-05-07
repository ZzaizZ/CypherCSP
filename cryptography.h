// ---------------------------------------------------------------------------

#ifndef cryptographyH
#define cryptographyH
#include <string>
#include <windows.h>
#include <wincrypt.h>
#include "include/wincryptex.h"

// ---------------------------------------------------------------------------
class cryptography
{
public:
	cryptography( );
	bool open(
		std::wstring inputPath,
		std::wstring outputPath );
	bool close( );
	bool encryptBlock(
		BYTE * bytes,
		CHAR * szPassword );
	bool decryptBlock(
		BYTE * enc_bytes,
		CHAR * szPassword );
	bool readBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    readBuffer );
	bool writeBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    writeBuffer );
	bool loadKey( std::wstring );
	bool saveKey( std::wstring );

private:
	HCRYPTKEY hSessionKey_;
	HCRYPTPROV hCryptProvider_;
	HANDLE inputHandle_;
	HANDLE outputHandle_;
	HANDLE keyHandle_;
	DWORD hProvType;
	DWORD BLOCK_LENGTH;

	void HandleError( char * s );
	bool generateKey( CHAR * szPassword );

} ;

#endif
