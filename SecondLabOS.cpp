// SecondLabOS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>
#include <bitset>
#include "stdio.h"
#include <string>

using namespace std;



// Прототипы функций для работы

//Меню
int showMenu();

//Вывод информации о системе
void getSysInformation();

//Функции работы с памятью

//Вывод информации о памяти
void getGlobalMemoryStatus();

//Состояние конкретного участка памяти, введённого с клавиатуры
void getVirtualQuery(void* ptr);

//выделение региона памяти в автоматическом режиме
void reserveMemory();

//выделение региона памяти и передача ему физической памяти в автоматическом режиме
void reserveMemorySim();

//Запись в выделенный регион памяти введенной пользователем строки.
void writeString();

//Установка флага на запрет доступа к региону памяти.
void protectMemory();

//Очищение выделенного региона памяти
void freeMemory();


PVOID paddress = nullptr;


int main() {

	int menu;
	int ptr;

	do
	{
		system("cls");
		menu = showMenu();

		switch (menu) 
		{
		case 1:
			system("cls");
			getSysInformation();

			system("pause");
			break;

		case 2:
			system("cls");
			getGlobalMemoryStatus();

			system("pause");
			break;

		case 3:

			system("cls");
			

			if (paddress != nullptr) 
			{ 
				cout << "Commited memory address: " << hex << paddress << endl; 
			}

			cout << "Enter memory address(hex): ";
			cin >> hex >> ptr;

			getVirtualQuery((void*)ptr);

			system("pause");
			break;

		case 4:
			system("cls");
			reserveMemory();

			system("pause");
			break;

		case 5:
			system("cls");
			reserveMemorySim();

			system("pause");
			break;

		case 6:
			system("cls");
			writeString();

			system("pause");
			break;

		case 7:
			system("cls");
			protectMemory();

			system("pause");
			break;

		case 8:
			system("cls");
			freeMemory();

			system("pause");
			break;

		case 0:

			system("cls");

			puts("Best wishes!");
			
			system("pause");
			break;

		default:

			cout << "Retry input!" << endl;

			system("pause");
			break;

		}


	} while (menu != 0);

}


int showMenu()
{
	int res; // ввод пользователя
	cout << "Choose the function:" << endl
		<< "1 - getSystemInfo() " << endl
		<< "2 - getGlobalMemoryStatus() " << endl
		<< "3 - getVirtualQuery(pointer) " << endl
		<< "4 - reserveMemory() " << endl
		<< "5 - reserveMemorySim() " << endl
		<< "6 - writeString() " << endl
		<< "7 - protectMemory() " << endl
		<< "8 - freeMemory() " << endl
		<< "0 - exit " << endl
		<< ">>";
	cin >> res;
	return res;

}

void getSysInformation() 
{

	SYSTEM_INFO info;
	GetSystemInfo(&info);

	cout << "<<Output of system information>>" << endl;

	cout << "System info:" << endl;
	cout << "Processor architecture: ";

	switch (info.wProcessorArchitecture) 
	{
		case PROCESSOR_ARCHITECTURE_AMD64:

			cout << "x64 (AMD or Intel)" << endl;

		break;

		case PROCESSOR_ARCHITECTURE_ARM:

			cout << "ARM" << endl;

		break;

		case PROCESSOR_ARCHITECTURE_ALPHA:

			cout << "Alpha" << endl;

		break;

		case PROCESSOR_ARCHITECTURE_IA64:

			cout << "Intel Itanium-based" << endl;

		break;

		case PROCESSOR_ARCHITECTURE_INTEL:

			cout << "x86" << endl;

		break;

		default:

			cout << "No information" << endl;

		break;
	}


	cout << "Page size: " << info.dwPageSize << endl;
	cout << "Minimum application address: " << info.lpMinimumApplicationAddress << endl;
	cout << "Maximum application address: " << info.lpMaximumApplicationAddress << endl;
	cout << "Number of processors: " << info.dwNumberOfProcessors << endl; 
	
	bitset<32> x(info.dwActiveProcessorMask); 

	cout << "Active processors: " << x << endl;
	cout << "Allocation granuality: " << info.dwAllocationGranularity << endl;
	cout << "Processor level: " << info.wProcessorLevel << endl;
	cout << "Processor revision: " << info.wProcessorRevision << endl;

}

void getGlobalMemoryStatus() 
{


	MEMORYSTATUS status;
	GlobalMemoryStatus(&status);

	cout << "<<Output of memory information>>" << endl;

	cout << "Global memory status: " << endl;
	cout << "Physical memory in use, %: " << status.dwMemoryLoad << endl;
	cout << "Actual physical memory, bytes: " << status.dwTotalPhys << endl;
	cout << "Available physical memory, bytes: " << status.dwAvailPhys << endl;

	cout << "Commited memory limit: " << status.dwTotalPageFile << endl;
	cout << "Available memory processor can commit: " << status.dwAvailPageFile << endl;

	cout << "Total virtual address space: " << status.dwTotalVirtual << endl;
	cout << "Ammount of virtual address space: " << status.dwAvailVirtual << endl;

}

void getVirtualQuery(void* ptr) 
{


	MEMORY_BASIC_INFORMATION memBasicInfo;

	cout << "<<State of a specific memory area entered from the keyboard>>" << endl;

	if (VirtualQuery(ptr, &memBasicInfo, sizeof(memBasicInfo))) 
	{

		cout << "Base address: " << memBasicInfo.BaseAddress << endl
			 << "Allocation base: " << memBasicInfo.AllocationBase << endl
			 << "Memory protection: " << memBasicInfo.AllocationProtect << endl
			 << "Region size: " << memBasicInfo.RegionSize << endl
			 << "State: " << memBasicInfo.State << " "; 
		
		
		switch (memBasicInfo.State) 
		{
			case MEM_COMMIT:

				cout << "memory committed" << endl;
				break;

			case MEM_FREE:

				cout << "memory free" << endl;
				break;

			case MEM_RESERVE:

				cout << "memory reserved" << endl;
				break;
		}


		cout << "Protect: " << hex << memBasicInfo.Protect << endl; 
		
		switch (memBasicInfo.Protect) 
		{
			case PAGE_READONLY:

				cout << "PAGE_READONLY" << endl;
				break;

			case PAGE_READWRITE:

				cout << "PAGE_READWRITE" << endl;
				break;

			case PAGE_WRITECOMBINE:

				cout << "PAGE_WRITECOMBINE" << endl;
				break;

			case PAGE_WRITECOPY:

				cout << "PAGE_WRITECOPY" << endl;
				break;

			case PAGE_GUARD:

				cout << "PAGE_GUARD" << endl;
				break;

			case PAGE_NOACCESS:

				cout << "PAGE_NOACCESS" << endl;
				break;

			case PAGE_NOCACHE:

				cout << "PAGE_NOCACHE" << endl;
				break;

			case PAGE_EXECUTE:

				cout << "PAGE_EXECUTE" << endl; 
				break;

			case PAGE_EXECUTE_READ:

				cout << "PAGE_EXECUTE_READ" << endl; 
				break;

			case PAGE_EXECUTE_READWRITE:

				cout << "PAGE_EXECUTE_READWRITE" << endl; 
				break;

			case PAGE_EXECUTE_WRITECOPY:

				cout << "PAGE_EXECUTE_WRITECOPY" << endl; 
				break;
			
		}

		cout << "Type: " << hex << memBasicInfo.Type;
		
		switch (memBasicInfo.Type) 
		{

			case MEM_IMAGE:

				cout << " mapped into the view of an image section" << endl;
				break;

			case MEM_MAPPED:

				cout << " mapped into the view of a section" << endl;
				break;

			case MEM_PRIVATE:

				cout << " memory pages within the region are private" << endl;
				break;

		}
		cout << endl;

	}
	else {

		cout << "An error occurred. Error code: " << GetLastError() << endl;

	}

}

void reserveMemory() 
{

	cout << "<<Allocation of the region of memory in automatic mode>>" << endl;

	SIZE_T rSize = 0;

	if (paddress != nullptr) 
		freeMemory();

	int address;

	cout << "Enter address to allocate(-1 to auto allocate): "; 
	cin >> address;

	if (address == -1) 
		paddress = nullptr;
	else 
		paddress = (PVOID)address;

	cout << "Enter size of region: ";

	cin >> rSize;

	

	if (paddress = VirtualAlloc(paddress, rSize, MEM_RESERVE, PAGE_READWRITE)) 
	{
		cout << "Memory reserved. " << endl;

		if (paddress = VirtualAlloc(paddress, rSize, MEM_COMMIT, PAGE_READWRITE)) 
		{
			cout << "Memory commited." << endl;
			getVirtualQuery(paddress);
		}
		else
			cout << "Error commiting memory. Error code: " << GetLastError() << endl;

		paddress = nullptr;

		rSize = 0;

	}
	else 
	{
		cout << "Error reserving memory. Error code: " << GetLastError() << endl;
		paddress = nullptr;
		rSize = 0;
	}

}


void reserveMemorySim() 
{
	cout << "<<Allocation of a memory region and transfer of physical memory to it in automatic mode>>" << endl;

	SIZE_T rSize = 0;

	if (paddress != nullptr) 
		freeMemory();

	int address;

	cout << "Enter address to allocate(-1 to auto alloc): "; 
	cin >> address;

	if (address == -1) 
		paddress = nullptr;
	else 
		paddress = (PVOID)address;

	cout << "Enter size of region: ";
	cin >> rSize;

	

	if (paddress = VirtualAlloc(paddress, rSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE)) 
	{
		cout << "Memory reserved and commited. " << endl; 
		getVirtualQuery(paddress);
	}
	else 
	{
		cout << "Error allocating memory. Error code:  " << GetLastError() << endl;
		paddress = nullptr;
		rSize = 0;
	}

}


void freeMemory() {

	if (VirtualFree(paddress, 0, MEM_RELEASE)) 
	{
		cout << "memory cleanup was successful." << endl;
	}
	else 
	{
		cout << "Error cleanup memory. Error code: " << GetLastError() << endl;
	}

}



void writeString() {

	cout << "<<Write a string entered by the user to the allocated memory region.>>" << endl;

	string s;
	cout << "Enter the string you want to write: ";

	cin.ignore(1024, '\n');
	getline(cin, s);

	

	memcpy(paddress, s.c_str(), s.length());
	cout << "Writing the string was successful." << endl;

}


void protectMemory() {

	cout << "<<Setting the flag to deny access to the memory region.>>" << endl;
	
	SIZE_T rSize = 0;
	DWORD OldProtect, newProtect;
	
	

	cout << "Enter new flag: ";

	cin >> hex >> newProtect;

	if (VirtualProtect(paddress, rSize, newProtect, &OldProtect)) 
	{
		cout << "Flag set successful." << endl;
	}

	getVirtualQuery(paddress);

}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
