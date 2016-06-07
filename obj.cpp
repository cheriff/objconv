#include <fstream>
#include <iostream>

#include <assert.h>

#include "obj.h"
#include "util.h"


using std::cout;
using std::endl;


ObjFile::ObjFile(std::ifstream &fin, const std::string &name)
{
    this->name = name;

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
}


static inline bool
is_num(char c) { return isdigit(c) || (c=='-'); }

static std::tuple<int, int, int, char*> read_group(char *str) {
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
    return std::tuple<int, int, int, char*>(v0, c0, n0, str);
}

int
ObjFile::PushVertex(int pos_idx, int tc_idx, int norm_idx)
{
    printf("Vertex: %d %d %d\n", pos_idx, tc_idx, norm_idx);
    assert(pos_idx != 0);

    if (pos_idx < 0)
        pos_idx = positions.size() + pos_idx;
    else
        pos_idx -= 1;

    Vertex v(positions.at(pos_idx));

    cout << "POS  : " << positions.at(pos_idx) << std::endl;

    if (tc_idx != 0) {
        if (tc_idx < 0)
            tc_idx = coords.size() + tc_idx;
        else
            tc_idx -= 1;

        v.SetTex(coords.at(tc_idx));
        cout << "TEX  : " << coords.at(tc_idx) << std::endl;
    }

    if (norm_idx != 0) {
        if (norm_idx < 0)
            norm_idx = normals.size() + norm_idx;
        else
            norm_idx -= 1;

        v.SetNormal(normals.at(norm_idx));
        cout << "NORM : " << normals.at(norm_idx) << std::endl;
    }
    cout << std::endl;
    
    groups.back().count++;
    return vc.feed(v);
}

void ObjFile::AddFace(const std::string &line)
{
    char* str = (char*)line.c_str();

    int pos, tc, norm;
    int first, last;

    std::tie(pos, tc, norm, str) = read_group(str);
    first = PushVertex(pos, tc, norm);

    std::tie(pos, tc, norm, str) = read_group(str);
    last = PushVertex(pos, tc, norm);

    std::tie(pos, tc, norm, str) = read_group(str);
    int current = PushVertex(pos, tc, norm);

    (void)first;
    (void)last;
    (void)current;



    do {
        std::tie(pos, tc, norm, str) = read_group(str);
        if (pos == 0) break;

        // todo: trianglulate faces with more points
        printf("TODO: BIGGER FACES\n");
    } while (pos != 0);
}

void ObjFile::AddVertex(const std::string &line)
{
    char* end = (char*)line.c_str();
    float x = strtof( end, &end );
    float y = strtof( end, &end );
    float z = strtof( end, &end );
    positions.push_back(float3(x,y,z));
}

void ObjFile::AddNormal(const std::string &line)
{
    char* end = (char*)line.c_str();
    float x = strtof( end, &end );
    float y = strtof( end, &end );
    float z = strtof( end, &end );
    normals.push_back(float3(x,y,z));
}

void ObjFile::AddTexcoord(const std::string &line)
{
    char* end = (char*)line.c_str();
    float s = strtof( end, &end );
    float t = strtof( end, &end );
    coords.push_back(float2(s,t));
}

void ObjFile::toASCII(std::ofstream &fout)
{
    int i = 0;
    for (auto p: vc.buffer) {
        fout << "Vertex: "<< ++i << std::endl;
        fout << "  p: "<< p.pos << std::endl;
        fout << "  t: "<< p.tc << std::endl;
        fout << "  n: "<< p.normal << std::endl;
    };


    fout << std::endl;
    fout << "Indices:" << std::endl;
    i=0;
    for (auto x: vc.indices) {
        i++;
        fout << "  V" << x;
        if (i & ((i%3)==0)) fout<<std::endl;
        else fout<<"\t";
    }
}

static inline void
do_write(std::ofstream &fp, std::string str, int len)
{
    str.resize(len, '\0');
    fp.write(str.c_str(), len);
}


template<typename T>
static inline void
do_write(std::ofstream &fp, T val)
{
    auto ptr = reinterpret_cast<const char *>(&val);
    fp.write(ptr, sizeof(val));
}

static inline void
do_write(std::ofstream &fp, float3 &t)
{
    do_write<float>(fp, t.x);
    do_write<float>(fp, t.y);
    do_write<float>(fp, t.z);
}

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A


void ObjFile::toBin(std::ofstream &fout)
{
    const uint32_t magic = 0x0B1EC701;
    const uint16_t major = 0x0001;
    const uint16_t minor = 0x0001;
    const uint16_t index_type = GL_UNSIGNED_INT;
    const uint16_t index_count = vc.indices.size();

//    const int floats_per_vert = 8; // pos(x,y,z) + norm(x,y,z) + tex(s,t) = 3 + 3 + 2 = 8
    const int floats_per_vert = 6; // pos(x,y,z) + norm(x,y,z) = 3 + 3 = 6
    const uint32_t buffsize = vc.buffer.size() * floats_per_vert * sizeof(float);


    const uint32_t num_attrs = 2;
    const uint32_t num_groups = groups.size();

    // header
    do_write<uint32_t>(fout, magic);
    do_write<uint16_t>(fout, major);
    do_write<uint16_t>(fout, minor);
    do_write<uint16_t>(fout, index_type);
    do_write<uint16_t>(fout, index_count);
    do_write<uint32_t>(fout, buffsize);
    do_write(fout, name, 16);
    do_write<uint32_t>(fout, num_attrs);
    do_write<uint32_t>(fout, num_groups);

    //const uint32_t float1_size = 1 * sizeof(float);
    const uint32_t float3_size = 3 * sizeof(float);

    // Attr1: Position
    do_write(fout, "position", 16);
    do_write<uint32_t>(fout, float3_size); // stride
    do_write<uint32_t>(fout, 0); // offset
    do_write<uint32_t>(fout, GL_FLOAT); // elem_type
    do_write<uint32_t>(fout, 3); // elem_count

    // Attr2: Normal
    do_write(fout, "colour", 16);
    do_write<uint32_t>(fout, float3_size); // stride
    do_write<uint32_t>(fout, float3_size); // offset
    do_write<uint32_t>(fout, GL_FLOAT); // elem_type
    do_write<uint32_t>(fout, 3); // elem_count

    // Groups
    for(auto g: groups) {
        do_write(fout, g.name, 16);
        do_write<uint16_t>(fout, g.base_idx);
        do_write<uint16_t>(fout, g.count);
    }

    for (auto i: vc.indices) {
        if (index_type==GL_UNSIGNED_INT)
            do_write<uint32_t>(fout, i);
        else if (index_type==GL_UNSIGNED_SHORT)
            do_write<uint16_t>(fout, i);
        else if (index_type==GL_UNSIGNED_BYTE)
            do_write<uint8_t>(fout, i);
    }

    for (auto v: vc.buffer) {
        cout << "POS " << v.pos << endl;
        cout << "COl " << v.normal << endl;
        do_write(fout, v.pos);
        do_write(fout, v.normal);
        // do_write(fout, v.tc);
    }
}

