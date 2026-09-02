#pragma once

#include "Entity.h"
#include "Renderer.h"
#include <concepts>
#include <memory>
#include <queue>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

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
	// heap-owned so addresses stay stable (Renderer keeps raw pointers)
	std::vector<std::unique_ptr<T>> free;
	std::vector<std::unique_ptr<T>> active;
public:
	std::vector<std::unique_ptr<T>>& getActive() {
		return active;
	}
	explicit SubPool(int count) {
		free.reserve(count);
		active.reserve(count);
		for (int i=0; i<count; i++) {
			free.push_back(std::make_unique<T>());
		}
	}
	T& instantiate() {
		if (free.empty()) throw std::runtime_error("Pool exhausted");
		active.push_back(std::move(free.back()));
		free.pop_back();
		return *active.back();
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
	std::unordered_map<std::type_index, std::unique_ptr<ISubPool>> pools;
	
	template<typename T>
	requires std::derived_from<T, Base>
	void addPool(PoolConfig<T> config) {
		pools.emplace(typeid(T), std::make_unique<SubPool<T>>(config.count));
	}
public:
	template<typename... Ts>
	requires (std::derived_from<Ts, Base> && ...)
	ObjectPool(PoolConfig<Ts>... configs) {
		(addPool(std::move(configs)), ...);
	}
	
	template<typename T>
	requires std::derived_from<T, Base>
	T& instantiate(Renderer& rd) {
		//get the appropiate subpool
		auto it = pools.find(typeid(T));
		if (it == pools.end()) throw std::runtime_error("No pool for this type");

		auto* pool = static_cast<SubPool<T>*>(it->second.get());

		//instantiate an object from the subpool
		T& obj = pool->instantiate();

		//add to renderer
		rd.add(obj);

		return obj;
	}
};
