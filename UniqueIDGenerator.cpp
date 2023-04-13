// UniqueIDGenerator.cpp
#include "UniqueIDGenerator.h"

UniqueIDGenerator::UniqueIDGenerator() : m_currentID(1) {}

uint32_t UniqueIDGenerator::GenerateUniqueID(const std::string& name)
{
	auto it = m_nameToID.find(name);
	if (it != m_nameToID.end())
	{
		return it->second;
	}
	uint32_t newID = m_currentID++;
	m_nameToID[name] = newID;
	return newID;
}