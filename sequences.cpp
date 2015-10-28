#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  string line;
  ifstream datafile ("Prog4-data.txt");
  if (datafile.is_open()) {
    unordered_map<string, vector<string>> m;
    int count = 0;
    string label = "";
    while (getline(datafile, line)) {
      if(count%2 == 0){
        label = line;
      } else {
        if(m.find(line) == m.end()) {
          // not found
          vector<string> labels;
          labels.push_back(label);
          m.emplace(line, labels);
        } else {
          vector<string> sv = m.at(line);
          sv.push_back(label);
          m[line] = sv;
        }
      }
      count++;
    }
    datafile.close();
    ofstream outFile ("outData.txt");
    if(outFile.is_open()){
      for(auto data: m){
        string labels = "";
        for(string s: data.second){
          labels += (s + ", ");
        }
        labels = labels.substr(0, labels.length() - 2);
        outFile << labels << endl << data.first << endl;
      }
    }
  } else cout << "Unable to open File" << endl;
  return 0;
}
