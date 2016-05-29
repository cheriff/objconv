#include <fstream>
#include <iostream>

#include "obj.h"
#include "util.h"

#include "VertexCache.h"

using std::cout;
using std::endl;


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
            case 'u':
                if (line.find("usemtl") == 0)
                    SetMaterial(line.substr(7));
                else
                    throw StackException("Unexpected 'u' line (" + line + ")");
                break;
            default:
                throw StackException("Unexpected line (" + line + ")");
        }
    }

    VertexCache vc;
    for (auto &g :groups) {
        g.base_idx = vc.count();
        cout << "Group: " << g.name << " has :" << g.base_idx <<endl;
        for (auto &f : g.faces) {
            vc.feed(f);
            g.count++;
        }
    }
}


static inline bool
is_num(char c) { return isdigit(c) || (c=='-'); }

static std::tuple<int3, char*> read_group(char *str) {
    int v0, n0, c0;
    v0=n0=c0 = 0;

    v0 = strtol(str, &str, 10);
    if ((*str++) == '/') {
        if (is_num(*str)) {
            c0 = strtol(str, &str, 10);
        }

        if ((*str++) == '/') {
            if (is_num(*str)) {
                n0 = strtol(str, &str, 10);
            }
        }
    }
    return std::tuple<int3, char*>(int3(v0, n0, c0), str);
}

void ObjFile::AddFace(const std::string &line)
{

    char* str = (char*)line.c_str();

    int3 v1, v2, v3;
    std::tie(v1, str) = read_group(str);
    std::tie(v2, str) = read_group(str);
    std::tie(v3, str) = read_group(str);

    while (std::get<0>(v3) != 0) {
        groups.back().AddFace(v1, v2, v3);

        v2 = v3;
        std::tie(v3, str) = read_group(str);
    }
}

void ObjFile::AddVertex(const std::string &line)
{
    char* end = (char*)line.c_str();
    float x = strtof( end, &end );
    float y = strtof( end, &end );
    float z = strtof( end, &end );
    positions.push_back(triple(x,y,z));
}

void ObjFile::AddNormal(const std::string &line)
{
    char* end = (char*)line.c_str();
    float x = strtof( end, &end );
    float y = strtof( end, &end );
    float z = strtof( end, &end );
    normals.push_back(triple(x,y,z));
}

void ObjFile::AddTexcoord(const std::string &line)
{
    char* end = (char*)line.c_str();
    float s = strtof( end, &end );
    float t = strtof( end, &end );
    coords.push_back(pair(s,t));
}

