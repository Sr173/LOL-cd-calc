#include "MemRWer.h"


MemRWer::MemRWer(HANDLE h) : hProcess(h)
{

}

MemRWer::~MemRWer()
{

}

void MemRWer::readData(LPVOID lpAddress, int lenth, byte * buffer)
{
	ReadProcessMemory(hProcess, lpAddress, buffer, lenth, 0);
}

void MemRWer::writeData(LPVOID lpAddress, int lenth, byte* buffer) {

}

void MemRWer::runRemoteThread(std::vector<byte> opcode)
{

}


std::wstring MemRWer::readWstring(uint addr) {
	WCHAR buffer[200];
	readData((LPVOID)addr, sizeof(WCHAR) * 200, (byte*)buffer);
	return buffer;
}

std::string MemRWer::readString(uint addr)
{
	CHAR buffer[200];
	readData((LPVOID)addr, sizeof(CHAR) * 200, (byte*)buffer);
	return buffer;
}

void MemRWer::writeWstring(uint addr, std::wstring str)
{
	writeData((LPVOID)addr, str.size() * 2 + 2, (byte*)str.c_str());
}

int MemRWer::decryption(uint addr) {
	return 0;
}