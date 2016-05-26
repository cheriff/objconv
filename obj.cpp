#include <fstream>
#include <iostream>

#include "obj.h"

using std::cout;



ObjFile::ObjFile(std::ifstream &fin)
{


#define SKIP_WS(_f)  _f>>std::ws
    for (std::string line; SKIP_WS(fin), getline(fin, line); ) {
        switch(line.at(0)) {
            case '#':
            case 's':
                continue;
            case 'g':
                AddGroup(line.substr(2));
                continue;
            case 'v':
                AddVertex(line.substr(2));
                continue;
            case 'f':
                AddFace(line.substr(2));
                continue;
            default:
                cout << "WTF: " << line << std::endl;
        }

        printf("Base: '%c', == %s\n", line[0], line.c_str());
    }
}

