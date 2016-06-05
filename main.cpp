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
    if (argc < 3) {
        printf("Usage: %s <infile> <outfile>\n", argv[0]);
        return -1;
    }

    const char *input_filename = argv[1];
    ifstream fin(input_filename, ios::in);
    if (!fin) throw StackException(std::string("Unable to open :") + input_filename + std::string(strerror(errno)));

    const char *output_filename = argv[2];
    ofstream fout(output_filename, ios::out);
    if (!fout) throw StackException(std::string("Unable to open :") + output_filename + std::string(strerror(errno)));

    Timer timer("Objfile load time");
    ObjFile(fin, input_filename).toBin(fout);

    return 0;
}

