// FourthLab.ReaderWriter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

int main() {

	const int PageCount = 15, SizePage = 4096, Process = 7;

	HANDLE MapFileHandle = CreateFileA("C:\\Labor4\\File", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE MapFileMapping = CreateFileMappingA(MapFileHandle, NULL, PAGE_READWRITE, 0, SizePage * PageCount, "map_file");

	HANDLE WriteSem[PageCount];
	HANDLE ReadSem[PageCount];

	for (int i = 0; i < PageCount; i++)
	{
		WriteSem[i] = CreateSemaphoreA(NULL, 1, 1, ("WSemaphore" + to_string(i)).c_str());
		ReadSem[i] = CreateSemaphoreA(NULL, 0, 1, ("RSemaphore" + to_string(i)).c_str());

		if (WriteSem[i] == NULL || ReadSem[i] == NULL) {
			cout << GetLastError() << endl;
		}
	}
	HANDLE LogMutex = CreateMutexA(NULL, false, "LogMutex");

	ofstream ofs;
	ofs.open("C:\\Labor4\\log.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();


	PROCESS_INFORMATION piW[Process];
	PROCESS_INFORMATION piR[Process];
	for (int i = 0; i < Process; i++)
	{
		STARTUPINFOA siW;
		ZeroMemory(&siW, sizeof(siW));
		siW.cb = sizeof(siW);
		ZeroMemory(&(piW[i]), sizeof(piW[i]));

		STARTUPINFOA siR;
		ZeroMemory(&siR, sizeof(siR));
		siR.cb = sizeof(siR);
		ZeroMemory(&(piR[i]), sizeof(piR[i]));

		if (!CreateProcessA("D:\\VisualProjects\\FourthLab.Writer\\Debug\\FourthLab.Writer.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &siW, &(piW[i]))) {
			cout << GetLastError() << endl;
		}

		if (!CreateProcessA("D:\\VisualProjects\\FourthLab.Reader\\Debug\\FourthLab.Reader.exe", NULL, NULL, NULL, false, 0, NULL, NULL, &siR, &(piR[i]))) {
			cout << GetLastError() << endl;
		}
	}

	system("pause");

	CloseHandle(MapFileHandle);
	CloseHandle(MapFileMapping);
	for (int i = 0; i < Process; i++)
	{
		CloseHandle(piW[i].hProcess);
		CloseHandle(piW[i].hThread);
		CloseHandle(piR[i].hProcess);
		CloseHandle(piR[i].hThread);
	}

	for (auto& i : WriteSem)
		CloseHandle(i);
	for (auto& i : ReadSem)
		CloseHandle(i);

	return 0;
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
