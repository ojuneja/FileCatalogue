#ifndef FILEMANAGER_H
#define FILEMANAGER_H

///////////////////////////////////////////////////////////////////
//  FileManager.h      -  header file for FileManager class      //
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
Package Operations:
=================
This package performs operations like processing inputs and dissect valid inputs 
properly and also search files in directories and subdirectories.
The package uses flag approach.
All the options and patterns are processed first and then flags are set and display
information needed for display package is stored.
Then,particular operation is performed only if its flag is true.
The operations are performed then and appropriate files and paths are stored in datastore.
This package is responsile for developing searching in directories and developing file catalog.


Public Interface:
=================
void addFilePattern(const std::string& patt)                                                 - process and add patterns to vector
void findDirectoriesAndSubdirectories(const std::string &path,const std::string pattern)     - accepts path and pattern as arguments and search files 
                                                                                               in the directories and subdirectories present in that path 
																							   and develops catalog by saving in datastore.
std::string search                                                                           - acts as entry point function for all functions.
                                                                                               allow other functions to perform its task if its flag is
																							   true and returns display information.
void processInput                                                                            - process input and dissects valid options(/s /d /f),patterns
                                                                                               and then stores in particular function or in some container.
void processOptionsAndPatterns(list)                                                         - process options(/s /d /f) and sets appropriate flags as 
                                                                                               true.Also specifies display info needed for display package. 
void clearOptionandPatternsVector                                                            - resets options and patterns vector
void resetflags                                                                              - resets all flags(subdirectories,directories,search,
                                                                                               duplicate flag) as false
void findDirectories(const std::string &path, const std::string pattern)                     - accepts path and pattern as arguments and search files 
                                                                                               only in directory of that path 
																							   and develops catalog by saving in datastore.
*/
/*Required Files :
*---------------- -
*-DataStore.h , DataStore.cpp , FileSystem.h , FileSystem.cpp , FileSearch.h , FileSearch.cpp , FileManager.h , FileManager.cpp , Display.h , Display.cpp
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


#include<vector>
#include<iostream>
#include"..//DemoProject/DataStore.h"
#include"..//FileSystem/FileSystem.h"
#include"..//Display/Display.h"
#include"..//FileSearch/FileSearch.h"
#include<fstream>
#include<regex>

class FileManager{

public:
	using Path = const std::string;
	using list = std::list < std::string > ;
	using vector = std::vector < std::string >;
	using Paths = std::set < Path >;
	using PathIter = Paths::iterator;
	using ListOfiters = std::list < PathIter >;
	using File = std::string;
	using Store = std::map < File, ListOfiters >;
	using patterns = std::vector < std::string > ;
	using options = std::vector < std::string > ;
	
	void addFilePattern(const std::string& patt);
	void findDirectoriesAndSubdirectories(const std::string &path,const std::string pattern);
	std::string search();
	FileManager(const std::string& path, DataStore& ds,std::vector<std::string>& vector,FileSearch &fs,Display &dp);
	void processInput();
	void processOptionsAndPatterns(list);
	void clearOptionandPatternsVector();
	void resetflags();
	void findDirectories(const std::string &path, const std::string pattern);
private:
	list listOfOptions;
	std::string path_;
	DataStore &store_;
	patterns patterns_;
	options& optionsVector_;
	vector::iterator processIterator;
	boolean subdirectoriesFlag = false;
	boolean duplicateFlag = false;
	boolean searchFlag = false;
	boolean invalidFlag = false;
	boolean directoryFlag = false;
	boolean NoPushFlag = false;
	std::string searchString;
	std::string displayString = "display";
	FileSearch &fs_;
	Display &dp_;
};


#endif