#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

string hashData(string s) {
    return to_string(hash<string>{}(s));
}

int main() {
    vector<string> data = {"A", "B", "C", "D"};
    vector<string> hashes;

    // Leaf hashes
    for (string x : data)
        hashes.push_back(hashData(x));

    // Build Merkle Tree
    while (hashes.size() > 1) {
        vector<string> temp;

        for (int i = 0; i < hashes.size(); i += 2) {
            if (i + 1 < hashes.size())
                temp.push_back(hashData(hashes[i] + hashes[i + 1]));
            else
                temp.push_back(hashData(hashes[i] + hashes[i])); // duplicate last hash
        }

        hashes = temp;
    }

    cout << "Merkle Root: " << hashes[0] << endl;

    return 0;
}

*/or/*

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
using namespace std;

string sha256(string input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << hex << setw(2) << setfill('0') << (int)hash[i];

    return ss.str();
}

int main() {
    int n;
    cout << "Enter number of transactions: ";
    cin >> n;
    cin.ignore();

    vector<string> hashes;

    for (int i = 0; i < n; i++) {
        string tx;
        cout << "Transaction " << i + 1 << ": ";
        getline(cin, tx);
        hashes.push_back(sha256(tx));
    }

    while (hashes.size() > 1) {
        if (hashes.size() % 2 != 0)
            hashes.push_back(hashes.back());

        vector<string> temp;

        for (int i = 0; i < hashes.size(); i += 2)
            temp.push_back(sha256(hashes[i] + hashes[i + 1]));

        hashes = temp;
    }

    cout << "\nMerkle Root:\n" << hashes[0] << endl;

    return 0;
}
  
