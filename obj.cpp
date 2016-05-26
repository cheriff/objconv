#include <fstream>
#include <iostream>

#include "obj.h"
#include "util.h"

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
                switch(line.at(1)) {
                    case ' ':
                    case '\t':
                        AddVertex(line.substr(2));
                        break;
                    case 'n':
                        AddNormal(line.substr(3));
                        break;
                    case 't':
                        AddTexcoord(line.substr(3));
                        break;
                    default:
                        throw StackException("Unexpected 'V' line (" + line + ")");
                }
                continue;
            case 'f':
                AddFace(line.substr(2));
                continue;
            default:
                throw StackException("Unexpected line (" + line + ")");
        }
    }
}

