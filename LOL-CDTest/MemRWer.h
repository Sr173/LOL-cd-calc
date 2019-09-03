#pragma once
#include "initializer_list"
#include "string"
#include "vector"
#include "mutex"
#include <windows.h>

using uint = unsigned int;

class MemRWer
{
public:
	MemRWer(HANDLE h);
	~MemRWer();
	void readData(LPVOID lpAddress, int lenth, byte* buffer);
	std::wstring readWstring(uint addr);
	std::string readString(uint addr);
	void writeWstring(uint addr, std::wstring str);
	int decryption(uint addr);
	void writeData(LPVOID lpAddress, int lenth, byte * buffer);
	void runRemoteThread(std::vector<byte> opcode);
	template<class T>
	T read(uint lpBaseAddress) {
		T buffer;
		readData((LPVOID)lpBaseAddress, sizeof(T), (byte*)&buffer);
		return buffer;
	}

	template<class T>
	T read(uint lpBaseAddress, std::initializer_list<uint> offset) {
		uint result;
		result = read<uint>(lpBaseAddress);
		for (auto i = 0; i < offset.size() - 1; i++) {
			result = read<uint>(result + offset.begin()[i]);
		}
		return read<T>((uint)result + (uint)offset.end()[-1]);
	}

	template<class T>
	void write(uint lpBaseAddress, T data) {
		writeData((LPVOID)lpBaseAddress, sizeof(T), (byte*)&data);
	}

	template<class T>
	T write(uint lpBaseAddress, std::initializer_list<uint> offset, T data) {
		int result;
		result = read<uint>(lpBaseAddress);
		for (int i = 0; i < offset.size() - 1; i++) {
			result = read<uint>(result + offset.begin()[i]);
		}
		return write<T>((uint)result + (uint)offset.end()[-1], data);
	}

private:
	HANDLE hProcess;
};

