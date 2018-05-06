// ---------------------------------------------------------------------------

#ifndef cryptographyH
#define cryptographyH
#include <string>
#include <windows.h>
#include <wincrypt.h>
#include "include/wincryptex.h"

// ---------------------------------------------------------------------------
class Cryptography
{
public:
	Cryptography( );
	~Cryptography( );
	bool open(
		std::wstring inputPath,
		std::wstring outputPath );
	bool close( );
	bool encyptBlock(
		BYTE *      bytes,
        BYTE *      enc_bytes,
        CHAR *szPassword );
	bool decryptBlock(
		BYTE *      enc_bytes,
        BYTE *      dec_bytes,
        CHAR *szPassword );
	bool readBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    readBuffer );
	bool writeBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    writeBuffer );
	bool loadKey( );
	bool saveKey( );

private:
	HCRYPTKEY hSessionKey_;
	HCRYPTPROV hCryptProvider_;
	HANDLE inputHandle_;
	HANDLE outputHandle_;
	HANDLE keyHandle_;
	DWORD hProvType;
	const DWORD BLOCK_LENGTH = 16;
	void HandleError(char *s);
	bool generateKey( CHAR *szPassword );

} ;

#endif
