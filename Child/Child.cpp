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
//////
//////	HANDLE mutex;
//////	HANDLE end_mutex;
//////	mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"Child activated process");
//////	end_mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"Child ended event");
//////
//////	for (int i = 0; i < 3; ++i)
//////	{
//////		events[i] = OpenEvent(EVENT_ALL_ACCESS, TRUE, (LPCWSTR)s.c_str());
//////		s[s.size() - 1]++;
//////	}
//////	WaitForSingleObject(mutex, INFINITE);
//////	bool q = 0;
//////	std::ifstream fin;
//////	while (!q)
//////	{
//////		WaitForSingleObject(new_message_prepared, INFINITE);
//////		switch (WaitForMultipleObjects(3, events, FALSE, INFINITE) - WAIT_OBJECT_0)
//////		{
//////		case 1:
//////			fin.open("Exchanger_2.txt");
//////			getline(fin, s);
//////			std::cout << s << '\n';
//////			fin.close();
//////			ReleaseSemaphore(end_mutex, 1, NULL);
//////			break;
//////		case 2:
//////			fin.open("Exchanger_2.txt");
//////			getline(fin, s);
//////			std::cout << s << '\n';
//////			fin.close();
//////			ReleaseSemaphore(end_mutex, 1, NULL);
//////			break;
//////
//////		case 3:
//////			fin.open("Exchanger_2.txt");
//////			getline(fin, s);
//////			std::cout << s;
//////			std::cout << "\npress any key, to close process...";
//////			q = 1;
//////			fin.close();
//////			ReleaseSemaphore(mutex, 1, NULL);
//////			_getch();
//////			ReleaseSemaphore(end_mutex, 1, NULL);
//////			return 0;
//////			break;
//////		default:
//////			break;
//////		}
//////	}
//////	_getch();
//////	ReleaseSemaphore(mutex, 1, NULL);
//////	return 0;
//////}
////
////
////
////
////
#include <iostream>
#include <windows.h>
#include <string>
HANDLE  B, c_2;
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE mutex;
	B = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"B");
	c_2 = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"c_2");
	mutex = OpenMutex(SYNCHRONIZE, FALSE, (LPSTR)"mutex");


	int count_ = std::stoi(argv[1]);

	//Использование значения count
	std::cout << "count: " << count_ << std::endl;







	if (B == NULL)
		return GetLastError();
	if (c_2 == NULL)
		return GetLastError();
	if (mutex == NULL)
	{
		cout << "Create mutex failed." << endl;
		cout << "Press any key to exit." << endl;
		cin.get();
		return GetLastError();
	}

	WaitForSingleObject(mutex, INFINITE);
	for(int i = 0; i < count_ ; i++){
		cout << "Enter the message: ";
		char d;
		cin >> d;
	if (d == 'B')
	{
		SetEvent(B);
	}
	
	}SetEvent(c_2);
	ReleaseMutex(mutex);
	CloseHandle(c_2);
	CloseHandle(B);
	return 0;
}