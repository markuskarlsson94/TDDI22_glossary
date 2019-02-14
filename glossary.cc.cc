#include <string>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include "glossary.h"

void wash(std::string & s)
{
    std::string trash_begining="\"\'(";
    std::string trash_end="!?;,:.\"\')";

    //Ta bort första skräptecknen
    int n=s.find_first_not_of(trash_begining);
    s.erase(s.begin(),s.begin()+n);

    //Ta bort sista skräptecknen
    n=s.find_last_not_of(trash_end);
    s.erase(s.begin()+n+1,s.end());

    //Ta bort 's om det finns något
    n=s.find("'s");
    if ( n==s.size()-2 )
    {
	s.erase( s.end()-2,s.end() );
    }
}

bool allowed_chars(std::string const & s)
{
    return ( all_of(s.begin(),s.end(), [](char const c){ return isalpha(c) || c=='-'; }) );
}

bool allowed_size(std::string const & s)
{
    return ( s.size()>=3 );
}

bool allowed_start_end(std::string const & s)
{
    return !(s.at(0)=='-' || s.at(s.size()-1)=='-');
}

bool no_double_line(std::string const & s)
{
    return ( s.find("--")==-1 ); 
}

bool is_word(std::string const & s)
{
    return ( allowed_chars(s) && allowed_size(s) && allowed_start_end(s) && no_double_line(s) );
}



void word_management(std::ifstream &file, std::vector<std::string> &words,
		     std::map<std::string,unsigned int> &wordMap, int &longestWord, int &maxNum, std::string flag,
		     std::vector <std::pair<std::string, unsigned int>> &wordFreq)
{
    std::for_each(std::istream_iterator<std::string>{file},std::istream_iterator<std::string>{},[&words, &wordMap, &longestWord, &maxNum, flag](std::string s)
	     {
		 wash(s);
		 if (is_word(s))
		 {
                     std::transform( s.begin(),s.end(),s.begin(),::tolower );

		     //Alfabetisk och fallande ordning
		     if (flag=="-a" || flag=="-f")
		     {
			 //Hitta längsta ordet i mapen
			 if (s.size()>longestWord)
			 {
			     longestWord=s.size();
			 }
		     
			 if (wordMap.find(s) == wordMap.end())
			 {
			     wordMap[s] = 1;
			 }
			 else
			 {
			     wordMap[s]++;
			     //Hitta största värdet i mapen
			     if (wordMap[s]>maxNum)
			     {
				 maxNum=wordMap[s];
			     }
			 }
		     }

		     //Kronologisk ordning
		     else if (flag=="-o")
		     {
			 words.push_back(s);
		     }
		 }
	     });

    file.close();

    //Lägg till i vector och sortera
    if (flag=="-f")
    {
        std::copy(wordMap.cbegin(),wordMap.cend(), std::back_inserter<std::vector <std::pair<std::string, unsigned int>> >(wordFreq) );

        std::sort(wordFreq.begin(), wordFreq.end(), [=](std::pair<std::string, unsigned int>& a, std::pair<std::string, unsigned int>& b)
	     {
		 return a.second > b.second;
	     }
	    );
    }
}

void word_print(std::vector<std::string> &words, std::map<std::string,unsigned int> &wordMap, int &longestWord, int &maxNum, std::string flag, std::vector <std::pair<std::string, unsigned int>> &wordFreq, int const maxWidth)
{
    //Alfabetisk ordning
    if (flag=="-a")
    {
	std::string numWidth=std::to_string(maxNum);
	std::for_each(wordMap.cbegin(), wordMap.cend(), [longestWord, numWidth](std::pair<std::string, unsigned int> p)
		 {
		     std::cout << std::setw(longestWord) << std::left << p.first << "  " << std::right << std::setw(numWidth.size()) << p.second << std::endl;
		 }
	    );
    }

    //Fallande ordning
    else if (flag=="-f")
    {
	std::string numWidth=std::to_string(maxNum);
	std::for_each(wordFreq.cbegin(), wordFreq.cend(), [longestWord, numWidth](std::pair<std::string, unsigned int> p)
		 {
		     std::cout << std::setw(longestWord) << std::right << p.first << "  " << std::right << std::setw(numWidth.size()) << p.second << std::endl;
		 }
	    );
    }

    //Kronologisk ordning
    else if (flag=="-o")
    {
	int width=0;
	bool firstWord=true;
	std::for_each(words.cbegin(),words.cend(),[maxWidth, &width, &firstWord](std::string i)
		 {
		     if (firstWord==true)
		     {
			 std::cout << i;
			 width+=i.size();
			 firstWord=false;
		     }
		     else
		     {
			 if ( width+(i.size()+1)<maxWidth )
			 {
			     std::cout << " " << i;
			     width+=i.size()+1;
			 }
			 else
			 {
			     std::cout << std::endl << i;
			     width=i.size();
			 }
		     }
		 }
	    );
	std::cout << std::endl;
    }
}
