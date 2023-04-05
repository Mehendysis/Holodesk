// UniqueIDGenerator.h
#pragma once
#ifndef UNIQUE_ID_GENERATOR_H
#define UNIQUE_ID_GENERATOR_H

#include <cstdint>
#include <string>
#include <unordered_map>

class UniqueIDGenerator {
public:
    UniqueIDGenerator();
    uint32_t GenerateUniqueID(const std::string& name);

private:
    uint32_t m_currentID;
    std::unordered_map<std::string, uint32_t> m_nameToID;
};

#endif // UNIQUE_ID_GENERATOR_H