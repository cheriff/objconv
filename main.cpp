#include <iostream>
#include <fstream>
#include <iomanip>


#include "obj.h"
#include "timer.h"
#include "util.h"

using namespace std;

int
main(int argc, char *argv[])
{
    Timer timer("Application Runtime");

    const char *filename = argc > 1? argv[1] : "gt86.obja";
    ifstream fin(filename, ios::in);
    if (!fin) {
        cout << "Unable to open " << filename  << ": " << strerror(errno) << endl;
        return -1;
    }

    auto obj = ObjFile(fin);

    return 0;
}

