#include <windows.h>
#include <string>
#include <iostream>
#include<dirent.h>
using namespace std;;

string Dir() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

void addCurrentDir() {
    struct dirent *d;
    DIR *dr;
    dr = opendir(".");
	cout << "List of file in current directory: " + Dir()<< endl;
    if (dr != NULL){
        for(d = readdir(dr); d != NULL; d = readdir(dr)){
            cout << d->d_name << endl;
        }
        closedir(dr);
    } else {
    	cout << "Error Occurred!";
    }
}
