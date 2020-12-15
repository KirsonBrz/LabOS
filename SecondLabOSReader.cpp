// SecondLabOSReader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>
#include <locale.h>

using namespace std;


int main()
{
	HANDLE handleMap;
	string descriptorName;
	LPVOID mapView;

	//Open FileMapping

	cout << "Enter descriptor name(same as in writer programm): " << endl;
	cin >> descriptorName;


	handleMap = OpenFileMapping(FILE_MAP_READ, false, (LPCWSTR)descriptorName.c_str());

	if (handleMap) 
	{

		//Create a mapView to displays a representation of the projected file in the address space

		mapView = MapViewOfFile(handleMap, FILE_MAP_READ, 0, 0, NULL);
		if (mapView)
		{

			//Output the information from file
			
			cout << "File data:" << endl
				 << (char*)mapView << endl;
		
			system("pause");
			UnmapViewOfFile(mapView);
		}
		else
		{
			cout << " An error occurred in MapViewOfFile. Error code: " << GetLastError() << endl;
			system("pause");

		}


	}
	else
	{
		cout << " An error occurred in OpenFileMapping. Error code: " << GetLastError() << endl;
		system("pause");

	}
	CloseHandle(handleMap);

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
