#ifndef TOPOLOGY_HPP
#define TOPOLOGY_HPP

#include <vector>
#include <cmath>

// Terrain grid
const int gridSizeX = 100;
const int gridSizeZ = 100;
const float spacing = 1.0f;

// Generate terrain heights (sine wave pattern)
inline std::vector<std::vector<float>> GenerateHeightMap() {
    std::vector<std::vector<float>> heightMap(gridSizeZ, std::vector<float>(gridSizeX));
    for (int z = 0; z < gridSizeZ; z++) {
        for (int x = 0; x < gridSizeX; x++) {
            heightMap[z][x] = 2.0f * sinf(x * 0.03f) * cosf(z * 0.03f);
        }
    }
    return heightMap;
}

#endif // TOPOLOGY_HPP
