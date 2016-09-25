#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<string> hashtable;

bool compare_string_len(string a, string b)
{
  return (a.size() >= b.size());
}

bool isword(string& word, bool compound_only);

// return true if word is a subword or compound word
bool isword(string& word, bool compound_only)
{
  string prefix;
  
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

int main()
{
  vector<string> words_sorted;
  ifstream inputfile;
  string word;
  int rc = 1; // 0: sucess, 1: fail
  
  inputfile.open("words.list");
  while (!infile.eof())
  {
    getline(infile, word);
    words_sorted.push_back(word);
    hashtable.insert(word);
  }
  
  sort(words_sorted.begin(), words_sorted.end(), compare_string_len);
  
  for (auto it = words_sorted.begin(); it < words_sorted.end(); it++) {
    if (isword(*it, true)) {
      cout << "The longest compund word is " << (*it) << endl;
      rc = 0;
      break;
    }
  }
  
  if (rc) {
    cout << "Can't find the longest compound word"<< endl;
  }

  inputfile.close();
  return rc;
}
