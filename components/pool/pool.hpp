#pragma once
#include <vector>
#include <memory>
#include <stdexcept>

template <typename TType>
class Pool {

  public:
	class Object {

	  public:

		Object(std::unique_ptr<TType> ptr, Pool *pool) : _ptr(std::move(ptr)), _pool(pool) {}
		~Object() {
			if (_ptr) {
				_pool->release(std::move(_ptr));
			}
		}

		TType *operator->() {
			return _ptr.get();
		}

		TType& operator*() {
			return *_ptr;
		}

		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

	  private:
		std::unique_ptr<TType> _ptr;
	  	Pool	*_pool;

	};

  Pool() = default;

	void resize(const size_t& numberOfObjectStored) {
		_pool.reserve(numberOfObjectStored);
		while (_pool.size() < numberOfObjectStored) {
			_pool.push_back(std::make_unique<TType>());
		}
	}


	template <typename... TArgs>
	Pool<TType>::Object acquire(TArgs&&... args) {
		if (_pool.empty()) {
			throw std::runtime_error("Pool was empty.");
		}

		std::unique_ptr<TType> obj = std::move(_pool.back());
		_pool.pop_back();

		new (obj.get()) TType(std::forward<TArgs>(args)...);
		return (Object(std::move(obj), this));
	}

  private:
	std::vector<std::unique_ptr<TType> > _pool;
  	void	release(std::unique_ptr<TType> ptr) {
		  _pool.push_back(std::move(ptr));
	  }
};