#include "FileSearch.h"

///////////////////////////////////////////////////////////////////
//  FileSearch.cpp   -  implementation file for Filesearch class //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


FileSearch::FileSearch(DataStore &ds, Display &dp) :dsr_(ds), dp_(dp)
{
	//empty constructor designed to initialize variables
}


void FileSearch::textSearchAgain(Store store) {
	//searching text second time after construction of catalog.
	std::string displayString = "display_searchFiles";
	std::string text;
	BOOLEAN validFlag = false;
	std::cout << "Enter text with pattern(s)(eg.:<search text> <pattern(s)>): ";
	std::getline(std::cin, text);
	
	std::string textTobeSearched;
	validFlag = processInputs(text);
	if (validFlag)
	{
		textSearch(displayString, store);
		patternsVector.clear();
	}
	else
	{
		patternsVector.clear();
		dp_.outputResults("Invalid");
	}

}


BOOLEAN FileSearch::processInputs(std::string text)
{
	std::string delimiter = " ";
	std::string delimiterOfPattern = ".";
	std::string patterns;
	size_t pos = 0;
	std::string textTobeSearched;
	BOOLEAN flag = false;
	BOOLEAN patternSeparationFlag = false;
	size_t occurences = std::count(text.begin(), text.end(), '"');
		if (occurences > 1)
		{ //Sets patternflag as true(if patterns are present) and separate the text(if one word text) and pattern
			textTobeSearched = text.substr(text.find_first_of('"'), text.find_last_of('"'));
			textTobeSearched = textTobeSearched.substr(1);
			patterns = text.substr((textTobeSearched.size() + 2), text.size());
			if (patterns != "")
			{
				patternSeparationFlag = true;
			}
		}
		else
		{  //Sets patternflag as true(if patterns are present) and separate the text(if more than one word text) and pattern
			textTobeSearched = text;
			textTobeSearched = textTobeSearched.substr(0, textTobeSearched.find_first_of(delimiter));
			if (!(textTobeSearched == text))
			{
				patterns = text.substr((textTobeSearched.size() + 1), text.size());
				patternSeparationFlag = true;
			}
		}
		PatternSeparation(patternSeparationFlag, patterns);
			flag = storeSearchText(textTobeSearched);
		return flag;
	
}


void FileSearch::PatternSeparation(BOOLEAN patternSeparationFlag, std::string patterns)
{
	int pos = 0;
	std::string token;
	std::string delimiter = " ";
	std::string delimiterOfPattern = ".";
	if (patternSeparationFlag)
	{//separate the patterns if multiple presents are present and hen stores in vector
		while ((pos = patterns.find(delimiter)) != std::string::npos) {
			token = patterns.substr(0, pos);
			token = token.erase(0, delimiterOfPattern.length());
			patternsVector.push_back(token);
			patterns.erase(0, pos + delimiter.length());
		}
		token = patterns.substr(0, pos);
		token = token.erase(0, delimiterOfPattern.length());
		patternsVector.push_back(token);
	}
}


BOOLEAN FileSearch::storeSearchText(std::string searchText)
{
	if (searchText == "")
	{
		return false;
	}
	else
	{
		searchString = searchText;
		return true;
	}
}




void FileSearch::textSearch(std::string displayString, Store store)
{

	if (displayString == "display_searchFiles"
		|| displayString == "display_subdirectories_searchFiles"
		|| displayString == "display_duplicateFiles_searchFiles"
		|| displayString == "display_subdirectories_duplicateFiles_searchFiles"){
		if (store.size() != 0)
			findText(store, searchString);
		else
			dp_.outputNoFilesPresent();
	}
}



void FileSearch::findText(Store store_, std::string searchString)
{
	
	BOOLEAN booleanFileFound = false;
	BOOLEAN  booleanAnyFileFound = false;
	std::string file;
	std::string specificFile;
	processPatterns();
	if (booleanFindFlag)
	{
		std::cout << "\n""\n" << "Search text: " << '"' << searchString << '"' << " is found in:" << "\n""\n";
		for (auto elem : store_)
		{
			for (auto item : elem.second)
			{
				file = FileSystem::Path::fileSpec(*item, elem.first);
				specificFile = filterFiles(patternsVector, file);
				booleanFileFound = fileSearch(searchString, specificFile);
				if (booleanFileFound)
				{
					booleanAnyFileFound = true;
					dp_.outputSearchedFileResults(file);
				}
			}
		}
		if (booleanAnyFileFound == false)
			dp_.outputNoSearchedFileResults(searchString, file);
		booleanFindFlag = false;
	}
	else
	{
		dp_.outputResults("Invalid");
	}
}



BOOLEAN FileSearch::processPatterns()
{
	if (patternsVector.size() > 0)
	{ //checks if pattern is appropriate or not
		int pos = 0;
		for (auto element : patternsVector)
		{ 
			booleanFindFlag = false;
			if ((pos = (element).find(".")) != std::string::npos)
			{
				booleanFindFlag = true;
			}
		}
	}
	else if (patternsVector.size() == 0)
	{
		booleanFindFlag = true;
	}
	else
	{
		booleanFindFlag = false;
	}
	return booleanFindFlag;
}

std::string FileSearch::filterFiles(std::vector<std::string> strPatternsandText_,std::string file){
	std::string specificFile;
	std::string tempFilePattern = file;
	if (strPatternsandText_.size() > 0)
	{ 
		//filter the files according to pattern entered by user
		for (auto element : strPatternsandText_)
		{
			tempFilePattern = file.substr(file.find_last_of('.'), file.size());
			//no need to look into pattern if the pattern is *.*
			if (element == ".*")
			{
				specificFile = file;
				return specificFile;
			}
			if (tempFilePattern == element)
			{
				specificFile = file;
			}
		}
	}
	else
	{
		specificFile = file;
	}
	return specificFile;
}


BOOLEAN FileSearch::fileSearch(std::string stringToBeSearched, std::string file)
{
	BOOLEAN boolSearch = false;
	std::fstream myFile2;
	myFile2.open(file, std::fstream::in);
	int offset;
	std::string line;
	if (myFile2.is_open())
	{
		while (!myFile2.eof())
		{
			getline(myFile2, line);
			if ((offset = line.find(stringToBeSearched, 0)) != std::string::npos)
			{
				boolSearch = true;
			}
		}
	}
	return boolSearch;
}



#ifdef TEST_FILESEARCH
int main()
{
	DataStore ds_;
	Display dp(ds_);
	FileSearch fs(ds_,dp);
	std::string answer = "c";
	ds_.save("TestFile.txt","..//FileSearch/");
	ds_.save("TestFile2.txt", "..//FileSearch/");
	fs.storeSearchText("ojas juneja");
	fs.textSearch("display_searchFiles", ds_.getStoreMap());
	fs.storeSearchText("test");
	fs.textSearch("display_searchFiles", ds_.getStoreMap());
	fs.storeSearchText("invalidtext");
	fs.textSearch("display_searchFiles", ds_.getStoreMap());
	std::cout << "\n""\n" << "Press c and then enter for additional text searching or else any other key to quit." << "\n";
	std::getline(std::cin, answer);
	while (answer == "c")
	{
		fs.textSearchAgain(ds_.getStoreMap());
		std::cout <<"\n""\n"<< "Press c and then enter for additional text searching or else any other key to quit." << "\n";
		std::getline(std::cin, answer);
	}
	return 0;
}

#endif