// ThirdLabOS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <time.h>


using namespace std;

//Прототипы функций для работы
DWORD WINAPI calculation(LPVOID lpParam);

//Переменные, необходимые для работы

DWORD block_size = 8308040; // размер блока
DWORD N = 100000000; //общее количество итераций
long double pi = 0.0; 
int count_threads; // число потоков
int current_position = 0; //текущая позиция потока
LPCRITICAL_SECTION section = new CRITICAL_SECTION; //критическая секция



int main()
{
	setlocale(LC_ALL, "rus");

	DWORD start, end;

	cout << "Введите количество потоков - " << endl;
	cin >> count_threads;

	HANDLE* Threads = new HANDLE[count_threads];
	int* position = new int[count_threads];
	InitializeCriticalSection(section);

	for (int i = 0; i < count_threads; ++i) {
		position[i] = block_size * i;
		current_position = position[i];
		Threads[i] = CreateThread(NULL, 0, calculation, &position[i], CREATE_SUSPENDED, NULL);
	}

	start = clock();

	for (int i = 0; i < count_threads; ++i) {
		ResumeThread(Threads[i]);
	}

	WaitForMultipleObjects(count_threads, Threads, TRUE, INFINITE);

	end = clock();

	cout << "\nВремя работы программы: " << end - start << endl;

	cout.precision(15);
	cout << "Вычисленное значение числа pi: " << pi / N << "\n";

	DeleteCriticalSection(section);
}


DWORD WINAPI calculation(LPVOID lpParam) {

	int* first = (int*)lpParam;
	int end = *first + block_size;
	long double x = 0.0, temp = 0.0;

	do {

		temp = 0.0;

		for (int i = *first; (i < end) && (i < N); ++i) {
			x = (i + 0.5) / N;
			temp += (4 / (1 + x * x));
		}

		EnterCriticalSection(section);
		pi += temp;
		current_position += block_size;
		*first = current_position;
		LeaveCriticalSection(section);

		end = *first + block_size;

	} while (*first < N);

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
