//
// Created by nicoc on 14.05.2024.
//

#include <vector>

template <typename T>
std::vector<T> collapse(const std::vector<std::vector<T>> & vec) {
    std::vector<T> result;
    for (const auto & v : vec)
        result.insert(result.end(), v.begin(), v.end());
    return result;
}

template <typename T>
std::vector<std::vector<T>> rebuild(const std::vector<T>& flatVector, size_t chunkSize) {
    std::vector<std::vector<T>> result;
    size_t numChunks = flatVector.size() / chunkSize;

    for (size_t i = 0; i < numChunks; ++i) {
        std::vector<T> chunk;
        for (size_t j = 0; j < chunkSize; ++j) {
            chunk.push_back(flatVector[i * chunkSize + j]);
        }
        result.push_back(chunk);
    }

    return result;
}