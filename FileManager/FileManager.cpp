

///////////////////////////////////////////////////////////////////
//  FileManager.cpp  - Implementation file for FileManager class //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


#include <iostream>
#include "..//FileSystem/FileSystem.h"
#include "FileManager.h"

FileManager::FileManager(const std::string& path, DataStore& ds, std::vector<std::string>& vector, FileSearch &fs, Display &dp) :path_(path), store_(ds), optionsVector_(vector), fs_(fs), dp_(dp)
{
	patterns_.push_back("*.*");

}

std::string FileManager::search() {
	processInput();
	BOOLEAN pathExitsFlag;
	if (invalidFlag)
	{
		displayString = "Invalid";
	}
	else{
		// checking whether the path entered exists or not
		pathExitsFlag = FileSystem::Directory::exists(path_);
		path_ = FileSystem::Path::getFullFileSpec(path_);
		if (pathExitsFlag)
		{
			if (subdirectoriesFlag)
			{
				for (auto patt : patterns_) {
					findDirectoriesAndSubdirectories(path_, patt);
				}
			}
			if (searchFlag)
			{
				fs_.storeSearchText(searchString);
			}
			if (directoryFlag)
			{
				for (auto patt : patterns_) {
					findDirectories(path_, patt);
				}
			}
		}
		else
		{
			displayString = "Invalid";
		}
	}
	clearOptionandPatternsVector();
	resetflags();
	return displayString;
}


void FileManager::processInput()
{
	int pos = 0;
	//Iterating through options vector(which contains options and patterns) and storing valid patterns and options(/d /s /f) in proper vectors.
		for (processIterator = optionsVector_.begin(); processIterator != optionsVector_.end(); ++processIterator)
		{
			std::string option = "";
			if (std::regex_match(*processIterator, std::regex("(/f)(.*)")) || std::regex_match(*processIterator, std::regex("(/F)(.*)")))
			{
				searchString = (*processIterator).substr(2);
				option = (*processIterator).substr(0, (*processIterator).find(searchString));
				listOfOptions.push_back(option);
			}
			else if (std::regex_match(*processIterator, std::regex("(/)(.*)")))
			{
				listOfOptions.push_back(*processIterator);
			}
			else if ((pos = (*processIterator).find("*.")) != std::string::npos)
			{
				if (*processIterator == "*.*") //clearing the patterns if *.* is encountered.
				{
					patterns_.clear();
					patterns_.push_back("*.*");
					NoPushFlag = true;
				}
				addFilePattern(*processIterator);
			}
			else
			{
				invalidFlag = true;
			}
		}
		if (!invalidFlag)
		{
			if (listOfOptions.size() == 0)
			{
				//setting directory flag is true if no option is provided by user
				directoryFlag = true;
				displayString = displayString + "_directory";
			}
			else
				processOptionsAndPatterns(listOfOptions);
		}
	}



void FileManager::processOptionsAndPatterns(list listOfOptions)
{
	//setting the flag as true according to the options provided
		for (auto elem : listOfOptions)
		{
			if (elem == "/s" || elem == "/S")
			{
				subdirectoriesFlag = true;
				displayString = displayString + "_subdirectories";
				
			}
			else if (elem == "/d" || elem == "/D")
			{
				subdirectoriesFlag = true;
				displayString = displayString + "_duplicateFiles";
			}
			else if (elem == "/f" || elem == "/F")
			{
				subdirectoriesFlag = true;
				searchFlag = true;
				displayString = displayString + "_searchFiles";
			}
			else
			{
				invalidFlag = true;
			}
		}
	}





void FileManager::addFilePattern(const std::string& patt)
{
	if (patterns_.size() == 1 && patterns_[0] == ("*.*") && NoPushFlag == false)  {
		patterns_.pop_back(); //popping the pattern(which is pushed in constructor) if pattern is mentioned by user.
		patterns_.push_back(patt);
	}
	else if (patterns_.size() >= 1 && patterns_[0] != ("*.*"))
	{
		patterns_.push_back(patt); 
	}
}


void FileManager::findDirectories(const std::string &path, const std::string patt)
{
	std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
    FileSystem::Directory::setCurrentDirectory(path);
	if (files.size() != 0)
	{
		for (auto iteratation : files)
		{
			store_.save(iteratation, { FileSystem::Path::getFullFileSpec(path) });
		}
	}
}


void FileManager::findDirectoriesAndSubdirectories(const std::string &path, const std::string patt) {
	std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
	std::vector<std::string> ::iterator iterDirectory;
	std::vector<std::string> directories = FileSystem::Directory::getDirectories(path);
	FileSystem::Directory::setCurrentDirectory(path);
	if (directories.size() != 0)
	{
		directories.erase(directories.begin(), directories.begin() + 2);
		for (iterDirectory = directories.begin(); iterDirectory != directories.end(); ++iterDirectory)
		{
			*iterDirectory = FileSystem::Path::fileSpec(FileSystem::Directory::getCurrentDirectory(), *iterDirectory);
		}
	}
	if (files.size() != 0)
	{
		for (auto iteration : files)
		{
			store_.save(iteration, { FileSystem::Path::getFullFileSpec(path) });
		}
	}
	if (directories.size() != 0)
	{
		for (auto dir : directories)
		{
			//recursive call of function to iteratae through sub directories
			findDirectoriesAndSubdirectories(dir, patt);
		}
	}
}



void FileManager::clearOptionandPatternsVector()
{
	listOfOptions.clear();
	optionsVector_.clear();
	patterns_.clear();
}

void FileManager::resetflags()
{
	subdirectoriesFlag = false;
	duplicateFlag = false;
	searchFlag = false;
    invalidFlag = false;
	 directoryFlag = false;
	 NoPushFlag = false;
}



#ifdef TEST_FILEMANAGER
int main() {
	DataStore ds;
	Display dp(ds);
	FileSearch fs(ds,dp);
	std::string displayString;
	std::vector<std::string> testVector;

	std::cout << "\n""\n""\n"<<"Test Case 1: path is current directory , Pattern/Patterns is/are: *.h *.cpp and option is /s" << "\n";
	testVector.push_back("*.h");
	testVector.push_back("*.cpp");
	testVector.push_back("/s");
	FileManager fm("../", ds, testVector,fs,dp);
	displayString = fm.search();
	dp.outputResults(displayString,ds.getStoreMap());

	std::cout << "\n""\n""\n" << "Test Case 2: path is current directory , Pattern/Patterns is/are: *.h *.cpp and option is /s /d" << "\n";
	testVector.push_back("*.h");
	testVector.push_back("*.cpp");
	testVector.push_back("/s");
	testVector.push_back("/d");
	displayString = fm.search();
	displayString = "display_subdirectories_duplicateFiles";
	dp.outputResults(displayString, ds.getStoreMap());

	std::cout << "\n""\n""\n" << "Test Case 3: path is current directory , Pattern/Patterns is/are: *.h *.cpp and option is /d" << "\n";
	testVector.push_back("*.h");
	testVector.push_back("*.cpp");
	testVector.push_back("/d");
	displayString = fm.search();
	displayString = "display_duplicateFiles";
	dp.outputResults(displayString, ds.getStoreMap());

	std::cout << "\n""\n""\n" << "Test Case 4: path is current directory , Pattern/Patterns and options are default" << "\n";
	testVector.push_back("*.*");
	displayString = fm.search();
	displayString = "display_directory";
	dp.outputResults(displayString, ds.getStoreMap());

	std::cout << "\n""\n""\n" << "Test Case 5: path is current directory , Pattern/Patterns is *.* and option is incorrect: /t" << "\n";
	testVector.push_back("*.*");
	testVector.push_back("/t");
	displayString = fm.search();
	dp.outputResults(displayString, ds.getStoreMap());
	return 0;

}
#endif