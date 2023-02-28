//
// Created by ammar on 01/03/2023.
//

#ifndef TUCIL2_13521136_GETCPU_H
#define TUCIL2_13521136_GETCPU_H

#ifdef _WIN32
#include <intrin.h>
#endif

#ifdef linux
#include <fstream>
#endif

#include <string>


using namespace std;

string getProcessorInfo() {
    string result;
#ifdef _WIN32
    int CPUInfo[4] = {-1};
    unsigned nExIds, i = 0;
    char CPUBrandString[0x40];
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    for (i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(CPUInfo, i);
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    result = CPUBrandString;
#endif
#ifdef linux
    ifstream cpuinfo("/proc/cpuinfo");
    string line;
    while (getline(cpuinfo, line)) {
        if (line.find("model name") != string::npos) {
            result = line.substr(line.find(':') + 2);
            break;
        }
    }
    cpuinfo.close();
#endif
    return result;
}

#endif
