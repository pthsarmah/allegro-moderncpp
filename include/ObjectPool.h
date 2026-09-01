#pragma once

#include "Entity.h"
#include <concepts>
#include <memory>
#include <queue>
#include <typeinfo>

// need this cuz SubPool<T> and SubPool<G> where T != G are also different types
class ISubPool {
public:
	virtual ~ISubPool() = default;
};

// sub pool of entities (ONLY renderable stuff)
template<typename T>
requires std::derived_from<T, Entity>
class SubPool : public ISubPool {
private:
	std::vector<T> objects;
public:
	std::vector<T>& getObjects() {
		return objects;
	}
	explicit SubPool(int count) {
		objects.reserve(count);
	}
};

template<typename T>
struct PoolConfig
{
    std::size_t count;
};

template<typename Base>
class ObjectPool {
private:
	std::vector<std::unique_ptr<ISubPool>> pools;
	
	template<typename T>
	requires std::derived_from<T, Base>
	void addPool(PoolConfig<T> config) {
		pools.push_back(std::make_unique<SubPool<T>>(config.count));
	}
public:
	template<typename... Ts>
	requires (std::derived_from<Ts, Base> && ...)
	ObjectPool(PoolConfig<Ts>... configs) {
		(addPool(configs), ...);
	}
};
