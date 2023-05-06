/*
LibBinaryStream, Copyright (c) 2015 - 2023 Realsphere Entertainment

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

2. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include <assert.h>
#include <fstream>

class BinaryWriter {
public:
	void WriteInt(int value) {
		str->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	void WriteFloat(float value) {
		str->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	void WriteLong(long value) {
		str->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	void WriteShort(short value) {
		str->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	void WriteChar(char value) {
		str->write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	template<typename T>
	void Write(const T& data) {
		str->write(reinterpret_cast<const char*>(&data), sizeof(T));
	}

	void WriteString(const char* value) {
		WriteInt(strlen(value));
		for (size_t i = 0; i < strlen(value); i++)
			WriteChar(value[i]);
	}

	BinaryWriter(const char* filename) {
		str = new std::ofstream(filename, std::ios::binary);
	}

	void Close() {
		str->close();
		delete str;
	}

	std::ofstream* GetFileStream() {
		return str;
	}

private:
	std::ofstream* str;
};

class BinaryReader {
public:
	int ReadInt() {
		int value;
		char buffer[sizeof(value)];
		str->read(buffer, sizeof(value));
		std::memcpy(&value, buffer, sizeof(value));
		return value;
	}

	short ReadShort() {
		short value;
		char buffer[sizeof(value)];
		str->read(buffer, sizeof(value));
		std::memcpy(&value, buffer, sizeof(value));
		return value;
	}

	float ReadFloat() {
		float value;
		char buffer[sizeof(value)];
		str->read(buffer, sizeof(value));
		std::memcpy(&value, buffer, sizeof(value));
		return value;
	}

	long ReadLong() {
		long value;
		char buffer[sizeof(value)];
		str->read(buffer, sizeof(value));
		std::memcpy(&value, buffer, sizeof(value));
		return value;
	}

	template<typename T>
	T Read() {
		T value;
		char buffer[sizeof(T)];
		str->read(buffer, sizeof(T));
		std::memcpy(&value, buffer, sizeof(T));
		return value;
	}

	char ReadChar() {
		char buffer[1];
		str->read(buffer, 1);
		return buffer[0];
	}

	const char* ReadString() {
		int size = ReadInt();
		char* buffer = new char[size];
		for (size_t i = 0; i < size; i++)
			buffer[i] = ReadChar();
		return buffer;
	}

	BinaryReader(const char* filename) {
		str = new std::ifstream(filename, std::ios::binary);
	}

	void Close() {
		str->close();
		delete str;
	}

	std::ifstream* GetFileStream() {
		return str;
	}
private:
	std::ifstream* str;
};
