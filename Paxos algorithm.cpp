#include <iostream>
using namespace std;

int main() {
    int proposalNo, accepted = 0;
    string value;

    cout << "Enter Proposal Number: ";
    cin >> proposalNo;

    cout << "Enter Value: ";
    cin >> value;

    // Three acceptors
    int highestProposal[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
        if (proposalNo > highestProposal[i]) {
            highestProposal[i] = proposalNo;
            accepted++;
            cout << "Acceptor " << i + 1 << " accepted proposal.\n";
        } else {
            cout << "Acceptor " << i + 1 << " rejected proposal.\n";
        }
    }

    if (accepted >= 2)
        cout << "\nConsensus Achieved! Value = " << value << endl;
    else
        cout << "\nConsensus Failed!" << endl;

    return 0;
}
