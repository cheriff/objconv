#pragma once

#include <vector>

#include "util.h"
#include "Group.h"
#include "VertexCache.h"

struct ObjFile {
    ObjFile(std::ifstream &fin, const std::string &name = "NoName");
    void toASCII(std::ofstream &fout);
    void toBin(std::ofstream &fout);

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

    int PushVertex(int pos_idx, int tc_idx, int norm_idx);

    void AddFace(const std::string &line);
    void AddVertex(const std::string &line);
    void AddNormal(const std::string &line);
    void AddTexcoord(const std::string &line);

    std::string name;


    public:
    std::vector<Group> groups;
    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float2> coords;

    std::vector<int> indices;
    VertexCache vc;
};

