#include <windows.h>
#include<bits/stdc++.h>
#include <string>
#include <iostream>

using namespace std;

void WELCOME() 
{
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
    cout << "                                        Welcome to the MyShell command line!\n";
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    cout << "                                     T.H.Binh, T.T.Hiep, L.H.Hoang, V.T.K.Huyen\n";
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
} 

void GOODBYE() 
{
    cout << "Thank you for using the MyShell command line. Goodbye!\n";
}

void COMMAND_NOT_FOUND(string command) 
{
    cout << "The command " + command + " was not recognized.\n";
}

void CANNOT_HAVE_PARAMETER(string command) 
{
    cout << "The command " + command + " cannot have parameters.\n";
}

void CANNOT_HAVE_OUTPUT(string command) 
{
    cout << "The command " + command + " cannot have an output.\n";
}

void CANNOT_HAVE_INPUT(string command) 
{
    cout << "The command " + command + " cannot have an input.\n";
}
