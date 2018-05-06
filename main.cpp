#include <iostream>
#include <stdio.h>
#include <clocale>
#include <windows.h>
#include <wincrypt.h>
#include "include/WinCryptEx.h"

#include "cryptography.h"

using namespace std;

int main(void)
{
    char string[]="qazwsxedc rfv \nrfv 123";        //Сообщение для шифрования

    // ОЧИСТКА ПАМЯТИ

//    if(hHash)
//        CryptDestroyHash(hHash);
//
//    // Уничтожение сессионного ключа.
//    if(hKey)
//        CryptDestroyKey(hKey);
//
//    // Освобождение дескриптора провайдера.
//    if(hProv)
//        CryptReleaseContext(hProv, 0);
//    if(Encrypt)
//        fclose (Encrypt);
//    if(vectorf)
//        fclose (vectorf);
//    if(source)
//        fclose(source);

//    printf("The program to derive a key completed without error. \n");

    Cryptography *c = new Cryptography();
    CHAR szPassword[] = "123456";
    //BYTE test_data[16] = {0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56,0x56};
    char test_data[]="qazwsxedc rfv rf";
    cout << test_data << endl;
    c->encyptBlock((BYTE*)test_data, (BYTE*)test_data, szPassword);
    c->decryptBlock((BYTE*)test_data, (BYTE*)test_data, szPassword);

    return 0;
}