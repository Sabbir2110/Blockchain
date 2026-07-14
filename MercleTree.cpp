#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <openssl/sha.h>

using namespace std;

// Function to compute SHA-256
string sha256(const string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)input.c_str(), input.length(), hash);

    stringstream ss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}

int main()
{
    vector<string> transactions =
    {
        "alice pays bob 5 btc",
        "bob pays charlie 2 btc",
        "charlie pays david 1 btc",
        "david pays eva 3 btc"
    };

    vector<string> leafHashes;

    cout << "=============================\n";
    cout << "Leaf Hashes (SHA-256)\n";
    cout << "=============================\n\n";

    for (int i = 0; i < transactions.size(); i++)
    {
        string h = sha256(transactions[i]);
        leafHashes.push_back(h);

        cout << "t" << i + 1 << ": "
             << transactions[i] << endl;

        cout << "H" << i + 1 << ": "
             << h << endl << endl;
    }

    cout << "=============================\n";
    cout << "Intermediate Hashes\n";
    cout << "=============================\n\n";

    string h12 = sha256(leafHashes[0] + leafHashes[1]);
    string h34 = sha256(leafHashes[2] + leafHashes[3]);

    cout << "H12 = SHA256(H1 + H2)\n";
    cout << h12 << endl << endl;

    cout << "H34 = SHA256(H3 + H4)\n";
    cout << h34 << endl << endl;

    string merkleRoot = sha256(h12 + h34);

    cout << "=============================\n";
    cout << "Merkle Root\n";
    cout << "=============================\n\n";

    cout << "Root = SHA256(H12 + H34)\n";
    cout << merkleRoot << endl;

    cout << "\n\n";
    cout << "============== Merkle Tree ==============\n\n";

    cout << "                         Root\n";
    cout << "                         |\n";
    cout << "      ---------------------------------\n";
    cout << "      |                               |\n";
    cout << "     H12                             H34\n";
    cout << "      |                               |\n";
    cout << "   ---------                     ---------\n";
    cout << "   |       |                     |       |\n";
    cout << "  H1      H2                    H3      H4\n";
    cout << "   |       |                     |       |\n";
    cout << "  t1      t2                    t3      t4\n";

    return 0;
}
 or,
   
