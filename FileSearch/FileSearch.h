#ifndef FILESEARCH_H
#define FILESEARCH_H


///////////////////////////////////////////////////////////////////
//  FileSearch.h      -  header file for Filesearch class        //
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
This package performs operations like searching of text in particular files.
This package is capable of searching text or line in particular files as specified
by path.
While searching again, this package takes files and path from map stored in datastore
and search text in those files.
This package also process the inputs(/f<searchtext> <pattern/patterns>) which is 
entered second time in console.


Public Interface:
=================
void textSearchAgain(Store store)                               - allows user to enter search text along with pattern and 
                                                                  controls operations of other functions.
BOOLEAN storeSearchText(std::string searchText)                 - stores the text or line to be searched.
void findText(Store store_, std::string)                        - takes display info and map(where files and path iterators are stored) as arguments 
                                                                  and generates the absolute path and controls he operations of other functions 
																  like fileSearch and filterFiles.
BOOLEAN fileSearch(std::string, std::string)                    - searches text in files and returns true if a particular text is found in file. 
void textSearch(std::string displayString,Store store)          - accepts display string and map(where files and path iterators are stored) 
                                                                  and controls operations of other functions.
BOOLEAN processInputs(std::string text)                         -  process inputs that are entered second time after catalog is developed
                                                                  (/f<searchtext><pattern/patterns>) and dissects patterns and search text.
std::string filterFiles(std::vector<std::string> strPatternsandText_,std::string file)   - filter the files according to pattern mentioned.
BOOLEAN processPatterns                                         - process patterns and returns true if a pattern is valid
void PatternSeparation(BOOLEAN patternSeparationFlag, std::string patterns)   - Used to separate patterns(if user supplies patterns) and store them in vector

*/
/*Required Files :
*---------------- -
*-DataStore.h , DataStore.cpp , FileSystem.h , FileSystem.cpp , FileSearch.h , FileSearch.cpp , Display.h , Display.cpp
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
#include<vector>
#include"..//DemoProject/DataStore.h"
#include"..//FileSystem/FileSystem.h"
#include"..//Display/Display.h"
#include<regex>
class FileSearch
{
public:
	using Path = const std::string;
	using list = std::list < std::string >;
	using vector = std::vector < std::string >;
	using Paths = std::set < Path >;
	using PathIter = Paths::iterator;
	using ListOfiters = std::list < PathIter >;
	using File = std::string;
	using Store = std::map < File, ListOfiters >;

	void textSearchAgain(Store store);
	BOOLEAN storeSearchText(std::string searchText);
	void findText(Store store_, std::string);
	BOOLEAN fileSearch(std::string, std::string);
	void textSearch(std::string displayString,Store store);
	BOOLEAN processInputs(std::string text);
	FileSearch(DataStore &ds,Display &dp);
	std::string filterFiles(std::vector<std::string> strPatternsandText_,std::string file);
	BOOLEAN processPatterns();
	void PatternSeparation(BOOLEAN patternSeparationFlag, std::string patterns);

private:
	std::string searchString;
	std::vector<std::string> patternsVector;
	DataStore &dsr_;
	Display &dp_;
	BOOLEAN booleanFindFlag = false;
};


#endif