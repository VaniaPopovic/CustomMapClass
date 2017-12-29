// AVLMap.cpp : Defines the entry point for the console application.
//
#include "MyMap.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <map>
#include <fstream>

int main()
{
	std::ofstream outFile("output.txt", std::ios::out);
	outFile << "-----------------------------------------------------------" << std::endl;

	MyMap<int, std::string> t;
	outFile << "Creating a map of type <int(key),string(value)> with keys 1-5" << std::endl;

	t.insert(1, "HE1");
	t.insert(2, "2He");
	t.insert(3, "H3e");
	t.insert(4, "He4");
	t.insert(5, "He5");


	outFile << '\n';

	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << "Demonstrating using iterators begin() and end() to print all values in the map " << std::endl;
	for (auto it = t.begin(); it != t.end(); ++it)
	{
		outFile << '\n' << "it.first()-> " << it.first() << " it->second()->   " << it.second() << std::endl;

	}
	outFile << '\n';
	outFile << "-----------------------------------------------------------" << std::endl;

	outFile << "Trying to use find on key 3. Find returns an iterator to that key so we can call second() to show the value" << std::endl;


	outFile << t.find(3).second();

	outFile << '\n';
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << "Demonstrating erase on key 1" << std::endl;

	t.erase(1);
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';

	outFile << "Demonstrating size() function" << std::endl;

	outFile << t.size() << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating at function for key 3, it returns the value of the key if found, exception if not " << std::endl;
	outFile << t.at(3) << std::endl;
	outFile << "Demonstrating at function for key 300, should throw but we will catch it " << std::endl;
	try
	{
		t.at(300);
	}
	catch(MyMap<int, std::string>::out_of_range a){
		outFile << "\nEXCEPTION CAUGHT" << std::endl;
	}
	
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating copy constructor, creating map b with the values of map t and printing the values" << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;
	MyMap<int, std::string> b(t);
	outFile << "Map b iterator->first() , iterator->second()" << std::endl;
	for (auto it = b.cbegin(); it != b.cend(); ++it)
	{
		outFile << '\n' << "it.first()-> " << it.first() << " it->second()->   "<< it.second() << std::endl;
	}
	
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating assignment operator Map g = t (our first map) and printing values" << std::endl;

	outFile << "Map g iterator->first() , iterator->second()" << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;
	MyMap<int, std::string> g = t;
	for (auto it = g.cbegin(); it != g.cend(); ++it)
	{
		outFile << '\n' << "it.first()-> " << it.first() << " it->second()->   " << it.second() << std::endl;
	}

	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating empty() function on map b" << std::endl;

	outFile << t.empty() << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;

	outFile << '\n';
	outFile << "Demonstrating count() function on map b key 4(which was deleted)" << std::endl;

	outFile << t.count(4) << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;

	outFile << '\n';
	outFile << "Demonstrating equals operator on the two maps " << std::endl;
	bool mapsAreEqual = b == t;
	outFile << mapsAreEqual << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating not equals operator on the two maps " << std::endl;
	mapsAreEqual = b != t;
	outFile << mapsAreEqual << std::endl;
	outFile << "-----------------------------------------------------------" << std::endl;

	outFile << '\n';
	outFile << "Demonstrating creation of constant iterators and their preincrement operator " << std::endl;
	outFile << "printing second() pointed by constant iterator const_it which is cbegin() of map b" << std::endl;
	MyMap<int, std::string>::const_iterator const_it = b.cbegin();
	outFile << const_it.second() << std::endl;
	outFile << "Using ++const_it and printing second again" << std::endl;
	++const_it;
	outFile << const_it.second() << std::endl;

	
	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating swap() " << std::endl;
	outFile << "Erasing key 5 from t and swapping it with map b, which has key 5" << std::endl;
	t.erase(5);
	t.swap(b);
	outFile << "Printing map t. It should have key 5 in it because it is swapped with map b" << std::endl;

	for (auto it = t.cbegin(); it != t.cend(); ++it)
	{
		outFile << '\n' << "it.first()-> " << it.first() << " it->second()->   " << it.second() << std::endl;
	}


	outFile << "-----------------------------------------------------------" << std::endl;
	outFile << '\n';
	outFile << "Demonstrating erase with providing iterator to fifth element " << std::endl;
	
	auto itt = t.find(5);

	t.erase(itt);

	for (auto it = t.cbegin(); it != t.cend(); ++it)
	{
		outFile << '\n' << "it.first()-> " << it.first() << " it->second()->   " << it.second() << std::endl;
	}


	outFile <<"BENCH MARKING---------------------"<< std::endl;
	std::clock_t start;
	double duration;

	start = std::clock();
	std::map<int, int> stdMAP;
	for (int i = 0; i <10000; ++i)
	{
		stdMAP[i] = i / 10;
	}

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	outFile << "stdMAP took : " << duration << "to insert 10000 elements \n";

	start = std::clock();
	MyMap<int,int> myMAP;
	for (int i = 0; i <10000; ++i)
	{
		myMAP.insert(i, i / 10);
	}

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	outFile << "MyMAP took : " << duration << "to insert 10000 elements \n";


	start = std::clock();

	stdMAP.clear();
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	outFile << "stdMAP took : " << duration << "to clear 10000 elements \n";


	start = std::clock();

	myMAP.clear();
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	outFile << "myMAP took : " << duration << "to clear 10000 elements \n";


	system("pause");

	return 0;
}
