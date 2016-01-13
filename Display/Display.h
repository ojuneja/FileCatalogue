
#ifndef DISPLAY_H
#define DISPLAY_H

///////////////////////////////////////////////////////////////////
//  Display.h      -  header file for Display class              //
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
This package provides a display class for our project-File Catalog
Different packages performs operations and then searches
appropriate list of files and their iterators(which provides
access to their paths.).The Storage class(DataStore) saves those
results in a map.
This class is used to display those results in console.
Package wants to display their results returns some  'DisplayInfo'.
This Display info is display information which specifies which things
to display(e.g.: files along with their paths present in multiple directories
or files or files in which text is present or any combination of option
/s,/d,/f and no option. )

Public Interface:
=================
void outputResults(const std::string &strDisplayInfo,Store store)         - display all files present in directories or in directories and subdirectories.               
void outputDuplicateResults(const std::string &strDisplayInfo, Store store)    - display duplicate files present in directories or in directories 
                                                                                and subdirectories. 
void outputSearchedFileResults(const std::string &filePath)               - display all files present in directories and subdirectories that contains the 
                                                                          search text.
void outputResults(const std::string &strDisplayInfo)                     - display results if the sequence entered is incorrect.
void outputNoSearchedFileResults(const std::string &searchString, const std::string &filePath)   - display file not found if search text is not found 
                                                                                                 in directories and subdirectories.
void outputNoFilesPresent                                                 - display no files is present if files are not present in map.
std::string rearrangeDisplayInfo(std::string strDisplayInfo)              - As there are many combinations of display information for 3 flags
                                                                           (subdirectories,duplicate,search) exist.so, this function is particularly 
																		    designed to rearrange the 3 combinations into one general combination.
                                                                          
*/
/*Required Files :
*---------------- -
*-DataStore.h , DataStore.cpp ,Display.h , Display.cpp
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
#include"..//DemoProject/DataStore.h"
#include"..//Display/Display.h"

class Display
{
public:
	using Path = const std::string;
	using Paths = std::set < Path >;
	using PathIter = Paths::iterator;
	using ListOfiters = std::list < PathIter >;
	using File = std::string;
	using Store = std::map < File, ListOfiters >;
	
	void outputResults(const std::string &strDisplayInfo,Store store);
	void outputDuplicateResults(const std::string &strDisplayInfo, Store store);
	void outputSearchedFileResults(const std::string &filePath);
	void outputResults(const std::string &strDisplayInfo);
	void outputNoSearchedFileResults(const std::string &searchString, const std::string &filePath);
	void outputNoFilesPresent();
	std::string rearrangeDisplayInfo(std::string strDisplayInfo);
	Display(DataStore &dObj);
private:
	DataStore &ds;
};

#endif


