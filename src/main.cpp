# include "Cell.h"
# include "Circuit.h"
using namespace std;


int main(int argc, char *argv[]) {
    string path = "../benchmarks";
    string testFile = argv[1] + string(".txt");

    cout << "Start doing placement on " << testFile << endl;

    Circuit circuit;
    circuit.loadCircuit(path + "/" + testFile);

    circuit.branchClustering();

    do {
        cout << '\n' << "Press a key to continue...";
    } while (cin.get() != '\n');
    
    return 0;
}