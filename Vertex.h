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

    const bool operator<(const Vertex& other) const {
        auto me = pos.x + pos.y*2 + pos.z*4;
        auto him = other.pos.x + other.pos.y*2 + other.pos.z*4;

        if (has_normal) {
            me += normal.x*8 + normal.y*16 + normal.z*32;
            him += other.normal.x*8 + other.normal.y*16 + other.normal.z*32;
        }

        if (has_tc) {
            me += tc.s*64 + tc.t*128;
            him += other.tc.s*64 + other.tc.t*128;
        }

        return me < him;
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



