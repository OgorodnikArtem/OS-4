//////#include <windows.h>
//////#include <conio.h>
//////#include <iostream>
//////#include <fstream>
//////#include <string>
//////
//////int main()
//////{
//////	HANDLE new_message_prepared = CreateEvent(NULL, TRUE, TRUE, (LPCWSTR)"NEW_MESSAGE");
//////	HANDLE* events;
//////	events = new HANDLE[3];
//////	std::string s = "Event_0";
//////	for (int i = 0; i < 3; ++i)
//////	{
//////		events[i] = CreateEvent(NULL, TRUE, FALSE, (LPCWSTR)s.c_str());
//////		s[s.size() - 1]++;
//////	}
//////
//////	HANDLE semaphore;
//////	HANDLE end_semaphore;
//////	semaphore = CreateSemaphore(NULL, 3, 3, (LPCWSTR)"Parent activated process");
//////	end_semaphore = CreateSemaphore(NULL, -2, 1, (LPCWSTR)"Parent ended event");
//////
//////	int n, open_count;
//////	std::cout << "Enter count of processes Parent: ";
//////	std::cin >> n;
//////	open_count = n;
//////	char lpszAppName[] = "ParentProcess.exe";
//////
//////	int count_of_messages;
//////	std::cout << "Enter count of messages to parent: ";
//////	std::cin >> count_of_messages;
//////
//////	STARTUPINFO* si = new STARTUPINFO[n];
//////	PROCESS_INFORMATION* piApp = new PROCESS_INFORMATION[n];
//////
//////	for (int i = 0; i < n; ++i)
//////	{
//////		ZeroMemory(&(si[i]), sizeof(STARTUPINFO));
//////		if (!CreateProcessA(nullptr, lpszAppName, nullptr, nullptr, FALSE,
//////			CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFOA) & (si[i]), &(piApp[i])))
//////		{
//////			_cputs("The new process is not created.\n");
//////			_cputs("Check a name of the process.\n");
//////			_cputs("Press any key to finish.\n");
//////			_getch();
//////			return 0;
//////		}
//////	}
//////
//////	std::string EventSequence;
//////	std::cout << "Enter message:\n\'A\': Enable event 0\n\'B\': Enable event 0\n\'c_1\': close some (3) processes\n";
//////	std::cin >> EventSequence;
//////	std::string message;
//////	std::ofstream fout;
//////	for (int i = 0; i < count_of_messages; ++i)
//////	{
//////		fout.open("Exchanger_1.txt");
//////		std::cin >> message;
//////		switch (EventSequence[i])
//////		{
//////		case 'A':
//////			fout << "Event A send next message: " + message;
//////			fout.close();
//////			ResetEvent(new_message_prepared);
//////			SetEvent(events[0]);
//////			WaitForSingleObject(end_semaphore, INFINITE);
//////			WaitForSingleObject(end_semaphore, 0);
//////			WaitForSingleObject(end_semaphore, 0);
//////			ResetEvent(events[0]);
//////			break;
//////			{
//////		case 'B':
//////			fout << "Event B send next message: " + message;
//////			fout.close();
//////			ResetEvent(new_message_prepared);
//////			SetEvent(events[0]);
//////			WaitForSingleObject(end_semaphore, INFINITE);
//////			WaitForSingleObject(end_semaphore, 0);
//////			WaitForSingleObject(end_semaphore, 0);
//////			ResetEvent(events[0]);
//////			break;
//////		case 'c_1':
//////			open_count -= 3;
//////			fout << "Exit event send next message: " + message;
//////			fout.close();
//////			ResetEvent(new_message_prepared);
//////			SetEvent(events[2]);
//////			WaitForSingleObject(end_semaphore, INFINITE);
//////			WaitForSingleObject(end_semaphore, 0);
//////			WaitForSingleObject(end_semaphore, 0);
//////			ResetEvent(events[2]);
//////			break;
//////		default:
//////			break;
//////			}
//////
//////			Sleep(50);
//////			SetEvent(new_message_prepared);
//////			if (open_count < 3)
//////			{
//////				break;
//////			}
//////		}
//////
//////		fout.open("Exchanger_1.txt");
//////		fout << "All messages have been forwarded, press any key, to close process...";
//////		fout.close();
//////
//////
//////
//////
//////		HANDLE mutex;
//////		HANDLE end_mutex;
//////		mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"Child activated process");
//////		end_mutex = CreateMutex(NULL, FALSE, (LPCWSTR)"Child ended event");
//////
//////		int n, open_count_;
//////		std::cout << "Enter count of processes Child: ";
//////		std::cin >> n;
//////		open_count_ = n;
//////		char lpszAppName_[] = "ChildProcess.exe";
//////
//////		int count_of_messages_;
//////		std::cout << "Enter count of messages to child: ";
//////		std::cin >> count_of_messages_;
//////
//////		STARTUPINFO* si = new STARTUPINFO[n];
//////		PROCESS_INFORMATION* piApp = new PROCESS_INFORMATION[n];
//////
//////		for (int i = 0; i < n; ++i)
//////		{
//////			ZeroMemory(&(si[i]), sizeof(STARTUPINFO));
//////			if (!CreateProcessA(nullptr, lpszAppName_, nullptr, nullptr, FALSE,
//////				CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFOA) & (si[i]), &(piApp[i])))
//////			{
//////				_cputs("The new process is not created.\n");
//////				_cputs("Check a name of the process.\n");
//////				_cputs("Press any key to finish.\n");
//////				_getch();
//////				return 0;
//////			}
//////		}
//////
//////		std::string EventSequence_;
//////		std::cout << "Enter message:\n\'A\': Enable event 0\n\'B\': Enable event 0\n\'c_1\': Close some (3) processes\n";
//////		std::cin >> EventSequence_;
//////		std::string message_;
//////		std::ofstream fout_;
//////		for (int i = 0; i < count_of_messages_; ++i)
//////		{
//////			fout_.open("Exchanger_2.txt");
//////			std::cin >> message_;
//////			switch (EventSequence_[i])
//////			{
//////			case 'A':
//////				fout_ << "Event A send next message: " + message_;
//////				fout_.close();
//////				ResetEvent(new_message_prepared);
//////				SetEvent(events[1]);
//////				WaitForSingleObject(end_mutex, INFINITE);
//////				WaitForSingleObject(end_mutex, 0);
//////				WaitForSingleObject(end_mutex, 0);
//////				ResetEvent(events[1]);
//////			case 'B':
//////				fout_ << "Event B send next message: " + message_;
//////				fout_.close();
//////				ResetEvent(new_message_prepared);
//////				SetEvent(events[1]);
//////				WaitForSingleObject(end_mutex, INFINITE);
//////				WaitForSingleObject(end_mutex, 0);
//////				WaitForSingleObject(end_mutex, 0);
//////				ResetEvent(events[1]);
//////				break;
//////			case 'c_1':
//////				open_count_ -= 3;
//////				fout << "Exit event send next message: " + message;
//////				fout.close();
//////				ResetEvent(new_message_prepared);
//////				SetEvent(events[2]);
//////				WaitForSingleObject(end_mutex, INFINITE);
//////				WaitForSingleObject(end_mutex, 0);
//////				WaitForSingleObject(end_mutex, 0);
//////				ResetEvent(events[2]);
//////				break;
//////			default:
//////				break;
//////			}
//////
//////			Sleep(50);
//////			SetEvent(new_message_prepared);
//////			if (open_count_ < 3)
//////			{
//////				break;
//////			}
//////		}
//////
//////		fout.open("Exchanger_2.txt");
//////		fout << "All messages have been forwarded, press any key, to close process...";
//////		fout.close();
//////		SetEvent(events[2]);
//////		SetEvent(new_message_prepared);
//////		for (int i = 0; i < n; ++i)
//////		{
//////			WaitForSingleObject(piApp[i].hProcess, INFINITE);
//////			CloseHandle(piApp[i].hThread);
//////			CloseHandle(piApp[i].hProcess);
//////		}
//////
//////		CloseHandle(semaphore);
//////		CloseHandle(end_semaphore);
//////
//////		CloseHandle(mutex);
//////		CloseHandle(end_mutex);
//////
//////		for (int i = 0; i < 3; ++i)
//////		{
//////			CloseHandle(events[i]);
//////		}
//////
//////		delete[] events;
//////		return 0;
//////	}
//////}
////
////
////
////
////
////
////
////
////
////
////
////
#include <iostream>
#include <windows.h>
#include <string>
HANDLE A, B, c_2, c_1, semafor;
using namespace std;

int main()
{

	HANDLE mutex;
	semafor = CreateSemaphore(NULL, 1, 1, (LPSTR)"semafor");

	A = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"A");
	B = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"B");

	c_2 = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"c_2");
	c_1 = CreateEvent(NULL, FALSE, FALSE, (LPSTR)"c_1");

	mutex = CreateMutex(NULL, FALSE, (LPSTR)"mutex");

	int countof;
	int countof_;
	cout << "Enter the number of all parent processes ";
	cin >> countof;
	cout << "Enter the number of all chiled processes ";
	cin >> countof_;
	cout << endl;

	int count;
	int count_;
	cout << "Enter the number of Parents ";
	cin >> count;
	cout << "Enter the number of Child ";
	cin >> count_;
	cout << endl;

	char lpszAppName[] = "ParentProcess.exe";
	char lpszAppName_[] = "ChildProcess.exe";


	char countAsString[20];
	sprintf_s(countAsString, "%d", count);
	char args[100];
	sprintf_s(args, "%s %s", lpszAppName, countAsString);


	char countAsString_[20];
	sprintf_s(countAsString_, "%d", count_);
	char args_[100];
	sprintf_s(args_, "%s %s", lpszAppName_, countAsString_);

	STARTUPINFO* si = new STARTUPINFO[countof];
	PROCESS_INFORMATION* piApp = new PROCESS_INFORMATION[countof];
	HANDLE* a = new HANDLE[countof];
	STARTUPINFO* si1 = new STARTUPINFO[countof_];
	PROCESS_INFORMATION* piApp1 = new PROCESS_INFORMATION[countof_];
	HANDLE* a1 = new HANDLE[countof_];


	for (int i = 0; i < countof; i++) {
		ZeroMemory(&si[i], sizeof(STARTUPINFO));
		si[i].cb = sizeof(STARTUPINFO);
		if (!CreateProcess(NULL, args, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, (LPSTARTUPINFOA)&si[i], &piApp[i]))
		{
			cout << "The new Parent process is not created.\n";
			return 0;
		}
		a[i] = piApp[i].hProcess;
		Sleep(100);
	}


	for (int i = 0; i < countof_; i++)
	{
		ZeroMemory(&si1[i], sizeof(STARTUPINFO));
		si1[i].cb = sizeof(STARTUPINFO);
		if (!CreateProcess(NULL, args_, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, (LPSTARTUPINFOA)&si1[i], &piApp1[i]))
		{
			cout << "The new Child process is not created.\n";
			return 0;
		}
		a1[i] = piApp1[i].hProcess;
		Sleep(100);
	}


	int i = 0;

	while (true)
	{
		if (WaitForSingleObject(c_2, 0) == WAIT_OBJECT_0 or WaitForSingleObject(c_1, 0)) {

			if (WaitForSingleObject(A, 0) == WAIT_OBJECT_0)
			{
				i++;
				cout << "Parent process shows message A" << endl;
			}
			if (WaitForSingleObject(B, 0) == WAIT_OBJECT_0)
			{
				i++;
				cout << "Child process shows message B" << endl;
			}
		}

		if (i >= count * countof + count_ * countof_)
		{
			break;
		}
	}

	return 0;
}