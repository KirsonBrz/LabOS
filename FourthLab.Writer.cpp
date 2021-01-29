// FourthLab.Writer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;

int main() {

	const int PageCount = 15, PageSize = 4096;
	srand(GetCurrentProcessId());

	HANDLE WriteSem[PageCount];
	HANDLE ReadSem[PageCount];
	for (int i = 0; i < PageCount; i++) {
		WriteSem[i] = OpenSemaphoreA(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, false, ("WSemaphore" + to_string(i)).c_str());
		ReadSem[i] = OpenSemaphoreA(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, false, ("RSemaphore" + to_string(i)).c_str());
	}

	HANDLE LogMutex = OpenMutexA(MUTEX_MODIFY_STATE | SYNCHRONIZE, false, "LogMutex");
	HANDLE Mapping = OpenFileMappingA(GENERIC_WRITE, false, "map_file");
	void* OwnMap = MapViewOfFile(Mapping, FILE_MAP_WRITE, 0, 0, PageSize * PageCount);
	VirtualLock(OwnMap, PageSize * PageCount);
	ofstream Log;
	Log.open("C:\\Labor4\\log.txt", fstream::out | fstream::app);

	while (1)
	{
		char msg[PageSize];
		for (int i = 0; i < PageSize; i++)
			msg[i] = 'a' + rand() % 26;

		WaitForSingleObject(LogMutex, INFINITE);
		Log << "Type: WriteProcess " << "Time: " << GetTickCount() << " ID: " << GetCurrentProcessId() << " Operation: start to waiting" << endl;
		ReleaseMutex(LogMutex);

		DWORD index = WaitForMultipleObjects(PageCount, WriteSem, false, INFINITE);

		WaitForSingleObject(LogMutex, INFINITE);
		Log << "Type: WriteProcess " << "Time: " << GetTickCount() << " ID: " << GetCurrentProcessId() << " Operation: start to write" << "Page: " << index << endl;
		ReleaseMutex(LogMutex);

		CopyMemory((LPVOID)((int)OwnMap + (index * PageSize)), msg, PageSize);
		Sleep(500 + (rand() % 1000));

		WaitForSingleObject(LogMutex, INFINITE);
		Log << "Type: WriteProcess " << "Time: " << GetTickCount() << " ID: " << GetCurrentProcessId() << " Operation: end of write" << "Page: " << index << endl;
		ReleaseMutex(LogMutex);

		ReleaseSemaphore(ReadSem[index], 1, NULL);
	}
	system("pause");
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
