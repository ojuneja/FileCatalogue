///////////////////////////////////////////////////////////////////
//  Executive.cpp      -  implementation file for Executive class//
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////

#include "Executive.h"

Executive::Executive(FileManager &fm, Display &dp, DataStore &ds, FileSearch &fs) :file(fm), display(dp), dStore(ds), fileSearch(fs)
{
//Empty constructor designed to initialize variables
}
int main(int argc, char *argv[])
{
	try{
		std::string answer;
		Executive::vector container_;
		std::string  path = "";
		Executive::vector restOptions;
		//storing all the user input into container
		for (int arg_ = 1; arg_ < argc; ++arg_)
		{

			container_.push_back(argv[arg_]);
		}
		if (container_.size() == 0)
		{
			path = ".";
		}
		else
		{
			//storing path in one variable and rest of the things in another vector
			path = container_[0];
			container_.erase(container_.begin());
			restOptions = container_;
		}
		DataStore ds;
		std::string strDisplayInfo;
		Display dp(ds);
		FileSearch fs(ds, dp);
		FileManager fm(path, ds, restOptions, fs, dp);
		Executive eObj(fm, dp, ds, fs);
		strDisplayInfo = fm.search();
		dp.outputResults(strDisplayInfo, ds.getStoreMap());
		fs.textSearch(strDisplayInfo, ds.getStoreMap());
		std::cout << "\n""\n" << "PRESS ANY KEY AND THEN PRESS ENTER FOR ADDITIONAL TEXTSEARCH OR PRESS ENTER TO QUIT." << "\n";
		std::getline(std::cin, answer);
		while (!answer.empty())
		{
			fs.textSearchAgain(ds.getStoreMap());
			std::cout << "\n""\n" << "PRESS ANY KEY AND THEN PRESS ENTER FOR ADDITIONAL TEXTSEARCH OR PRESS ENTER TO QUIT." << "\n";
			std::getline(std::cin, answer);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
}