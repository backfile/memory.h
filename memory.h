#pragma once

#include <Windows.h>
#include <Tlhelp32.h>

using namespace std;

// Clase que se va a encargar de manejar las funciones relacionadas a un proceso.

class Memory{
private:
	uintptr_t processID = 2;
	HANDLE hprocess = nullptr;
public:
	Memory(char* nombre) {
		PROCESSENTRY32 process;
		HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);


		// Tamaño de la estructura antes de ser utilizada.
		process.dwSize = sizeof(PROCESSENTRY32);

		if (::Process32First(snapshot, &process)) {
			if (!strcmp(nombre, process.szExeFile)) {
				hprocess = ::OpenProcess(PROCESS_ALL_ACCESS, true, process.th32ProcessID);
				processID = process.th32ProcessID;
			}
			else {
				while (::Process32Next(snapshot, &process)) {
					if (!strcmp(nombre, process.szExeFile)) {
						hprocess = ::OpenProcess(PROCESS_ALL_ACCESS, true, process.th32ProcessID);
						processID = process.th32ProcessID;
						break;
					}
				}
			}
			CloseHandle(snapshot);
		}

	}
	~Memory() {
		CloseHandle(hprocess);
	}

	template <typename T>
	void Write(uintptr_t address, T& data) {
		::WriteProcessMemory(hprocess, reinterpret_cast<const void*>(address), &data, sizeof(data), 0);
	}

	template <typename T>
	void Read(uintptr_t address, T& data) {
		::ReadProcessMemory(hprocess, reinterpret_cast<const void*>(address), &data, sizeof(data), 0);
	}

	uintptr_t GetModuleAddress(char* nombre) {
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(MODULEENTRY32);
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
		if(Module32First(snapshot, &entry)) {
			if (!strcmp(nombre, entry.szModule)) {
				CloseHandle(snapshot);
				return  reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			}
			else {
				while (Module32Next(snapshot, &entry)) {
					if (!strcmp(nombre, entry.szModule)) {
						CloseHandle(snapshot);
						return  reinterpret_cast<uintptr_t>(entry.modBaseAddr);
					}
				}
			}
		}

	}

	uintptr_t GetProcessID() {
		return processID;
	}

};