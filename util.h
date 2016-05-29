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
typedef std::tuple<int, int, int> int3;
typedef std::tuple<float, float, float> triple;
typedef std::tuple<float, float> pair;

std::ostream &operator<<(std::ostream &os, triple const &m);
std::ostream &operator<<(std::ostream &os, pair const &m);

