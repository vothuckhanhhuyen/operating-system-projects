#include <windows.h>
#include <bits/stdc++.h>
#include <string.h>
#include <vector>
#include <thread>
#include <chrono>
#include <tlhelp32.h>
#include <tchar.h>
#include <debugapi.h>
#include <processthreadsapi.h>
#include <fstream>
#include "bibrary.h"
#include "currentDir.h"
#include "messenger.h"
#include "concurentCommandBuilder.h"


using namespace std;

const string EXIT_COMMAND = "exit";
string currentDirectory;

void runable(string command)
{

    void time1();
    void date();
    void time2();
    if (command.compare("help") == 0)
    {
        help();
    }

    else if (command.compare("exit") == 0)
    {
        GOODBYE;
        printf("Sending signal to kill all child processes ...\n");
        kill_All();
        this_thread::sleep_for(chrono::milliseconds(800));
        exit(0);
    }

    else if (command.compare("notepad back") == 0 || command.compare("notepad fore") == 0)
    {
        print("Hello, notepad is running\n");
        openInBackOrFore(command, "c:/windows/system32/notepad.exe");
    }

    else if (command.compare("dir") == 0)
    {
        listOfCurrent();
    }

    else if (command.compare("date") == 0){
        HANDLE h1;   
        DWORD ThreadId;
        h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)date, NULL, 0, &ThreadId);
        cin.get();
        TerminateThread(h1, 0);
        CloseHandle(h1);
    }

    else if (command.compare("time") == 0) {
        HANDLE h1;   
        DWORD ThreadId;
        h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)time1, NULL, 0, &ThreadId);
        cin.get();
        TerminateThread(h1, 0);
        CloseHandle(h1);
    }
    
    else if (command.compare("clock") == 0) {
        HANDLE h1;   
        DWORD ThreadId;
        h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)time2, NULL, 0, &ThreadId);
        cin.get();
        TerminateThread(h1, 0);
        CloseHandle(h1);    	
    }

	else if (command.compare("countdown fore") == 0 || command.compare("countdown back") == 0)
    {
            print("Hello, countdown clock is running\n");
            openInBackOrFore(command, "countDownClock.exe");
    }

    else if (command.compare("list") == 0)
    {

        list1();
    }

    else if (command.compare("clear") == 0)
    {
        system("cls");
    }

    else if (command.length() > 4 && command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
    {
        string s = "";
        for (int i = 3; i <= command.length(); ++i)
        {
            s += command[i];
        }
        cd(s);
    }

    else if (command.length() > 4 && command[0] == 'k' && command[1] == 'i' && command[2] == 'l' & command[3] == 'l')
    {
        if (command.length() == 7 && command[5] == '-' && command[6] == '1')
        {
            kill_All();
        }
        else
        {
            string s = "";
            for (int i = 4; i <= command.length(); ++i)
            {
                s += command[i];
            }
            kill(s);
        }
    }

    else if (command.length() > 4 && command[0] == 's' && command[1] == 't' && command[2] == 'o' & command[3] == 'p') {
        string s = "";
            for (int i = 4; i <= command.length(); ++i)
            {
                s += command[i];
            }
            stop(s);
    }

    else if (command.length() > 6 && command[0] == 'r' && command[1] == 'e' && command[2] == 's' & command[3] == 'u' && command[4] == 'm' && command[5] == 'e') {
        string s = "";
            for (int i = 6; i <= command.length(); ++i)
            {
                s += command[i];
            }
            resume(s);
    }

    else if (command.find(".bat") != std::string::npos) {
    	runBat(command);
    }
    else if (command[0] == 'e' && command[1] == 'n' && command[2] == 'v'){
    	char envname[command.length() - 4];
    	if (command[3] == '\0') {
    		read_env(NULL);
		}	
		else {
			for (int i = 4; i <= command.length(); i ++) {
				envname[i - 4] = command[i];
			}
			read_env(envname);
		}
	}
	
    else if (command.find("addenv ") != std::string::npos){
		int a;
		for (int i = 7; i< command.length(); i++){
			if(command[i] == ' '){
				a = i + 1;
				break;
			}
		}
		if (a) {
			char envname[a-7];
		char envvalue[command.length() - a + 1];
		for (int i = 7; i < a - 1; i++){
			envname[i - 7] = command[i];
		}
		envname[a - 8] = '\0';
		for (int i = a; i <= command.length(); i ++){
			envvalue[i-a] = command[i];
		}
		add_env(envname, envvalue);
		}
		else {
			cout << "Illegal command!\n";
		}
	}
	
	else if (command.find("delenv ") != std::string::npos){
		char envname[command.length() - 7];
		for (int i = 7; i <= command.length(); i++){
			envname[i - 7] = command[i];
		}
		del_env(envname);
	}
     else if (command.find(".exe") != std::string::npos) {
    	runExe(command);
    }
    else
    {
        printf("Illegal command!\n");
    }
}

void run(string command)
{
    vector<string> jobs;
    jobs = createJobs(command);
    for (int i = 0; i < jobs.size(); ++i)
    {
        runable(trim(jobs[i]));
    }
}

int main()
{
    WELCOME();
    string command;
    while (true)
    {
        
        cout << "> ";
        getline(cin, command);
        trim(command);
        if (command == EXIT_COMMAND)
        {
            GOODBYE();
            printf("Sending signal to kill all child processes ...\n");
            kill_All();
            break;
        }
        else
        {
            run(command);
        }
    }
    
}

