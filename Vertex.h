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

    float3 pos, normal;
    float2 tc;

    bool has_normal;
    bool has_tc;
};

