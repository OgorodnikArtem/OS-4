//////#include <windows.h>
//////#include <conio.h>
//////#include <iostream>
//////#include <fstream>
//////#include <string>
//////
//////int main()
//////{
//////	HANDLE new_message_prepared = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)"NEW_MESSAGE");
//////	HANDLE* events;
//////	events = new HANDLE[3];
//////	std::string s = "Event_0";
//////
//////	HANDLE semaphore;
//////	HANDLE end_semaphore;
//////	semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, (LPCWSTR)"Parent activated process");
//////	end_semaphore = OpenSemaphore(SEMAPHORE_MODIFY_STATE, TRUE, (LPCWSTR)"Parent ended event");
//////
//////	for (int i = 0; i < 3; ++i)
//////	{
//////		events[i] = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)s.c_str());
//////		s[s.size() - 1]++;
//////	}
//////	WaitForSingleObject(semaphore, INFINITE);
//////	bool q = 0;
//////	std::ifstream fin;
//////	while (!q)
//////	{
//////		WaitForSingleObject(new_message_prepared, INFINITE);
//////		switch (WaitForMultipleObjects(3, events, FALSE, INFINITE) - WAIT_OBJECT_0)
//////		{
//////		case 1:
//////			fin.open("Exchanger_1.txt");
//////			getline(fin, s);
//////			std::cout << s << '\n';
//////			fin.close();
//////			ReleaseSemaphore(end_semaphore, 1, NULL);
//////			break;
//////		case 2:
//////			fin.open("Exchanger_1.txt");
//////			getline(fin, s);
//////			std::cout << s << '\n';
//////			fin.close();
//////			ReleaseSemaphore(end_semaphore, 1, NULL);
//////			break;
//////
//////		case 3:
//////			fin.open("Exchanger_1.txt");
//////			getline(fin, s);
//////			std::cout << s;
//////			std::cout << "\npress any key, to close process...";
//////			q = 1;
//////			fin.close();
//////			ReleaseSemaphore(semaphore, 1, NULL);
//////			_getch();
//////			ReleaseSemaphore(end_semaphore, 1, NULL);
//////			return 0;
//////			break;
//////		default:
//////			break;
//////		}
//////	}
//////	_getch();
//////	ReleaseSemaphore(semaphore, 1, NULL);
//////	return 0;
//////}
////
////
////
////
////
////
#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>
HANDLE semafor, A, c_1;
CRITICAL_SECTION A_;
using namespace std;

int main(int argc, char* argv[])
{



	/*if (argc != 2) {
		std::cout << "Using: " << argv[0] << " <count>" << std::endl;
		return 1;
	}*/

	//Получение переданного значения count из аргументов командной строки
	int count = std::stoi(argv[1]);

	//Использование значения count
	std::cout << "count: " << count << std::endl;

	semafor = CreateSemaphore(NULL, 1, 1, (LPSTR)"semafor");
	A = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"A");
	c_1 = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"c_1");

	if (A == NULL)
		return GetLastError();
	if (c_1 == NULL)
		return GetLastError();
	if (semafor == NULL)
	{
		cout << "Create semafor failed." << endl;
		cout << "Press any key to exit." << endl;
		cin.get();
		return GetLastError();
	}
	
	
	WaitForSingleObject(semafor, INFINITE);

	for (int i = 0; i < count; i++) {
		cout << "Enter the message: ";
		char d;
		cin >> d;
		if (d == 'A')
		{
			SetEvent(A);
		}
	//	SetEvent(c_1);
	}
	ReleaseSemaphore(semafor, 1, NULL);
	SetEvent(c_1);
	CloseHandle(c_1);
	CloseHandle(A);
	return 0;
}
