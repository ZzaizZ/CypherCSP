#include <iostream>
#include <stdio.h>
#include <clocale>
#include <windows.h>
#include <wincrypt.h>
#include "include/WinCryptEx.h"

#include "cryptography.h"

using namespace std;

static HCRYPTPROV hProv;            // Дескриптор криптопровайдера
static FILE *source=NULL;               // Исходный файл
static FILE *Encrypt=NULL;              // Зашифрованный файл
static DWORD hProvType = PROV_GOST_2012_256;        // Тип используемого криптопровайдера (80)

void HandleError(char *s)
{
    printf("An error occurred in running the program.\n");
    printf("%s\n",s);
    printf("Error number %x\n.",GetLastError());
    printf("Program terminating.\n");
    exit(1);
}

//--------------------------------------------------------------------
// Пример создания сессионного ключа, основанного на хеше, рассчитанного
// из пароля пользователя. Пароль вводится в процессе работы программы.
// Замечание: под win32 рекомендуется использовать _s аналоги CRT функций.
//--------------------------------------------------------------------

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

static HCRYPTKEY hKey = 0;
static HCRYPTHASH hHash = 0;

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    //--------------------------------------------------------------------
    //  Пароль из которого будет получен сессионный ключ.

    CHAR szPassword[] = "123456\0";
    DWORD dwLength;


    dwLength = (DWORD)strlen(szPassword);

    //--------------------------------------------------------------------
    // Получение дескриптора контекста криптографического провайдера.

    if(CryptAcquireContext(
            &hProv,
            NULL,
            NULL,
            hProvType,
            CRYPT_VERIFYCONTEXT))
    {
        printf("A context has been acquired. \n");
    }
    else
    {
        HandleError("Error during CryptAcquireContext!");
    }
    //--------------------------------------------------------------------
    // Создание пустого объекта хеширования.
    // Хеширование алгоритмом ГОСТ Р 34.11-2012

    if(CryptCreateHash(
            hProv,
            CALG_GR3411_2012_256,
            0,
            0,
            &hHash))
    {
        printf("An empty hash object has been created. \n");
    }
    else
    {
        HandleError("Error during CryptCreateHash!");
    }
    //--------------------------------------------------------------------
    // Хеширование строки пароля.

    if(CryptHashData(
            hHash,
            (BYTE *)szPassword,
            dwLength,
            0))
    {
        printf("The password has been hashed. \n");
    }
    else
    {
        HandleError("Error during CryptHashData!");
    }
    //--------------------------------------------------------------------
    // Создание сессионного ключа, основанного на хеше, полученного из пароля.

    if(CryptDeriveKey(
            hProv,
            CALG_G28147,
            hHash,
            CRYPT_EXPORTABLE,
            &hKey))
    {
        printf("The key has been derived. \n");
    }
    else
    {
        HandleError("Error during CryptDeriveKey!");
    }

    static FILE *vectorf=NULL;              // Файл для хранения вектора инициализации
    static FILE *EncryptionParam;           // Файл для хранения неменяемой части блоба

    if(!(vectorf = fopen("vector.bin", "wb")))
        HandleError( "Problem opening the file 'vector.bin'\n" );
    printf( "The file 'vector.bin' was opened\n" );

    //--------------------------------------------------------------------
    // Чтение режима шифрования.
    DWORD dwMode;
    DWORD dwCount = sizeof(DWORD);
    BYTE pbData[16];
    if(CryptGetKeyParam(
            hKey,
            KP_MODE,
            (BYTE*)&dwMode,
            &dwCount,
            0))
    {
        //---------------------------------------------------------------
        // Печать режима шифрования.

        printf("Default cipher mode: %d\n", dwMode);

    }
    else
    {
        HandleError("Error during CryptGetKeyParam.");
    }

    //---------------------------------------------------------------
    // Чтение вектора инициализации.

    //-------------------------------------------------------------
    //  Получение длины вектора инициализации.

    if(!CryptGetKeyParam(
            hKey,
            KP_IV,
            NULL,
            &dwCount,
            0))
    {
        HandleError("Error getting the IV length");
    }

    //--------------------------------------------------------------
    // Получение IV - вектора инициализации.

    if(CryptGetKeyParam(
            hKey,
            KP_IV,
            pbData,
            &dwCount,
            0))
    {
        //---------------------------------------------------------
        // Печать вектора инициализации.
        printf("Default IV:");
        for(int i=0;i<dwCount;i++)
            printf("%2.2x ",pbData[i]);
        printf("\n");
    }
    else
    {
        HandleError("Error getting the IV.");
    }



    FILE * file = fopen("test.txt", "r");
    if (!file){
        printf("Unable to open file");
        return 1;
    }

    FILE * Encrypt = fopen("encrypt.bin", "wb");
    if (!Encrypt){
        printf("Unable to open Encrypt file");
        return 1;
    }


    // ШИФРОВАНИЕ СТРОКИ ДАННЫХ

    #define BLOCK_LENGTH 4096
    BYTE pbContent[BLOCK_LENGTH];       // Указатель на содержимое исходного файла
    DWORD cbContent = 0;        // Длина содержимого
    DWORD bufLen = BLOCK_LENGTH;   // Длина буфера

    char string[]="qazwsxedc rfv \nrfv 123";        //Сообщение для шифрования

    cout << string << endl;
    DWORD count=strlen(string);
    BYTE default_IV[8] = {0,0,0,0,0,0,0,0};
    if(CryptSetKeyParam(hKey,KP_IV,default_IV,0))
    {
        printf("New initialization vector is set.\n");
    }
    else
    {
        HandleError("The new IV was not set.");
    }
    if(!CryptEncrypt(hKey,0,true,0,(BYTE *)string,&count,strlen(string)))                       //Шифрование и вывод результата
    {
        HandleError("Error CryptEncrypt");
    }
    else
    {
        cout << string << endl;
    }
    // РАСШИФРОВЫВАНИЕ СТРОКИ ДАННЫХ
    // Но сначала устанавливаем начальный вектор инициализации
    if(CryptSetKeyParam(hKey,KP_IV,default_IV,0))
    {
        printf("New initialization vector is set.\n");
    }
    else
    {
        HandleError("The new IV was not set.");
    }
    count=strlen(string);
    if(!CryptDecrypt(hKey,0,true,0,(BYTE *)string,&count))                                            //Дешифрование  и вывод результата
    {
        HandleError("Error CryptDecrypt");
    }
    else
    {
        cout << string << endl;
    }




    // ОЧИСТКА ПАМЯТИ

    if(hHash)
        CryptDestroyHash(hHash);

    // Уничтожение сессионного ключа.
    if(hKey)
        CryptDestroyKey(hKey);

    // Освобождение дескриптора провайдера.
    if(hProv)
        CryptReleaseContext(hProv, 0);
    if(Encrypt)
        fclose (Encrypt);
    if(vectorf)
        fclose (vectorf);
    if(source)
        fclose(source);

    printf("The program to derive a key completed without error. \n");

    Cryptography c = new Cryptography();

    //wstring password = L"123456";
    //c.encyptBlock((BYTE *)string, password);

    return 0;
}