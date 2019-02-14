#ifndef GLOSSARY_H
#define GLOSSARY_H

#include <fstream>
#include <map>
#include <vector>


void wash(std::string & s);
bool allowed_chars(std::string const & s);
bool allowed_size(std::string const & s);
bool allowed_start_end(std::string const & s);
bool no_double_line(std::string const & s);
bool is_word(std::string const & s);

void word_management(std::ifstream &file, std::vector<std::string> &words, std::map<std::string,unsigned int> &wordMap, int &longestWord, int &maxNum, std::string flag, std::vector <std::pair<std::string, unsigned int>> &wordFreq);
void word_print(std::vector<std::string> &words, std::map<std::string,unsigned int> &wordMap, int &longestWord, int &maxNum, std::string flag, std::vector <std::pair<std::string, unsigned int>> &wordFreq, int const maxWidth);

#endif
