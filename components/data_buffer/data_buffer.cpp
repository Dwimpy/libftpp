#include <iomanip>
#include "data_buffer.hpp"

size_t DataBuffer::size() const
{
	return (_data.size());
}

bool DataBuffer::empty() const
{
	return (_data.empty());
}

void DataBuffer::clear()
{
	_data.clear();
}


std::ostream &operator<<(std::ostream &os, const DataBuffer &buffer)
{
	buffer.toStream(os);
	return (os);
}

void DataBuffer::toStream(std::ostream &os) const
{
	int max_line_width = 16 * 2 + 15;
	int curr_width = 0;
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*it);
		curr_width += 3;
		if (std::next(it) == _data.end()) {
			os << "\n";
			return;
		}
		else if (curr_width >= max_line_width) {
			curr_width = 0;
			os << '\n';
		} else {
			os << ' ';
		}
	}
	os << std::dec;
}
