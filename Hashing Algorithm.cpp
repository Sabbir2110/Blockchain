#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
using namespace std;

string getHash(string msg) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)msg.c_str(), msg.size(), hash);

    string result = "";
    char buf[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(buf, "%02x", hash[i]);
        result += buf;
    }
    return result;
}

int main() {
    string msg1, msg2;

    cout << "Enter Original Message: ";
    getline(cin, msg1);

    cout << "Enter Message to Check: ";
    getline(cin, msg2);

    string hash1 = getHash(msg1);
    string hash2 = getHash(msg2);

    cout << "\nOriginal Hash: " << hash1 << endl;
    cout << "Check Hash   : " << hash2 << endl;

    if (hash1 == hash2)
        cout << "Hash Match (Integrity Verified)";
    else
        cout << "Hash Mismatch (Message Modified)";

    return 0;
}
