// FourthLab.PipeClient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void WINAPI ReadCallback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
	cout << "Информация успешно считана!" << endl;
}


int main()
{
	setlocale(LC_ALL, "Rus");

	HANDLE hPipe = INVALID_HANDLE_VALUE;
	OVERLAPPED overlapped = OVERLAPPED();
	BOOL connection = false;

	char flag;

	do {
		system("cls");
		cout << "Введите пункт меню для работы: \n";
		cout << "1 - Подключиться к каналу" << endl;
		cout << "2 - Считать строку" << endl;
		cout << "0 - Выход" << endl;
		cin >> flag;
		system("cls");

		switch (flag) {
		case '1':

			hPipe = CreateFileA("\\\\.\\pipe\\pipename", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
			if (hPipe != INVALID_HANDLE_VALUE)
				cout << "Подключение выполнено!\n";
			else
				cout << GetLastError();

			system("pause");
			break;

		case '2': {
			char* mes = new char[512];
			overlapped = OVERLAPPED();
			if (!ReadFileEx(hPipe, (LPVOID)mes, 512, &overlapped, ReadCallback))
				cout << "Не считанно!\n";
			else
			{
				SleepEx(INFINITE, true);
				cout << "Полученное сообщение: ";
				for (int i = 0; i < strlen(mes); ++i) {
					cout << mes[i];
				}
				cout << endl;
			}

			system("pause");
			break;
		}
		default:
			break;

		case '0':
			system("cls");
			break;
		}

	} while (flag != '0');


	if (hPipe != INVALID_HANDLE_VALUE)
		CloseHandle(hPipe);

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
