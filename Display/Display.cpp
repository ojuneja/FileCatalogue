#include"Display.h"

///////////////////////////////////////////////////////////////////
//  Display.cpp      -  implementation for Display class         //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


Display::Display(DataStore &dObj) :ds(dObj)
{
	//empty constructor designed to initialize variables.
}


void Display::outputResults(const std::string &strDisplayInfo, Store store)
{
	std::string allThreeCombination = rearrangeDisplayInfo(strDisplayInfo);

	if (strDisplayInfo == "display_subdirectories" || strDisplayInfo == "display_directory"
		|| strDisplayInfo == "display_subdirectories_duplicateFiles" || strDisplayInfo == "display_duplicateFiles_subdirectories"
		|| strDisplayInfo == "display_subdirectories_searchFiles"    || strDisplayInfo == "display_searchFiles_subdirectories" 
		|| allThreeCombination == "display_subdirectories_duplicateFiles_searchFiles")
	{
		
		if (store.size() != 0)
		{
			for (auto fileElem : store)
			{
				std::cout << "\n" << fileElem.first << " is present in following paths:" << "\n""\n"; //printing filename
				for (auto IterElem : fileElem.second)
				{
					std::cout << "-- " << *IterElem << "\n"; //printing the presence of file in different paths

				}
				std::cout << "\n";
			}
			std::cout << "\n""\n" <<ds.getStoreMap().size()<<" Files found in "<<ds.getfilePaths().size()<<" directories""\n""\n";
		}
		else
			std::cout << "No file found in specified path." << "\n";
	}
	
		outputDuplicateResults(strDisplayInfo, store);
		outputResults(strDisplayInfo);
	
}


void Display::outputDuplicateResults(const std::string &strDisplayInfo,Store store)
{
	std::string allThreeCombination = rearrangeDisplayInfo(strDisplayInfo);
	if (strDisplayInfo == "display_duplicateFiles"
		|| strDisplayInfo == "display_subdirectories_duplicateFiles" || strDisplayInfo == "display_duplicateFiles_subdirectories"
		|| strDisplayInfo == "display_duplicateFiles_searchFiles" || strDisplayInfo == "display_searchFiles_duplicateFiles"
		|| allThreeCombination == "display_subdirectories_duplicateFiles_searchFiles")
	{

		std::cout <<"\n""\n""\n"<< "-----------Duplicate Files are:--------------" << "\n";
		if (store.size() >= 0)
		{
			bool booleanDuplicateFilesFlag = false;
			for (auto fileElem : store)
			{
				//checking if list of iterators are > 2 then a file is present in multiplte paths(/d option)
				if (fileElem.second.size() >= 2)
					{
						std::cout << "\n"<<"File: " << fileElem.first.c_str() << " is found in following paths: " << "\n""\n";
						booleanDuplicateFilesFlag = true;
						for (auto IterElem : fileElem.second)
						{
							std::cout << "-- " << *IterElem << "\n";
						}
						std::cout << "\n";
				}
			}
			if (!booleanDuplicateFilesFlag)
			{
				std::cout << "No duplicate files found in specified path." << "\n";
			}
		}
		else
			std::cout << "No files found in specified path." << "\n";
	}
}

//If the below combinations are present in any order,then this component will rearrange it to a general combination.
std::string Display::rearrangeDisplayInfo(std::string strDisplayInfo)
{
	
	if (strDisplayInfo == "display_subdirectories_duplicateFiles_searchFiles" || strDisplayInfo == "display_duplicateFiles_subdirectories_searchFiles"
		|| strDisplayInfo == "display_subdirectories_searchFiles_duplicateFiles" || strDisplayInfo == "display_duplicateFiles_searchFiles_subdirectories"
		|| strDisplayInfo == "display_searchFiles_duplicateFiles_subdirectories" || strDisplayInfo == "display_searchFiles_subdirectories_duplicateFiles")
	{
		return "display_subdirectories_duplicateFiles_searchFiles";
	}
	else
		return "Cant Rearrange";
}


void Display::outputSearchedFileResults(const std::string &filePath)
{
	std::cout <<"-- "<< filePath << "\n";
	}


void Display::outputNoSearchedFileResults(const std::string &searchString, const std::string &filePath)
{
	std::cout << "Search String: " << searchString << " is not found in any of the files." << "\n""\n";
}


void Display::outputNoFilesPresent()
{
	std::cout << "\n" << "Files are not present in specified path." << "\n";
}


void Display::outputResults(const std::string &strDisplayInfo)
{
	if (strDisplayInfo == "Invalid")
		std::cout << "\n"<< "The above sequence is not recognized as correct sequence." << "\n";
}

#ifdef TEST_DISPLAY
int main()
{
	DataStore dObj;
	Display ds(dObj);

	std::cout << "\n" << "Test Case1: Displaying files if size of store is zero" << "\n";
	ds.outputResults("display_subdirectories", dObj.getStoreMap());
	ds.outputResults("display_duplicateFiles", dObj.getStoreMap());
	ds.outputResults("display_subdirectories_duplicateFiles", dObj.getStoreMap());

	dObj.save("file 1", "path1");
	dObj.save("file 1", "path2");
	dObj.save("file 1", "path3");
	dObj.save("file 2", "path3");
	dObj.save("file 3", "path3");
	dObj.save("file 3", "path4");
	dObj.save("file 4", "path5");
	
	std::cout << "\n" "\n" << "Test Case2: Displaying files if size of store is not zero" << "\n";
	ds.outputResults("display_subdirectories", dObj.getStoreMap());
	ds.outputResults("display_duplicateFiles", dObj.getStoreMap());
	ds.outputResults("display_subdirectories_duplicateFiles", dObj.getStoreMap());
	return 0;
}
#endif