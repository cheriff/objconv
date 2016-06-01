#include <fstream>
#include <iostream>

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

    vc = std::unique_ptr<VertexCache>(new VertexCache); 
    for (auto &g :groups) {
        g.base_idx = vc->count();
        for (auto &f : g.faces) {
            vc->feed(f.vertices[0]);
            vc->feed(f.vertices[1]);
            vc->feed(f.vertices[2]);
            g.count+=3;
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

void ObjFile::ToASCII(std::ofstream &fout)
{
    int i = 0;
    for (auto p: vc->buffer) {
        fout << "Vertex: "<< ++i << std::endl;
        int p_idx = std::get<0>(p)-1;
        int t_idx = std::get<1>(p)-1;
        int n_idx = std::get<2>(p)-1;
        fout << "  p" << p_idx<<": "<< positions[p_idx] << std::endl;
        fout << "  t" << t_idx<<": "<< positions[t_idx] << std::endl;
        fout << "  n" << n_idx<<": "<< positions[n_idx] << std::endl;
    };


    fout << std::endl;
    fout << "Indices:" << std::endl;
    i=0;
    for (auto x: vc->indices) {
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
do_write(std::ofstream &fp, triple &t)
{
    do_write<float>(fp, std::get<0>(t));
    do_write<float>(fp, std::get<1>(t));
    do_write<float>(fp, std::get<2>(t));
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


void ObjFile::ToBin(std::ofstream &fout)
{
    const uint32_t magic = 0x0B1EC701;
    const uint16_t major = 0x0001;
    const uint16_t minor = 0x0001;
    const uint16_t index_type = GL_UNSIGNED_INT;
    const uint16_t index_count = vc->indices.size();
    const uint32_t buffsize = vc->buffer.size() * 3 * sizeof(float);

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

    const uint32_t float1_size = 1 * sizeof(float);
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
    do_write<uint32_t>(fout, float1_size); // offset
    do_write<uint32_t>(fout, GL_FLOAT); // elem_type
    do_write<uint32_t>(fout, 3); // elem_count

    // Groups
    for(auto g: groups) {
        do_write(fout, g.name, 16);
        do_write<uint16_t>(fout, g.base_idx);
        do_write<uint16_t>(fout, g.count);
    }

    for (auto i: vc->indices) {
        if (index_type==GL_UNSIGNED_INT)
            do_write<uint32_t>(fout, i);
        else if (index_type==GL_UNSIGNED_SHORT)
            do_write<uint16_t>(fout, i);
        else if (index_type==GL_UNSIGNED_BYTE)
            do_write<uint8_t>(fout, i);
    }

    for (auto v: vc->buffer) {
        const unsigned int p_idx = std::get<0>(v)-1;
        const unsigned int t_idx = std::get<1>(v)-1;
        const unsigned int n_idx = std::get<2>(v)-1;
        do_write(fout, positions[p_idx]);
        do_write(fout, normals[n_idx]);
        do_write(fout, coords[t_idx]);

    }
}

