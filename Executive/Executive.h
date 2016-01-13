#ifndef EXECUTIVE_H
#define EXECUTIVE_H

///////////////////////////////////////////////////////////////////
//  Executive.h      -  header file for Executive class          //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////
/*
Package Operations :
== == == == == == == == =
This package provides the main executive class.It controls all classes present in other packages.
This package accepts input from command line and passes that input to 
appropriate class.

* /
/*Required Files :
*---------------- -
*-DataStore.h , DataStore.cpp , FileSystem.h , FileSystem.cpp , FileSearch.h , FileSearch.cpp , Display.h , Display.cpp
*-FileManager.h , FileManager.cpp , Executive.h , Executive.cpp
*
*  Build Command :
*----------------
*    devenv DemoProject.sln / rebuild debug
*
*  Maintenance History :
*----------------------
*Ver 2.0 : 9 Feb 15
* -second release
*Ver 1.0 : 6 Feb 15
* -first release
*/


#include<iostream>
#include"..//FileManager/FileManager.h"
#include"..//Display/Display.h"
#include <exception>

class Executive
{
public:
	using vector = std::vector < std::string > ;
	Executive::Executive(FileManager &fm, Display &dp, DataStore &ds, FileSearch &fs);

private:
	FileManager &file;
	Display &display;
	DataStore &dStore;
	FileSearch &fileSearch;
	
};



#endif EXECUTIVE_H

