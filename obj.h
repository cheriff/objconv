#pragma once

#include <vector>

#include "util.h"
#include "Group.h"  

struct ObjFile {
    ObjFile(std::ifstream &fin);

    private:
    void AddGroup(const std::string &name)
    {
        groups.push_back(Group(name));
    }

    void SetMaterial(const std::string &line)
    {
        // TODO: Be more useful with Material
        //std::cout << "Material: '" << line << "'" << std::endl;
    }

    void AddFace(const std::string &line);
    void AddVertex(const std::string &line);
    void AddNormal(const std::string &line);
    void AddTexcoord(const std::string &line);


    public:
    std::vector<Group> groups;
    std::vector<triple> positions;
    std::vector<triple> normals;
    std::vector<pair> coords;

    std::vector<int> indices;
};

