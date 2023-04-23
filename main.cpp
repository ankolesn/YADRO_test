#include "Processing_Event.h"
using namespace std;


int main(int argc, char* argv[]) {
    ifstream file("file");
    if (!file.is_open()) {
        cout << "Error: cannot open input file " << argv[1] << endl;
        return 1;
    }

    Processing_Event p_e;

    try {
        p_e.parse_file(argv[1]);
    }
    catch (const string& error_message) {
        cout << error_message << endl;
        ::exit(0);
    }
    p_e.print();
    file.close();
}
