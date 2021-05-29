# Welcome to our TinyShell

## Introduction
TinyShell is a basic shell written in C++ programming language. The way it works is similar in "PowerShell", but simpler. There are some basic commands such as starting, pausing or ending a process, executing *.bat or *.exe files, etc.

## Aims
+ Research the process management APIs in Windows
+ Understand how to set and how shell works

## Contribute
Class: Talented in Computer Science - K64
+ Trần Trọng Hiệp
+ Tạ Hữu Bình
+ Lê Huy Hoàng
+ Võ Thục Khánh Huyền

## Table of contents
1. [Introduction](#Introduction)
2. [Aims](#Aims)
3. [Contribute](#Contribute)
4. [Commands](#Commands)
    + [Mode](#Mode)
    + [Process management commands](#Process-management-commands-in-background-mode)
    + [Excute *.bat and *.exe files](#Excute-bat-and-exe-files)
    + [Environment variable](#Environment-variables)
    + [Some special commands](#Some-special-commands)

## Commands

### Mode
#### 1. Foreground mode
`Shell must wait for the process to finish`

*Syntax:*
``` 
>countdown back
```
#### 2. Background mode
`Shell and process excute in parallel`

*Sytax:*
``` 
>countdown fore
```

### Process management commands (in background mode) 

#### 1. List
`Print out list of the processes (process Id, Cmd name, status)`

*Syntax:*
```
>list
```
#### 2. Stop
`Stop an running process`

*Syntax:*
```
>stop id_Process
```
#### 3. Resume
`Resume running paused process`

*Syntax:*
```
>resume id_Process
```

#### 4. Kill
`Kill a process (maybe running or stopping)`

*Syntax:*
``` 
>kill id_Process
```
If *id = -1*, kill all the processes
### Excute *.bat and *.exe files

#### 1. *.exe
`Run *.exe file, add foreground or background mode`

*Syntax:*
```
>path_of*.exe mode
```
Example:
```
>C:\Users\Example.exe fore
```
#### 2. *.bat
`Read *.bat file and run list of command lines`

*Syntax:*
```
>path_of*.bat
```
### Environment variables

#### 1. env 
`Display the value of the user environment variable called`

*Syntax:*
```
>env name
```
Exmaple:
```
>env path
```
**Note:** If name = NULL, shell will display the list of the user variables with their values.

#### 2. addenv
`Add an user environment variable`

*Syntax:*
```
>addenv (a) val
```
+ a and val is the name and value of variable you want to add.

#### 3. delenv
`Delete an user environment variable`

*Syntax:*
```
>delenv a
```
+ a is the name of variable you want to delete.

### Some special commands

#### 1. cd
+ `Change the parent directory to the current directory`

*Syntax:*
```
>cd ..
```
+ `Change the parent directory to the specified path`

*Syntax:*
```
>cd path
```
#### 2. dir
`Display the files and folders in parent directory`

*Syntax:*
```
>dir
```
#### 3. date - time - clock
`Display the current date - time - clock

*Syntax:*
```
>date
>time
>clock
```

#### 4. countdown - notepad
`Open the countdown clock or notepad in foreground or background mode`

*Syntax:*
```
>countdown mode
>notepad mode
```
Example:
```
>countdown fore
```
#### 5. clear
`Clear the screen of tinyshell`

*Syntax:*
```
>cls
```

#### 6. exit
`Exit tinyshell`

*Syntax:*
```
>exit
```
## 
