#pragma once

#define BT_BUF_SIZE 100
#include <execinfo.h>
#include <stdlib.h>

#include <iostream>


struct StackException {
    StackException(const std::string &errstr) {
        int nptrs = backtrace(buffer, BT_BUF_SIZE);
        strings = backtrace_symbols(buffer, nptrs);
        std::cout << "Exception: " << errstr << std::endl;
        for(int i=0; i<nptrs; i++) {
            std::cout << "\t" << strings[i] << std::endl;
        }
        exit(255);
    }
    private:
    void *buffer[BT_BUF_SIZE];
    char **strings;
};

#include <tuple>

struct float3 {
    float3() : x{0}, y{0}, z{0} {}
    float3(float x, float y, float z) : x{x}, y{y}, z{z} {}
    float x, y, z;
};

struct int3 {
    int3(int a, int b, int c) : a{a}, b{b}, c{c} {}
    int a, b, c;
};

struct float2 {
    float2() : s{0}, t{0} {}
    float2(float s, float t) : s{s}, t{t} {}
    float s, t;
};
std::ostream &operator<<(std::ostream &os, int3 const &m);
std::ostream &operator<<(std::ostream &os, float3 const &m);
std::ostream &operator<<(std::ostream &os, float2 const &m);

