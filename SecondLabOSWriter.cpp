// SecondLabOSWriter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main() {

	string fileDirection, descriptorName, writingData;

	HANDLE handleFile, handleMap;

	LPVOID mapView;


	//Creating file

	cout << " Enter direction of file(example c://newDir//newFile.txt): " << endl;
	cin >> fileDirection;


	handleFile = CreateFileA((LPCSTR)fileDirection.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,

		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handleFile)
	{
		cout << " File " << fileDirection << " was created successful." << endl;

		//Creating map

		cout << "Enter descriptor name: " << endl;
		cin >> descriptorName;


	

		handleMap = CreateFileMapping(handleFile, NULL, PAGE_READWRITE, 0, 512, (LPCWSTR)descriptorName.c_str());

		if (handleMap) {


			//Create a mapView to displays a representation of the projected file in the address space
			mapView = MapViewOfFile(handleMap, FILE_MAP_WRITE, 0, 0, NULL);
			if (mapView)
			{
			
				//Input the string and write it to the file

				cout << "Enter the string which must be written to a file: " << endl;

				cin.ignore(1024, '\n');
				getline(cin, writingData);

				CopyMemory(mapView, (char*)writingData.c_str(), writingData.length() * sizeof(char));

				cout << "String written successful: " << endl;

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
			cout << " An error occurred in CreateFileMappingA. Error code: " << GetLastError() << endl;
			system("pause");
		
		}
		CloseHandle(handleMap);

	}
		
	else
	{
		cout << " An error occurred in CreateFileA. Error code: " << GetLastError() << endl;
		system("pause");
	}
		
	CloseHandle(handleFile);
	

	cout << "Best wishes!" << endl;

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
