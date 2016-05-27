#ifndef __OBJ_H__
#define __OBJ_H__

#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> int3;

struct Face {
    Face(int3 v1, int3 v2, int3 v3): indices{v1,v2,v3}
    {
    }

    int3 indices[3];
};

struct Group {
    Group(const std::string &new_name) : name{new_name}
    {}

    void AddFace(int3 v1, int3 v2, int3 v3) {
        faces.push_back(Face(v1,v2,v3));
    }

    const std::string name;
    std::vector<Face> faces;
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

    void AddFace(const std::string &line);
    void AddVertex(const std::string &line);
    void AddNormal(const std::string &line);
    void AddTexcoord(const std::string &line);


    public:
    std::vector<std::unique_ptr<Group>> groups;
    std::vector<triple> positions;
    std::vector<triple> normals;
    std::vector<pair> coords;
};

#endif // __OBJ_H__
