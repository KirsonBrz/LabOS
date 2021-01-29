// FourthLab.PipeServer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	HANDLE hPipe = INVALID_HANDLE_VALUE;
	HANDLE hEvent = INVALID_HANDLE_VALUE;
	OVERLAPPED overlapped = OVERLAPPED();
	BOOL connection = false;

	char flag;

	do {
		system("cls");
		cout << "Введите пункт меню для работы: \n";
		cout << "1 - Создать канал" << endl;
		cout << "2 - Установить соединение" << endl;
		cout << "3 - Ввод данных" << endl;
		cout << "4 - Отключить соединение" << endl;
		cout << "0 - Выход" << endl;
		cin >> flag;
		system("cls");

		switch (flag) {
		case '1':

			hPipe = CreateNamedPipeA("\\\\.\\pipe\\pipename", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);
			if (hPipe != INVALID_HANDLE_VALUE) {
				cout << "Канал создан!\n";
			}

			system("pause");
			break;

		case '2':

			connection = ConnectNamedPipe((HANDLE)hPipe, NULL);
			if (connection)
				cout << "Подключение установлено!\n";
			else
				cout << "Подключение не установлено!\n";

			system("pause");
			break;

		case '3':
			if (!connection) {
				cout << "Установите подключение!" << endl;
			}
			else {

				hEvent = CreateEventA(NULL, false, false, NULL);
				if (hEvent == INVALID_HANDLE_VALUE)
					cout << GetLastError();

				char* mes = new char[512];
				cout << "Передаваемое сообщение: ";
				cin >> mes;

				overlapped.hEvent = hEvent;
				WriteFile(hPipe, mes, 512, NULL, &overlapped);

				if (WaitForSingleObject(hEvent, 2000) == WAIT_OBJECT_0)
					cout << "Сообщение успешно передано!" << endl;
			}
			cout << endl;

			system("pause");
			break;

		case '4':
			if (DisconnectNamedPipe((HANDLE)hPipe)) {
				cout << "Соединение отключено!\n";
				connection = FALSE;
			}
			break;

		default:
			break;

		case '0':
			system("cls");
			break;
		}

	} while (flag != '0');


	if (hPipe != INVALID_HANDLE_VALUE)
		CloseHandle(hPipe);
	if (hEvent != INVALID_HANDLE_VALUE)
		CloseHandle(hEvent);

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
