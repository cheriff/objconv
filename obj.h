#ifndef __OBJ_H__
#define __OBJ_H__

#include <vector>
#include <tuple>

struct Group {
    Group(const std::string &new_name) : name{new_name}
    {        }

    const std::string name;
};

typedef std::tuple<float, float, float> triple;
typedef std::tuple<float, float> pair;

std::ostream &operator<<(std::ostream &os, triple const &m);
std::ostream &operator<<(std::ostream &os, pair const &m);


struct ObjFile {
    ObjFile(std::ifstream &fin);

    private:
    void AddGroup(const std::string &name)
    {
        std::unique_ptr<Group> g(new Group(name));
        groups.push_back(move(g));
    }

    void AddFace(const std::string &name)
    { if(0) std::cout << "Face: " << name << std::endl; }

    void AddVertex(const std::string &name)
    {
        char* end = (char*)name.c_str();
        float x = strtof( end, &end );
        float y = strtof( end, &end );
        float z = strtof( end, &end );
        positions.push_back(triple(x,y,z));
    }


    public:
    std::vector<std::unique_ptr<Group>> groups;
    std::vector<triple> positions;
    std::vector<triple> normals;
    std::vector<pair> coords;
};

#endif // __OBJ_H__
