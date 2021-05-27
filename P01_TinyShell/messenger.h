#include <windows.h>
#include<bits/stdc++.h>
#include <string>
#include <iostream>

using namespace std;

void WELCOME() 
{
	cout << "_______________________________________________________________________________________________________________________\n";
    cout << "                                        Welcome to the MyShell command line!\n";
    cout << "_______________________________________________________________________________________________________________________\n";
    cout << "                                     T.H.Binh, T.T.Hiep, L.H.Hoang, V.T.K.Huyen\n";
    cout << "_______________________________________________________________________________________________________________________\n";
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
