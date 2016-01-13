#include"DataStore.h"

///////////////////////////////////////////////////////////////////
//  DataStore.cpp     -  implementation file for DataStore class //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//  Application:  DemoProject,Project - 1(File Catalog)          //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


void DataStore::save(const std::string& filename, const std::string &path)
{
	save(path);
	Paths::iterator pathIterator = paths.find(path);
	Store::iterator storeIterator = store.find(filename);
	//If a path iterator not present for a file in a map,then updating store otherwise clearing list of iterators and pushing it again.
	if (storeIterator != store.end())
	{
		store[filename].push_back(paths.find(path));
		}
	else
	{
		listIters.clear();
		listIters.push_back(pathIterator);
		store.insert(make_pair(filename, listIters));
	}
}

//Function that saves path and specially designed to show in test stub that path are saved only once.
void DataStore::save(const std::string &filespec)
{
	paths.insert(filespec);
}


DataStore::Store DataStore::getStoreMap()
{
	return store;
}


DataStore::Paths DataStore::getfilePaths()
{
	return paths;
}


#ifdef TEST_DATASTORE
int main()
{
	DataStore dObj;
	dObj.save("file 1","path1");
	dObj.save("file 1", "path2");
	dObj.save("file 1", "path3");
	dObj.save("file 2", "path3");
	dObj.save("file 3", "path3");
	dObj.save("file 3", "path4");
	dObj.save("file 4", "path5");
	
	std::set < const std::string >::iterator iter;
	
	//Showing the files with their list of iterators
	for (auto item : dObj)
	{
		std::cout << "File : " << item.first << "is present in path/paths:"<<"\n";
		for (auto elem : item.second)
		{
			std::cout << *elem <<"\n";
		}
		
		std::cout <<"\n";
	}
	//showing that each path is stored aonly once
	std::cout << "Paths stored is/are: "<<"\n";
	for (auto elem : dObj.getfilePaths())
	{
		std::cout << elem << "\n";
	}
	
	return 0;
}
#endif