#include "../include.hpp"
#define  WORD_SIZE 2
#define DWORD_SIZE 4
#define QWORD_SIZE 8

namespace Bounce::Serial
{
	// Converts up to the first 2 bytes of a string to a single 2 bytes unsigned integer.
	inline static uint16_t WordToInt(::std::string s)
	{
		if (!s.size())
			return 0;
		unsigned char* i = (unsigned char*)s.c_str();
		if (s.size() == 1)
			return i[0];
		return i[0] << 8 | i[1];
	}

	// Converts up to the first 4 bytes of a string to a single 4 bytes unsigned integer.
	inline static uint32_t DwordToInt(::std::string s)
	{
		unsigned char* i = (unsigned char*)s.c_str();
		if (s.size() < 3)
			return WordToInt(s);
		if (s.size() == 3)
			return i[0] << 16 | i[1] << 8 | i[2];
		return i[0] << 24 | i[1] << 16 | i[2] << 8 | i[3];
	}

	// Converts up to the first 8 bytes of a string to a single 8 bytes unsigned integer.
	inline static uint64_t QwordToInt(::std::string s)
	{
		unsigned char* si = (unsigned char*)s.c_str();
		uint8_t _size = s.size() < 8 ? s.size() : 8;
		uint64_t _val = 0;
		// cap the max value to be parsed to 8 bytes
		for (uint8_t i = 0; i < _size && i < 8; ++i)
			_val += (uint64_t)si[_size - i - 1] << 8LLU * i;
		return _val;
	}

	// Converts an int into a buffer of bytes representing the same value.
	inline static ::std::string IntToXWord(uint64_t n, uint8_t size)
	{
		::std::string s;
		for (uint8_t i = 0; i < size; ++i)
			s = (char)((n & (0xFFLLU << i * 8)) >> i * 8) + s;
		return s;
	}

	struct Table
	{
		// table's size
		uint64_t size;
		// header's size (where the indexes are)
		uint32_t header_size;
		uint32_t* indexes;
		char* data_buffer;
	};

	inline static uint32_t TableCountElements(Table t)
	{
		return t.header_size / sizeof(DWORD_SIZE);
	}

	static void DisplayTable(Table t)
	{
		::std::string indexes;
		for (size_t i = 0; i < t.header_size / sizeof(DWORD_SIZE); ++i)
			indexes += ::std::to_string(t.indexes[i]) + " ";
		::std::cout << "Table infos: \nSize:" << t.size
			<< "\nHeader size: " << t.header_size << "\nList of indexes: [ " << indexes
			<< "]\nData buffer:\n" << t.data_buffer << ::std::endl;
	}

	static Table ParseTable(::std::string s)
	{
		Table t;
		// reading index (in bytes)
		size_t index = 0;
		t.size = QwordToInt(s.substr(index , QWORD_SIZE));
		t.header_size = DwordToInt(s.substr(index += 8, DWORD_SIZE));
		index += 4;
		t.indexes = (uint32_t*)malloc(t.header_size);
		size_t data_begin = 12 + t.header_size;
		if (!t.indexes)
			return t;
		for (size_t i = 0; i < t.header_size / sizeof(uint32_t); ++i)
		{
			t.indexes[i] = DwordToInt(s.substr(index, DWORD_SIZE));
			index += 4;
		}
		t.data_buffer = (char*)malloc(t.size - t.header_size);
		memcpy((void*)t.data_buffer, s.c_str() + data_begin, t.size - t.header_size);
		return t;
	}

	// Creates a table containing each of the given (/strings) elements.
	// Each string should already be serialized, as the table is only a way of serializing an array.
	static ::std::string CreateTable(::std::vector<::std::string> elements)
	{
		uint64_t 
			size = 0,
			_header_size = elements.size() * DWORD_SIZE + QWORD_SIZE + DWORD_SIZE;
		::std::string table =
			  Serial::IntToXWord(_header_size - QWORD_SIZE - DWORD_SIZE, 4)	// table header size
			;
		::std::string data;
		for (size_t i = 0; i < elements.size(); ++i)
		{
			size += DWORD_SIZE; // each pointer adds some length to the table
			table += Serial::IntToXWord(data.size(), DWORD_SIZE);
			data += elements[i];
		}
		size += QWORD_SIZE + DWORD_SIZE // fixed header size
			+ data.size();
		// adding total size
		table = Serial::IntToXWord(size, 8) + table + data;
		return table;
	}

	// Creates a table containing each of the given (/strings) elements.
	// Each string should already be serialized, as the table is only a way of serializing an array.
	static ::std::string CreateTable(void* elements, size_t n_elements)
	{
		uint64_t 
			size = 0,
			_header_size = n_elements * DWORD_SIZE + QWORD_SIZE + DWORD_SIZE;
		::std::string table =
			  Serial::IntToXWord(_header_size - QWORD_SIZE - DWORD_SIZE, 4)	// table header size
			;
		::std::string data;
		for (size_t i = 0; i < n_elements; ++i)
		{
			size += DWORD_SIZE; // each pointer adds some length to the table
			table += Serial::IntToXWord(data.size(), DWORD_SIZE);
			data += ((char*)elements)[i];
		}
		size += QWORD_SIZE + DWORD_SIZE // fixed header size
			+ data.size();
		// adding total size
		table = Serial::IntToXWord(size, 8) + table + data;
		return table;
	}

	// Returns an element from the data buffer.
	static ::std::string GetTableElement(Table t, uint32_t index)
	{
		if (index >= TableCountElements(t))
			return "Out of bounds index.";
		::std::string s = t.data_buffer + (t.indexes[index]);
		if(index == TableCountElements(t) - 1)
			return s.substr(0, t.size - t.header_size);
		else
			return s.substr(0, t.indexes[index + 1] - t.indexes[index]);
	}

	// Frees a table in memory.
	static void FreeTable(Table* t)
	{
		free(t->indexes);
		free(t->data_buffer);
		t->header_size = 0;
		t->size = 0;
	}

	// Serializes a string.
	inline static ::std::string CreateString(::std::string original)
	{
		return IntToXWord(original.size(), QWORD_SIZE) + original;
	}

	// Parses a serialized string.
	inline static ::std::string ParseString(::std::string buffer)
	{
		size_t _s_size = QwordToInt(buffer.substr(0, QWORD_SIZE));
		if (_s_size && _s_size <= buffer.size())
			return buffer.substr(QWORD_SIZE, _s_size);
		else
			return "Invalid given string.";
	}
}