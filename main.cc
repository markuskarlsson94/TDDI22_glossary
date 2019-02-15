#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <iomanip>

#include "glossary.h"

using namespace std;

int error_argument_count(int argc);
int error_management(int argc, char*argv[], std::string &flag, std::ifstream &file, int &maxWidth);

int main(int argc, char *argv[])
{      
    //---------Felhantering----------
    
    if (error_argument_count(argc)==0)
    {
	return 0;
    }
    
    string flag=string(argv[2]);
    ifstream file(argv[1]);

    int maxWidth;
    int error=error_management(argc, argv, flag, file, maxWidth);

    if (error==0)
    {
	return 0;
    }
    
    //---------Containrar---------
    map<string,unsigned int> wordMap; //-a/-f
    vector < std::pair<string, unsigned int> > wordFreq; //-f
    vector <string> words; //-o
    
    int longestWord{0}, maxNum{1};

    //----------Hantering av ord---------
    word_management(file, words, wordMap, longestWord, maxNum, flag, wordFreq); 

    //----------Utskrift av ord----------
    word_print(words, wordMap, longestWord, maxNum, flag, wordFreq, maxWidth);

    return 0;
}

int error_argument_count(int argc)
{
    if (argc==1)
    {
	std::cout << "Error: No arguments given." << std::endl;
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
	return 0;
    }

    else if (argc==2)
    {
	std::cout << "Error: Second argument missing or invalid." << std::endl;
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
	std::cout << "avsluta" << std::endl;
	return 0;
    }
    return 1;
}

int error_management(int argc, char*argv[], std::string &flag, std::ifstream &file, int &maxWidth)
{
    //Ogiltig flagga
    if (flag!="-a" && flag!="-o" && flag!="-f")
    {
	std::cout << "ERROR: Second argument invalid." << std::endl;
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
	return 0;
    }

    //Ogiltig fil
    if (file.fail())
    {
	std::cout << "ERROR: Failed to open file" << std::endl;
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
	return 0;
    }

    if (flag=="-o")
    {
	if (argc<4)
	{
	    std::cout << "ERROR: Third argument missing." << std::endl;
	    std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
	    return 0;
	}
	else 
	{
	    try 
	    {
		maxWidth=std::stoi(argv[3]);
	    }
	    catch (std::invalid_argument)
	    {
		 std::cout << "ERROR: Third argument invalid." << std::endl;
		 std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
		 return 0;
	    }
	}
    }
    return 1;
}
