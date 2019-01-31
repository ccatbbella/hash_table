//Yixiao Yue
//01/23/2018
//hashTable implementation with Modulo Prime hash functions
#include "hash.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <time.h> 
using namespace std;

string intVectToBitStr(vector<int> v){
  //take in a vector of 4 integers, and return a string of how the vector is stored as 32 bits
  //eg [1,4,8,12] --> "00000001 00000100 00001000 00001100", no space for the actual string
  string str = "";
  for(int el:v){
    bitset<8> bit(el);
    str += bit.to_string();
  }
  return str;
}

vector<int> groupBitStr(string str, int b){
  //take in a string representing bits, slice string from left to right to groups of b char, and return the sliced bit char as integer vector
  // eg "00001000", 5 ---> 000 01000 --> {0, 8}
  int l = str.length();
  int vecL;
  int resultEl;
  vector<int> result;
  vector<int> v2;   //indicates how much char goes into each group
  if(l%b != 0){
    vecL = l/b + 1;
    for(int i = 1; i < vecL; i++){
      v2.push_back(b);
    }
    v2.insert(v2.begin(), l - v2.size()* b);
  }
  else if(l%b == 0){
    vecL = l/b;
    for(int i = 0; i < vecL; i++){ v2.push_back(b); }
  }
  for(int el:v2){
    
    string s = str.substr(0, el);
    bitset<32> bit(s);
    long lo = bit.to_ulong();
    result.push_back(int(lo));
    str.erase(str.begin(), str.begin() + el);
  }
  return result;
}

vector<int> parseIP(string ipAddress){
    //input "123.90.222.34", output {123, 90, 222, 34}
    vector<int> result;
    string s;
    int idx; int si;
    for(int i = 0; i < 3; i++){
      
      idx = ipAddress.find(".");
      s = ipAddress.substr(0, idx);
      si = stoi(s);
      result.push_back(si);
      ipAddress = ipAddress.erase(0, idx + 1);
      
    }
    result.push_back(stoi(ipAddress));
    
    return result;

}
int maxOfVector(vector<int> v){
  //return index of the last largest element index in v
  int maxIdx = 0;
  for(int i = 1; i < v.size(); i++){
    if(v.at(i) >= v.at(maxIdx)) {
      maxIdx = i;
    }
  }
  return maxIdx;
}
Table::Table(int tableSize, int b){
    this->tableSize = tableSize;
    this->b = b;
    col = std::vector<int>(tableSize, 0);
    table = {std::vector<Node*>(tableSize, NULL)};
    if(32%b == 0){
      srand(time(0));  //!important
      for(int i = 0; i < 32/b; i++){
        
        int coefficient = rand()% (tableSize);
        as.push_back(coefficient);
      }
    }else{
      for(int i = 0; i < (32/b) + 1; i++){
        int coefficient = rand()% (tableSize);
        as.push_back(coefficient);
      }
    }
}

int Table::hash(string ipAddress){
  vector<int> v = parseIP(ipAddress);
  string bitStr = intVectToBitStr(v);
  int sth = 0;
  v = groupBitStr(bitStr, b);
  for(int i = 0; i < v.size(); i++){
    sth += as[i] * v[i];
  }
  return sth % tableSize;
}


bool Table::lookUp(string ipAddress){
//  print x:  found or x:  not found depending on whether or not x is currently in the hash table
  int hashedKey = hash(ipAddress);
  Node* n = table.at(hashedKey);
  while(n != NULL){
    if(n->data == ipAddress){
      cout << ipAddress << ": found." << endl;
      return true;
    }
    n = n->next;
    
  }
  cout << ipAddress << ": not found." << endl;
  return false;
}

void Table::insert(string ipAddress){
  int hashedKey = hash(ipAddress);
  Node* m = new Node;  //!important using new so that the node exists after function exits
  m->next = NULL;
  m->data = ipAddress;
  Node* n = table.at(hashedKey);
  if(n == NULL){
    table.at(hashedKey) = m;
    insertSuccess++;
    col.at(hashedKey) += 1;
    return;
  }
  while(n->next != NULL){
  
    if(n->data == ipAddress){
      return;
    }
    n = n->next;
  }
  if(n->data == ipAddress){
      return;
  }
  n->next = m;
  insertSuccess++;
  col.at(hashedKey) += 1;
  
}

void Table::deleteHash(std::string ipAddress){
  int hashedKey = hash(ipAddress);
  Node* n = table.at(hashedKey);
  Node* m = table.at(hashedKey);
  if(n == NULL){
    cout << "Error : could not delete " << ipAddress << " because it does not exist." << endl;
    return;
  }else{
    while(n->next != NULL){
      
      if(n->next->data == ipAddress){
        m = n->next;
        n->next = m->next;
        delete m;
        deleteSuccess++;
        return;
      }
      n = n->next;
    }
    if(n->data == ipAddress){
        table.at(hashedKey) = NULL;
        delete n;
        deleteSuccess++;
        return;
    }
  }
  cout << "Error : could not delete " << ipAddress << " because it does not exist." << endl;
}

void Table::stat(){
  /* Number of items successfully inserted:
    Number of items successfully deleted:
    The number of empty slots in the hash table:
    The number of hash table slots with exactly 1 item:
    The maximum number of collisions in the hash table:  (count, location) */
  int emptySlot = 0; int singleSlot = 0;
  for(int i = as.size() - 1; i >= 0; i--) {cout << as.at(i) << " ";}
  cout << endl;
  cout << insertSuccess << endl;
  cout << deleteSuccess << endl;
  for(Node* n:table){
    if(n == NULL) emptySlot++;
    else if(n->next == NULL) singleSlot++;
  }
  cout << emptySlot << endl;
  cout << singleSlot << endl;
  int maxI = maxOfVector(col);
  cout << col.at(maxI) << " " << maxI << endl;
}