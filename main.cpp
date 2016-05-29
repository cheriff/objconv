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

    const char *filename = argc > 1? argv[1] : "gt86.obja";
    ifstream fin(filename, ios::in);
    if (!fin) {
        cout << "Unable to open " << filename  << ": " << strerror(errno) << endl;
        return -1;
    }

    {  Timer timer("Objfile load time");
       auto obj = ObjFile(fin);

       cout << "Vertices : " << obj.positions.size() << std::endl;
       cout << "Normals  : " << obj.normals.size() << std::endl;
       cout << "TexCoords: " << obj.coords.size() << std::endl;
       cout << endl;

       for(auto &g: obj.groups) {
           std::cout << "Group: " << g.name << std:: endl;
           std::cout << "       Faces:" << g.faces.size() << std::endl;
           std::cout << "       idx_Base :  " << g.base_idx <<std::endl;
           std::cout << "       idx_Count:  " << g.count <<std::endl;
       }
    }

    return 0;
}

