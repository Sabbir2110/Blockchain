#include <iostream>
#include <string>
#include <iomanip>

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace std;


void printHex(unsigned char* sig, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        cout << hex << setw(2) << setfill('0')
             << (int)sig[i];
    }
    cout << dec << endl;
}

int main()
{

    EVP_PKEY* pkey = EVP_RSA_gen(2048);

    if(!pkey)
    {
        cout << "Key generation failed.\n";
        return 1;
    }

    string message;

    cout << "Enter message: ";
    getline(cin, message);



    EVP_MD_CTX* signCtx = EVP_MD_CTX_new();

    EVP_DigestSignInit(signCtx, NULL, EVP_sha256(), NULL, pkey);

    EVP_DigestSignUpdate(signCtx,
                         message.c_str(),
                         message.size());

    size_t sigLen = 0;

    EVP_DigestSignFinal(signCtx, NULL, &sigLen);

    unsigned char* signature =
        new unsigned char[sigLen];

    EVP_DigestSignFinal(signCtx,
                        signature,
                        &sigLen);

    EVP_MD_CTX_free(signCtx);


    EVP_MD_CTX* verifyCtx = EVP_MD_CTX_new();

    EVP_DigestVerifyInit(verifyCtx,
                         NULL,
                         EVP_sha256(),
                         NULL,
                         pkey);

    EVP_DigestVerifyUpdate(verifyCtx,
                           message.c_str(),
                           message.size());

    int result =
        EVP_DigestVerifyFinal(verifyCtx,
                              signature,
                              sigLen);

    EVP_MD_CTX_free(verifyCtx);

    cout << "\nOriginal Message:\n";
    cout << message << endl;

    cout << "\nDigital Signature (Hex):\n";
    printHex(signature, sigLen);

    if(result == 1)
        cout << "\nVerification Result: VALID\n";
    else
        cout << "\nVerification Result: INVALID\n";



    string modified = message;

    if(!modified.empty())
        modified[0] = (modified[0] == 'A') ? 'B' : 'A';

    EVP_MD_CTX* verifyCtx2 = EVP_MD_CTX_new();

    EVP_DigestVerifyInit(verifyCtx2,
                         NULL,
                         EVP_sha256(),
                         NULL,
                         pkey);

    EVP_DigestVerifyUpdate(verifyCtx2,
                           modified.c_str(),
                           modified.size());

    result =
        EVP_DigestVerifyFinal(verifyCtx2,
                              signature,
                              sigLen);

    EVP_MD_CTX_free(verifyCtx2);

    cout << "\nModified Message:\n";
    cout << modified << endl;

    if(result == 1)
        cout << "\nVerification Result: VALID\n";
    else
        cout << "\nVerification Result: INVALID\n";

    cout << "\nExplanation:\n";
    cout << "The digital signature is created from the original message hash.\n";
    cout << "Changing even one character changes the SHA-256 hash completely.\n";
    cout << "Since the signature corresponds to the original hash, the modified message produces a different hash.\n";
    cout << "Therefore, the old signature cannot be verified and verification fails.\n";

    delete[] signature;
    EVP_PKEY_free(pkey);

    return 0;
}
