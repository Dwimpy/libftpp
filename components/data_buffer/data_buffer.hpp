#pragma once
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <ostream>

class DataBuffer {

  public:

	size_t	size() const;
	bool	empty() const;
	void	clear();

	friend std::ostream& operator<<(std::ostream& os, const DataBuffer& buffer);

	template<typename TType>
	DataBuffer& operator<<(const TType& p_object) {
		serialize(p_object);
		return *this;
	}

	template<typename TType>
	DataBuffer& operator>>(TType& p_object) {
		p_object = deserialize<TType>();
		return *this;
	}

  private:
	template <typename TType>
	void serialize(const TType& obj) {
		const auto* start_ptr = reinterpret_cast<const uint8_t *>(&obj);
		_data.insert(_data.end(), start_ptr, start_ptr + sizeof(TType));
	}

	template <typename TType>
	TType deserialize() {
		if (_data.empty()) {
			throw std::runtime_error("Not enough data to deserialize.");
		}

		TType obj;
		std::copy(_data.begin(), _data.begin() + sizeof(TType),
				  reinterpret_cast<uint8_t *>(&obj));
		_data.erase(_data.begin(), _data.begin() + sizeof(TType));
		return obj;
	}

	void	toStream(std::ostream& os) const;

	std::vector<uint8_t> _data;

};
