#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>
#include <algorithm> 
#include "hash.h"
using namespace std;
vector<int> primes = {3, 5, 11, 17, 37, 67, 131, 257, 521, 1031, 2053, 4099, 8209, 16411, 32771, 65537, 131101, 262147, 524309, 1048583};





int main(){
  int firstLine; int tableSize; int b;
  cin >> firstLine;

  string in; string ipAddress; 
  b = log2(firstLine);
  tableSize = primes[b-1];
  Table t(tableSize, b);
  
 while(!cin.eof()){
    cin >> in;
    cin >> ipAddress;
    if(in == "insert"){
      t.insert(ipAddress);

    }
    else if(in == "delete"){
      t.deleteHash(ipAddress);
      
    }
    else if(in == "lookup"){
      t.lookUp(ipAddress);
      
    }
    else if(in == "stat") t.stat();
  }   
  /* int s = 123;
  int s2 = 4;
  bitset<8> b0(s);
  bitset<8> b1(s2);
  cout << b0 << endl;
  cout << b1 << endl;
  string str = b0.to_string();
  string str2 = b1.to_string();
  str.append(str2);
  string ss1 = "hello";
  string ss2 = "last";
  string ss3 = ss1 + ss2;
  cout << ss3;
  cout << str << endl;
  bitset<32> b2(str);
  cout << b2 << endl; */
  //cout << (b0 & b1) << endl;
   /*  int b = 10;
  int c = pow(2, b) - 1;
  bitset<32> bit(s);
  bitset<32> bit2(c);
  //cout << c << endl; 
  //bitset<32> b2("11001");
  cout << (bit2 & bit) << endl;
  cout << bit << endl;
  cout << bit2 << endl;  */

  /* int c = 0b010000;
  cout << c << endl; */
  return 0;
}



