// ---------------------------------------------------------------------------

#ifndef CryptographyH
#define CryptographyH
#include <string>

// ---------------------------------------------------------------------------
template < class T >
class Cryptography
{
protected:
	T hSessionKey_;

public:
	virtual bool EncryptFile(
		std::wstring sourceFile,
		std::wstring destinationFile ) = 0;
	virtual bool DecryptFile(
		std::wstring sourceFile,
		std::wstring destinationFile ) = 0;
} ;
#endif
