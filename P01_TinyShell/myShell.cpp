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
#include "messenger.h"
#include "concurentCommandBuilder.h"

using namespace std;

const string EXIT_COMMAND = "exit";
string currentDirectory = "";
vector<string> history;

void runable(string command)
{

    void time1();
    void date();
    void time2();
    
    if (command.compare("help") == 0)
    {
        help();
    }

    else if (command.compare("history") == 0)
    {
        int i = 0;
        for (string s: history){
            if (s != "history"){
                i++;
                cout << i << ". "<< s << endl;
            }
        }
        if (i == 0)
            cout << "Empty history!" << endl;
    }

    else if (command.compare("clean") == 0)
    {
        history.clear();
        cout << "Your history has been cleaned thoroughly!" << endl;
    }

    else if (command.compare("exit") == 0)
    {
        GOODBYE;
        printf("Sending signal to kill all child processes ...\n");
        kill_All();
        Sleep(1);
        //this_thread::sleep_for(chrono::milliseconds(800));
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
            string s = currentDirectory + "\\countDownClock.exe";
            openInBackOrFore(command, s);
    }

    else if (command.compare("list") == 0)
    {

        list1();
    }

    else if (command.compare("clear") == 0)
    {
        system("cls");
    }

    else if (command.length() >= 4 && command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
    {
        string s = "";
        for (int i = 3; i < command.length(); ++i)
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
    	string s = currentDirectory + "\\" + command;
    	runBat(s);
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
	
    else if (command.find("addenv (") != std::string::npos){
		int a;
		int b = 1;
		for (int i = 8; i< command.length(); i++){
			if(command[i] == '(') b ++;
			if(command[i] == ')') b --;
			if(b == 0) {
				a = i + 2;
				break;
			}
		}
		if(b > 0) {
			cout << "Syntax error\n";
		}
		else {
			if (command[a - 1] == ' ') {
				char envname[a - 9];
				char envvalue[command.length() - a + 1];
				for (int i = 8; i < a - 2; i++){
					envname[i - 8] = command[i];
				}
				envname[a - 10] = '\0';
				for (int i = a; i <= command.length(); i ++){
					envvalue[i-a] = command[i];
				}
				add_env(envname, envvalue);
			}
			else {
				cout << "Illegal command!\n";
			}	
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
        command.append(" -> Illegal command");
    }
    history.push_back(command);
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
    char *buffer1 = _getcwd(NULL, 0);
    int i = 0;
        while(buffer1[i] != '\0') {
            currentDirectory += buffer1[i];
            i++;
        }
    while (true)
    {
    	char *buffer = _getcwd(NULL, 0);    
    	printf("%s", buffer);
        cout << ">";
        getline(cin, command);
        trim(command);
        if (command == EXIT_COMMAND)
        {
            GOODBYE();
            printf("Sending signal to kill all child processes ...\n");
            kill_All();
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;
        }
        else
        {
            run(command);
        }
    }
    
}

void time1()
{
    int sec_prev=0; 
    while(1)
    {
        int seconds, minutes, hours;
        string str;

        //storing total seconds
        time_t total_seconds=time(0);

        //getting values of seconds, minutes and hours
        struct tm* ct = localtime(&total_seconds);

        seconds=ct->tm_sec;
        minutes=ct->tm_min;
        hours=ct->tm_hour;

        //converting it into 12 hour format
        /*if(hours>=12)
            str="PM";
        else
            str="AM";
        hours=hours>12?hours-12:hours;  */


        //printing the result
        if(seconds==sec_prev+1 || (sec_prev==59 && seconds==0))
        {
            cout << '\r';
            cout<< (hours<10?"0":"") << hours <<":" << (minutes<10?"0":"") << minutes << ":" << (seconds<10?"0":"") << seconds << " " << str;
        }

        sec_prev=seconds;

    }
}

void date()
{
    int sec_prev=0; //save previous second
    while(1){
        int seconds, minutes, hours;
        int days, months, years;
        int weekdays;
        string wday[] = {            
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };
        string str;

        //storing total seconds
        time_t total_seconds=time(0);

        //getting values of seconds, minutes and hours
        struct tm* ct = localtime(&total_seconds);

        seconds=ct->tm_sec;
        minutes=ct->tm_min;
        hours=ct->tm_hour;
        days = ct->tm_mday;
        months = ct->tm_mon + 1;
        years = ct ->tm_year + 1900;    //in struct ct, tm_year beginning at 1900
        weekdays = ct->tm_wday; //beginning at Sunday

        //converting it into 12 hour format
        if(hours>=12)
            str="PM";
        else
            str="AM";
        hours=hours>12?hours-12:hours;

        //printing the result
        if(seconds==sec_prev+1 || (sec_prev==59 && seconds==0))
        {
            cout << '\r';
            cout << wday[weekdays] << " ";
            cout<< (hours<10?"0":"") << hours <<":" << (minutes<10?"0":"") << minutes << ":" << (seconds<10?"0":"") << seconds << " " << str;
            cout<<'\t' <<(days<10?"0":"") << days <<"/" << (months<10?"0":"") << months << "/" << (years<10?"0":"") << years;
        }

        sec_prev=seconds;
    }
}
    
void time2()
{
    int sec_prev = 0;
    while (1)
    {
        int seconds, minutes, hours;
        string str;

        time_t total_seconds = time(0);            // storing total seconds
        struct tm *ct = localtime(&total_seconds); // getting values of seconds, minutes and hours

        seconds = ct->tm_sec;
        minutes = ct->tm_min;
        hours = ct->tm_hour;

        //printing the result

        if (seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
        {
            system("cls");
            cout << "       ,--.-----.--." << endl;
            cout << "       |--|-----|--|" << endl;
            cout << "       |--|     |--|" << endl;
            cout << "       |  |-----|  |" << endl;
            cout << "     _|--|     |--|_" << endl;
            cout << "    /  |  |-----|  |  \\" << endl;
            cout << "   /   \\__|-----|__/   \\" << endl;
            cout << "  /   _____---_____   \\/\\" << endl;
            cout << " /   /               \\   \\/" << endl;
            cout << "{   /      ROLEX      \\   }" << endl;
            cout << "|  {                   }  |-," << endl;

            cout << (hours < 10 ? "|  |    0" : "|  |    ") << hours << (minutes < 10 ? " : 0" : " : ") << minutes
                 << (seconds < 10 ? " : 0" : " : ") << seconds << "   |  | |" << endl;

            cout << "|  {                   }  |-'" << endl;
            cout << "{   \\                 /   }" << endl;
            cout << " \\   `------___------'   /\\ " << endl;
            cout << "  \\     _|-----|_     /\\/" << endl;
            cout << "   \\   /  |-----|  \\   /" << endl;
            cout << "    \\  |--|     |--|  /" << endl;
            cout << "     --|  |-----|  |--" << endl;
            cout << "       |--|     |--|" << endl;
            cout << "       |--|-----|--|" << endl;
            cout << "       `--'-----`--'" << endl;
        }
        sec_prev = seconds;
    }
}
