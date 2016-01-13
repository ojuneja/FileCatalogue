#ifndef DATASTORE_H
#define DATASTORE_H
///////////////////////////////////////////////////////////////////
//  DataStore.h      -  header file for DataStore class          //
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
This package act as storage class for all other classes.
After searching the files from different directories,a file 
catalog is constructed.
This class is helpful in storing files,paths,list of iterators.
The list Iterartors is also stored in a map which provide access
to paths.A particular filename and path is stored only once but 
may have several list of iterators. 
The Purpose of this package is to store that data.
This Package uses maps,sets,iterators to accomplish that task.

Public Interface:
=================
void save(const std::string &fileName, const std::string &path)    - saves filename and their list of iterators into map
void save(const std::string &filespec)                             - saves pathnames into set
Paths getfilePaths                                                 - get pathnames from set which is stored earlier.
Store getStoreMap                                                  - get map which contains filename and their list of iterators.
*/
/*Required Files :
*---------------- -
*-DataStore.h , DataStore.cpp
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

#include<map>
#include <string>
#include<set>
#include<iostream>
#include<list>
class DataStore
{
public:
	using Path = const std::string;
	using Paths = std::set < Path > ;
	using PathIter = Paths::iterator;
	using ListOfiters = std::list < PathIter >;
	using File = std::string;
	using Store = std::map < File, ListOfiters > ;
	using iterator = Store::iterator;

	void save(const std::string &fileName, const std::string &path);
	void save(const std::string &filespec);
	Paths getfilePaths();
	Store getStoreMap();
	iterator begin() { return store.begin(); }
	iterator end() { return store.end(); }
	
private:
	Store store;
	Paths paths;
	ListOfiters listIters;
	
};
#endif
