// LOL-CDTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MemRWer.h"

MemRWer* gMrw;

char skill_table[] = { 'Q','W','E','R','D','F' };

void mem_thread() {
	for (;;) {
		auto end = gMrw->read<uint>(0x01AB8990);
		for (auto i = gMrw->read<uint>(0x01AB898C); i < end; i += 4) {
			int obj = gMrw->read<uint>(i);
			if (gMrw->read<uint>(obj + 0x44) != 100 && gMrw->read<uint>(obj + 0x70) == 0x18) {
				for (int i = 0; i < 6; i++) {
					if (gMrw->read<float>(obj + 0x1FBC, { 0x438,uint(0x508 + i * 4),0x28 }) - gMrw->read<float>(0x33534D8) > 0) {
						std::cout << u8"敌方" << "[" << std::hex << gMrw->readString(gMrw->read<uint>(obj + 0xBC))
							<< "]" << u8"技能" << skill_table[i] << "cd:" << std::dec <<
							gMrw->read<float>(obj + 0x1FBC, { 0x438,uint(0x508 + i * 4),0x28 }) - gMrw->read<float>(0x33534D8)
							<< std::endl;
					}
				}
			}
		}
		
		Sleep(1000);
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::cout << u8"麦林炮手" << std::endl;
	auto hwnd = FindWindow(L"RiotWindowClass", L"League of Legends (TM) Client");
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	gMrw = new MemRWer(hProcess);

	std::thread(mem_thread).detach();
	system("pause");
}
