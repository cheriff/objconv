#pragma once

#include "util.h"

struct Vertex {
    Vertex(float3 pos): pos(pos), has_normal(false), has_tc(false) {}

    void SetNormal(float3 _normal)
    {
        normal = _normal;
        has_normal = true;
    }

    void SetTex(float2 _tc)
    {
        tc = _tc;
        has_tc = true;
    }

    bool operator==(const Vertex& other)
    {
        if (pos != other.pos) return false;

        if (has_normal != other.has_normal) return false;
        if (has_normal && (normal != other.normal)) return false;

        if (has_tc != other.has_tc) return false;
        if (has_tc && (tc != other.tc)) return false;

        return true;
    }

    float3 pos, normal;
    float2 tc;

    bool has_normal;
    bool has_tc;
};



