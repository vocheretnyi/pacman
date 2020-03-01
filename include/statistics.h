#pragma once

#include <ostream>
#include <cassert>
#include <algorithm>

class Statistics {
public:
    Statistics(std::string _name)
            : name(_name), maxMemoryUsageB(0), curMemoryUsageB(0), pathLength(0), cntIterations(0) {}

    void addMemoryUsage(uint64_t cntMemory) {
        curMemoryUsageB += cntMemory;
        maxMemoryUsageB = std::max(maxMemoryUsageB, curMemoryUsageB);
    }

    void freeMemoryUsage(uint64_t cntMemory) {
        assert(curMemoryUsageB >= cntMemory);
        curMemoryUsageB -= cntMemory;
    }

    void setPathLength(int _pathLength) {
        pathLength = _pathLength;
    }

    void increaseIterations() {
        cntIterations++;
    }

    void increaseIterations(int iterations) {
        cntIterations += iterations;
    }

    friend std::ostream& operator<<(std::ostream& out, const Statistics& statistics) {
        out << statistics.name << " statistics\n";
        out << "cntIterations = " << statistics.cntIterations << "\n";
        out << "maxMemoryUsageB = " << statistics.maxMemoryUsageB << "\n";
        out << "pathLength = " << statistics.pathLength << "\n";
        return out;
    }

private:
    std::string name;
    uint64_t maxMemoryUsageB;
    uint64_t curMemoryUsageB;
    int pathLength;
    int cntIterations;
};