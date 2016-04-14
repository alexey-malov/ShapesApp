#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class CResourceHolder
{
public:
	void Load(Identifier id, const std::string & fileName)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(fileName))
		{
			throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
		}

		InsertResource(id, std::move(resource));
	}

	template< typename Parameter> 
	void Load(Identifier id, const std::string & fileName, const Parameter & parameter)
	{
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(fileName, parameter))
		{
			throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
		}

		InsertResource(id, std::move(resource));
	}

	Resource & Get(Identifier id)
	{
		auto found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());

		return *found->second;
	}

	const Resource & Get(Identifier id) const
	{
		auto found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());

		return *found->second;
	}

private:
	void InsertResource(Identifier id, std::unique_ptr<Resource> resource)
	{
		auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};
