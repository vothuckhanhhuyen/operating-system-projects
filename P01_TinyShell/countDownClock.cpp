#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <tlhelp32.h> 
#include <vector>
#include <tchar.h>
#include <debugapi.h>
#include <processthreadsapi.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsExApp";
int timer = 10;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI 
WinMain (HINSTANCE hThisInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpszArgument,
        int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
	UINT myTimer;
	
	/* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW +1);
	
	   /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_CLIENTEDGE,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Count down",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           240,                 /* The programs width */
           240,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
	
	 /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    myTimer = SetTimer(hwnd, 0, 1000, NULL);
    
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
  HDC hdc; 
  PAINTSTRUCT ps; 
  RECT r	; 
  char szBuffer[200]; 
  static int count = 120; 
  int seconds = 0;
  int minutes = 0;
  int hours  = 0;

  switch (message) { 
  case WM_CREATE: 
    // create a 1 second timer 
    SetTimer (hwnd, 0, 1000, NULL); 
    return 0;      

  case WM_PAINT:
    if(count > 0)
    {
        hdc = BeginPaint (hwnd, &ps); 
        GetClientRect (hwnd, &r);
        seconds = count ;
        wsprintf (szBuffer, "\n\n\n\n%hd", seconds); 
        DrawText (hdc, szBuffer, -1, &r, DT_CENTER); 
        EndPaint (hwnd, &ps); 
    }
    else
    {
        SendMessage (hwnd, WM_CLOSE, 0, 0L);
    }
    return 0; 

  case WM_TIMER: 
    count--;       
    InvalidateRect (hwnd, NULL, TRUE);
    return 0;        

  case WM_DESTROY: 
    KillTimer (hwnd, 0); 
    PostQuitMessage (0); 
  default :
  	return DefWindowProc(hwnd, message, wParam, lParam);
    return 0; 
  }  /* end switch */ 
} 
