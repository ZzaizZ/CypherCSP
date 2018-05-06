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
		std::wstring password );
	bool decryptBlock(
		BYTE *      bytes,
		std::string key );
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
	const DWORD BLOCK_LENGTH = 4096;
	void HandleError(char *s);
	bool generateKey( std::wstring password );

} ;

#endif
