#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<string> hashtable;

// return true if word is a subword or compound word
bool isword(const string& word, bool compound_only)
{
  string prefix, suffix;
  
  for(int i = 1; i < word.size(); i++) {
    prefix = word.substr(0, i);
    if ((hashtable.find(prefix) != hashtable.end()) &&
        isword(word.substr(i, (word.size() - i)), false)) {
      return true;
    }
  }
  
  if (compound_only == false) {
    return (hashtable.find(word) != hashtable.end());
  }
  
  return false;
}

int main(int argc, char *argv[])
{
  ifstream inputfile;
  string word;
  int rc = 1; // 0: sucess, 1: fail
  int longestlen = 0;
  
  inputfile.open(argv[1]);
  while (!inputfile.eof())
  {
    getline(inputfile, word);
    hashtable.insert(word);
  }
  inputfile.close();
    
  for (auto it = hashtable.begin(); it != hashtable.end(); it++) {
    if ((*it).size() <= longestlen) {
      continue;
    }
    if (isword(*it, true)) {
      longestlen = (*it).size();
      word = *it;
      rc = 0;
    }
  }
  
  if (rc) {
    cout << "Can't find the longest compound word"<< endl;
  } else {
    cout << "The longest compund word is " << word << endl;
  }

  return rc;
}
