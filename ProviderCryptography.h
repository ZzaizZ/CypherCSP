// ---------------------------------------------------------------------------

#ifndef ProviderCryptographyH
#define ProviderCryptographyH
#include <windows.h>
#include <wincrypt.h>
#include "include/wincryptex.h"
#include "Cryptography.h"
#define BLOCK_LENGTH 4096

// ---------------------------------------------------------------------------
class ProviderCryptography : Cryptography < HCRYPTKEY >
{
public:
	ProviderCryptography( DWORD hPovType );
	~ProviderCryptography( );
	bool EncryptFile(
		std::wstring sourceFile,
		std::wstring destinationFile );
	bool DecryptFile(
		std::wstring sourceFile,
		std::wstring destinationFile );
	bool GenerateKey( CHAR * password );
	bool GenerateKey( std::wstring keyFile );
	bool SaveKey( std::wstring );

private:
	HCRYPTPROV hCryptProvider_;
	DWORD hProvType_;
	HANDLE sourceHandle_;
	HANDLE destinationHandle_;

	std::string password_;

	bool Open(
		std::wstring sourceFile,
		std::wstring destinationFile );
	bool Close( );
	bool EncryptBlock(
		BYTE * bytes,
		DWORD  blockSize );
	bool DecryptBlock(
		BYTE * enc_bytes,
		DWORD  blockSize );
	bool ReadBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    readBuffer );
	bool WriteBlock(
		ULONGLONG numberBlock,
		DWORD     blockSize,
		BYTE *    writeBuffer );

} ;

#endif
