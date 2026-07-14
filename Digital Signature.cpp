#include <iostream>
using namespace std;

long long power(long long a, long long b, long long m) {
    long long r = 1;
    while (b > 0) {
        r = (r * a) % m;
        b--;
    }
    return r;
}

int main() {
    long long message = 12;

    // RSA Keys
    long long n = 33;   // 3 * 11
    long long e = 3;    // Public key
    long long d = 7;    // Private key

    // Sign
    long long signature = power(message, d, n);

    // Verify
    long long verify = power(signature, e, n);

    cout << "Message   : " << message << endl;
    cout << "Signature : " << signature << endl;
    cout << "Verified  : " << verify << endl;

    if (verify == message)
        cout << "Digital Signature Verified";
    else
        cout << "Verification Failed";

    return 0;
}
