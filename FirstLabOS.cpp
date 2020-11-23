// FirstLabOS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

using namespace std;


//Прототипы функций для работы

//Меню
int showMenu();

// функции вывода списка дисков
void getLogDrives();
void getLogDriveStr();

// функции вывода информации о диске и размере свободного пространства
void getVolInfo(string diskName);

// Функции создания и удаления каталогов
void createDir();
void removeDir();

// Функции создания, копирования и перемещения файлов между каталогами
void createF();
void copyF();
void moveF();
void moveFEx();

// Функции получения информации и изменения атрибутов файлов
void getFAtt();
void setFAtt();
void getFInfo();
void getFTime();
void setFTime();






int main()
{
	setlocale(LC_ALL, "Rus");

	int menu;
	
	// Информация о диске
	string diskName;
	
	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;
	DWORD totalNumberOfClusters;
	

	
	do
	{
		system("cls");
		menu = showMenu();
		switch (menu)
		{
		case 1: // Вывод списка дисков двумя способами
			system("cls");
			cout << "Первый способ" << endl;
			// Первый способ
			getLogDrives();

			cout << "Второй способ" << endl;
			getLogDriveStr();
			
			system("pause");
			break;
		case 2:

			system("cls");
			//Выбор диска для работы
			getLogDrives();
			cout << "Введите имя диска для работы (одним символом) " << endl;
			cin >> diskName;
			diskName += "://";
			
			// Вывод типа устройства
			switch (GetDriveTypeA((LPCSTR)diskName.c_str())) {
			case 0:
				cout << "Тип устройства определить не удалось" << endl;
				break;
			case 1:
				cout << "Корневой директории не существует" << endl;
				break;
			case 2:
				cout << "Этот диск является сменным диском (например дискетта или любой сменный диск)" << endl;
				break;
			case 3:
				cout << "Этот диск является жестким диском" << endl;
				break;
			case 4:
				cout << "Этот диск является сетевым диском" << endl;
				break;
			case 5:
				cout << "Этот диск является CD-ROM" << endl;
				break;
			case 6:
				cout << "Этот диск является RAM-диском" << endl;
				break;
			}

			//Вывод информации о диске
			cout << "Информация о диске: " << endl;
			getVolInfo(diskName);

			//Вывод информации о памяти диска
			cout << "Информация о памяти диска: " << endl;
			
			if (GetDiskFreeSpaceA( (LPCSTR)diskName.c_str(),
				&sectorsPerCluster,
				&bytesPerSector,
				&numberOfFreeClusters,
				&totalNumberOfClusters)) {
				cout << "  Число секторов в кластере: " << sectorsPerCluster << endl;
				cout << "  Число байт в секторе: " << bytesPerSector << endl;
				cout << "  Число свободных кластеров: " << numberOfFreeClusters << endl;
				cout << "  Общее число кластеров: " << totalNumberOfClusters << endl;
			}
			else
				cout << " Не удалось получить информацию. Код ошибки: " << GetLastError() << endl;

			
			system("pause");
			break;

		case 3:
			system("cls");
			createDir();
			
			system("pause");
			break;
		case 4:
			system("cls");
			removeDir();

			system("pause");
			break;
		case 5:
			system("cls");
			createF();

			
			system("pause");
			break;
		case 6:
			system("cls");
			copyF();

			system("pause");
			break;
		case 7:
			system("cls");
			moveF();

			system("pause");
			break;
		case 8:
			system("cls");
			moveFEx();
		
			system("pause");
			break;
		case 9:
			system("cls");
			getFAtt();

			system("pause");
			break;
		case 10:
			system("cls");
			setFAtt();

			system("pause");
			break;
		case 11:
			system("cls");
			getFInfo();

			system("pause");
			break;
		case 12:
			system("cls");
			getFTime();
			
			system("pause");
			break;
		case 13:
			system("cls");
			setFTime();

			system("pause");
			break;
		case 0:

			system("cls");
			
			puts("Всего наилучшего!");
			system("pause");

			break;
		default:
			cout << "Вы выбрали несуществующий пункт меню, повторите ввод!" << endl;
			system("pause");
			break;

		}
		
		
	} while (menu != 0);
	


	
	return 0;
}

int showMenu()
{
	int res; // ввод пользователя
	cout << "Выберите пункт меню для продолжения:" << endl
		<< "1 - вывод списка дисков " << endl
		<< "2 - вывод информации о диске " << endl
		<< "3 - создать каталог " << endl
		<< "4 - удалить каталог " << endl
		<< "5 - создать файл " << endl
		<< "6 - копировать файл " << endl
		<< "7 - переместить файл " << endl
		<< "8 - переместить файл с флагом " << endl
		<< "9 - получить атрибуты файла " << endl
		<< "10 - установить атрибуты файла " << endl
		<< "11 - информация о файле " << endl
		<< "12 - вывод временных характеристик файла " << endl
		<< "13 - изменить временные характеристики файла " << endl
		<< "0 - выход из программы " << endl
		<< ">>";
	cin >> res;
	return res;

}

//Оба способа вывода дисков
//Первый способ
void getLogDrives() {

	int temp;
	DWORD logDrives = GetLogicalDrives(); // получаем битовую маску

	cout << "Доступные диски:" << endl;
	for (int i = 0; i < 26; i++) // проходимся по битам, если текущий единица, то диск с номером i есть
	{
		temp = (logDrives >> i) & 1;
		if (temp)
		{
			cout << (char)(65 + i) << ":\\   ";
		}

	}
	cout << endl;
}

// Второй способ
void getLogDriveStr() {
	wchar_t disks[256];
	wchar_t* disk;
	DWORD bufSize = 256;
	GetLogicalDriveStrings(bufSize, disks);
	disk = disks;
	cout << "Доступные диски:" << endl;
	while (*disk)
	{
		wprintf(L"%s   ", disk);
		disk = disk + wcslen(disk) + 1;
	}
	cout << endl;
	
}

// Реализация GetVolumeInformation

void getVolInfo(string diskName) {
	
	char VolumeNameBuffer[100];
	char FileSystemNameBuffer[100];
	unsigned long VolumeSerialNumber;
	DWORD VolumeFlags;

	if (GetVolumeInformationA(
		(LPCSTR)diskName.c_str(),
		VolumeNameBuffer,
		100,
		&VolumeSerialNumber,
		NULL,
		&VolumeFlags,
		FileSystemNameBuffer,
		100
	))
	{
		cout << "Имя диска -   " << VolumeNameBuffer << endl <<
				"Серийный номер диска -   " << VolumeSerialNumber << endl <<
				"Файловая система -   " << FileSystemNameBuffer << endl;

		cout << "Флаги файловой системы: " << endl;
		if (VolumeFlags & FS_CASE_IS_PRESERVED)
			cout << "  При записи на диск сохраняется регистр букв в имени файла" << endl;
		if (VolumeFlags & FS_FILE_COMPRESSION)
			cout << "  Файловая система поддерживает сжатие файлов" << endl;
		if (VolumeFlags & FS_VOL_IS_COMPRESSED)
			cout << "  Том был подвергнут сжатию" << endl;
		if (VolumeFlags & FILE_NAMED_STREAMS)
			cout << "  Файловая система поддерживает именованные потоки" << endl;
		if (VolumeFlags & FILE_SUPPORTS_ENCRYPTION)
			cout << "  Файловая система поддерживает Encrypted File System (EFS)" << endl;
		if (VolumeFlags & FILE_SUPPORTS_OBJECT_IDS)
			cout << "  Файловая система поддерживает идентификаторы объектов" << endl;
	}
	else 
		cout << " Не удалось получить информацию. Код ошибки: " << GetLastError() << endl;
	
}

void createDir()
{
	string nameCreateDir;
	
	cout << "Введите конечный путь к создаваемому каталогу(пример c://newDir):" << endl;
	cin >> nameCreateDir;


	if (CreateDirectoryA((LPCSTR)nameCreateDir.c_str(), NULL))
		cout << "Каталог " << nameCreateDir << " создан." << endl;
	else
		cout << " Произошла ошибка. Каталог не был создан. Код ошибки: " << GetLastError() << endl;
	cout << endl;
}

void removeDir()
{
	string nameRemoveDir;

	cout << "Введите конечный путь к удаляемому каталогу(пример c://newDir):" << endl;
	cin >> nameRemoveDir;


	if (RemoveDirectoryA((LPCSTR)nameRemoveDir.c_str()))
		cout << "Каталог " << nameRemoveDir << " успешно удален." << endl;
	else
		cout << " Произошла ошибка. Каталог не был удален. Код ошибки: " << GetLastError() << endl;
	cout << endl;
}

void createF()
{
	HANDLE handleFile;
	string fileCreateDir;

	cout << " Введите конечный путь к создаваемому файлу(пример c://newDir//newFile.txt): " << endl;
	cin >> fileCreateDir;

	handleFile = CreateFileA((LPCSTR)fileCreateDir.c_str(), GENERIC_READ |
		GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
	if (handleFile)
		cout  << " Файл " << fileCreateDir << " был создан." << endl;
	else
		cout << " Произошла ошибка. Файл не был создан. Код ошибки: " << GetLastError() << endl;

	CloseHandle(handleFile);

	cout << endl;
}

void copyF()
{
	string firstName, copyName;

	cout << " Введите конечный путь к копируемому файлу(пример c://newDir//oldFile.txt): " << endl;
	cin >> firstName;

	cout << " Введите конечный путь к новому файлу(пример c://newDir//newFile.txt): " << endl;
	cin >> copyName;

	if (CopyFileA((LPCSTR)firstName.c_str(), (LPCSTR)copyName.c_str(), 0))
		cout <<" Файл " << firstName << " успешно скопирован." << endl;
	else {
		if (GetLastError() == 183)
			cout << " Файл с таким названием уже существует." << endl;
		else
			cout << " Произошла ошибка. Копирование не выполнено. Код ошибки: " << GetLastError() << endl;
	}
	
}

void moveF() {
	string firstPath, newPath;

	cout << " Введите конечный путь к перемещаемому файлу(пример c://newDir//oldFile.txt): " << endl;
	cin >> firstPath;

	cout << " Введите конечный путь к новому файлу(пример c://newDir//newFile.txt): " << endl;
	cin >> newPath;

	if (MoveFileA((LPCSTR)firstPath.c_str(), (LPCSTR)newPath.c_str()))
		cout << " Файл " << firstPath << " был перемещен." << endl;
	else {
		if (GetLastError() == 183)
			cout << " Файл с таким названием уже существует." << endl;
		else
			cout << " Произошла ошибка. Перемещение не выполнено. Код ошибки: " << GetLastError() << endl;
	}
	cout << endl;
}

void moveFEx() {
	string firstPath, newPath;

	cout << " Введите конечный путь к перемещаемому файлу(пример c://newDir//oldFile.txt): " << endl;
	cin >> firstPath;

	cout << " Введите конечный путь к новому файлу(пример c://newDir//newFile.txt): " << endl;
	cin >> newPath;


	if (MoveFileExA((LPCSTR)firstPath.c_str(), (LPCSTR)newPath.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING))
		cout << " Файл " << firstPath << " был перемещен." << endl;
	else
		cout << " Произошла ошибка. Перемещение не выполнено. Код ошибки: " << GetLastError() << endl;
	cout << endl;
}


void getFAtt() {
	string path;
	long FileAttributes;
	
	cout << " Введите конечный путь к проверяемому файлу/каталогу(пример c://newDir//newFile.txt): " << endl;
	cin >> path;

	FileAttributes = GetFileAttributesA((LPCSTR)path.c_str());

	if (FileAttributes == -1)
		cout <<  " Файл " << path << " не найден." << endl;
	else {
		if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
			cout <<  " Файл " << path << " - архивный." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			cout <<  " Файл " << path << " - директория." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_READONLY)
			cout <<  " Файл " << path << " - только для чтения." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
			cout <<  " Файл " << path << " - системный." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
			cout <<  " Файл " << path << " - сжатый." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
			cout <<  " Файл " << path << " - скрытый." << endl;
		if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
			cout <<  " Файл " << path << " не имеет таких атрибутов." << endl;
		if (FileAttributes == 0)
			cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
	}
	cout << endl;
}


void setFAtt() {
	string path;
	int key;
	long FileAttributes;

	cout << " Введите конечный путь к файлу/каталогу, которому нужно установить атрибуты(пример c://newDir//newFile.txt): " << endl;
	cin >> path;

	cout << "1 - Сбросить все атрибуты " << endl
		 << "2 - Сделать скрытым файлом" << endl
		 << "3 - Сделать архивным файлом" << endl
		 << "4 - Сделать файлом 'только для чтения'" << endl
		 << "5 - Сделать системным файлом" << endl
		 << ">> " << endl;
	cin >> key;

	FileAttributes = GetFileAttributesA((LPCSTR)path.c_str());

	switch (key) {
	case 1:
		FileAttributes = FILE_ATTRIBUTE_NORMAL;
		break;
	case 2:
		FileAttributes |= FILE_ATTRIBUTE_HIDDEN;
		break;
	case 3:
		FileAttributes |= FILE_ATTRIBUTE_ARCHIVE;
		break;
	case 4:
		FileAttributes |= FILE_ATTRIBUTE_READONLY;
		break;
	case 5:
		FileAttributes |= FILE_ATTRIBUTE_SYSTEM;
		break;
	default:
		cout << "Ключ был введен неверно." << endl;
		break;
	}

	if (key > 0 && key < 6) {
		if (SetFileAttributesA((LPCSTR)path.c_str(), FileAttributes))
			cout << " Атрибуты успешно установлены." << endl;
		else
			cout << " Произошла ошибка при установке атрибутов. Код ошибки: " << GetLastError() << endl;
	}
	cout << endl;
}


void getFInfo() {
	long handleInfo, FileAttributes;
	BY_HANDLE_FILE_INFORMATION infoFile;
	string path;
	HANDLE handleFile;

	cout << " Введите конечный путь к файлу/каталогу, о котором нужно получить информацию(пример c://newDir//newFile.txt): " << endl;
	cin >> path;

	handleFile = CreateFileA((LPCSTR)path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	handleInfo = GetFileInformationByHandle(handleFile, &infoFile);
	if (!handleInfo)
		cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
	else {
		FileAttributes = infoFile.dwFileAttributes;
		if (FileAttributes == -1)
			cout << " Файл " << path << " не найден." << endl;
		else {

			cout << "Информация о файле по дескриптору:" << endl;
			
			if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				cout << " Файл " << path << " - архивный." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				cout << " Файл " << path << " - директория." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_READONLY)
				cout << " Файл " << path << " - только для чтения." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
				cout << " Файл " << path << " - системный." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
				cout << " Файл " << path << " - сжатый." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
				cout << " Файл " << path << " - скрытый." << endl;
			if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
				cout << " Файл " << path << " не имеет таких атрибутов.";
			if (FileAttributes == 0)
				cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
		}


		cout << " Старшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexHigh << endl;
		cout << " Порядковый номер тома, который содержит файл: " << infoFile.dwVolumeSerialNumber << endl;
		cout << " Старшая часть размера файла: " << infoFile.nFileSizeHigh << endl;
		cout << " Младшая часть размера файла: " << infoFile.nFileSizeLow << endl;
		cout << " Число связей с этим файлом: " << infoFile.nNumberOfLinks << endl;
		cout << " Младшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexLow << endl;
	}
	handleInfo = CloseHandle(handleFile);
	cout << endl;
}

void getFTime() {

	HANDLE handleFile;
	string path;
	
	FILETIME createTime, accessFile, lastWFile;
	
	SYSTEMTIME UTCtime, localTime;

	cout << " Введите конечный путь к проверяемому файлу/каталогу(пример c://newDir//newFile.txt): " << endl;
	cin >> path;

	handleFile = CreateFileA((LPCSTR)path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING | CREATE_NEW, 0, NULL);
	if (!handleFile)
		cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
	else {
		GetFileTime(handleFile, &createTime, &accessFile, &lastWFile);

		FileTimeToSystemTime(&createTime, &UTCtime);
		
		SystemTimeToTzSpecificLocalTime(NULL, &UTCtime, &localTime);
		cout << " Дата и время создания файла: " << endl
			<< localTime.wDay << "." << localTime.wMonth << "." << localTime.wYear << endl
			<< localTime.wHour << ":" << localTime.wMinute << endl;

		FileTimeToSystemTime(&accessFile, &UTCtime);
		
		SystemTimeToTzSpecificLocalTime(NULL, &UTCtime, &localTime);
		cout << " Время последнего доступа к файлу: " << endl
			<< localTime.wDay << "." << localTime.wMonth << "." << localTime.wYear << endl
			<< localTime.wHour << ":" << localTime.wMinute << endl;

		FileTimeToSystemTime(&lastWFile, &UTCtime);
		
		SystemTimeToTzSpecificLocalTime(NULL, &UTCtime, &localTime);
		cout << " Время последней записи в файл: " << endl
			<< localTime.wDay << "." << localTime.wMonth << "." << localTime.wYear << endl
			<< localTime.wHour << ":" << localTime.wMinute << endl;
	}
	CloseHandle(handleFile);
	cout << endl;
}


void setFTime() {

	HANDLE handleFile;
	string path;

	FILETIME createTime, accessFile, lastWFile;

	SYSTEMTIME UTCtime, localTime;


	cout << " Введите конечный путь к файлу/каталогу, которому нужно установить временные атрибуты(пример c://newDir//newFile.txt): " << endl;
	cin >> path;

	handleFile = CreateFileA((LPCSTR)path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING | FILE_WRITE_ATTRIBUTES, 0, NULL);
	if (!handleFile)
		cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
	else {
		
		GetFileTime(handleFile, &createTime, &accessFile, &lastWFile);
		GetSystemTimeAsFileTime(&accessFile);

		SetFileTime(handleFile, &createTime, &accessFile, &lastWFile);
		FileTimeToSystemTime(&accessFile, &UTCtime);
		SystemTimeToTzSpecificLocalTime(NULL, &UTCtime, &localTime);

		cout << "Текущее время: " << endl
			<< localTime.wDay << "."<< localTime.wMonth << "." << localTime.wYear << endl
			<< localTime.wHour << ":"<< localTime.wMinute << endl
			<< "установлено временем последнего доступа к файлу" << endl;
	}
	CloseHandle(handleFile);
	cout << endl;
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
