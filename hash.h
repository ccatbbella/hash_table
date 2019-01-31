#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#ifndef HASH_H
#define HASH_H
struct Node{
  std::string data;
  Node* next;

};

class Table{
  public:
    Table(int tableSize, int b);
    void insert(std::string ipAddress);
    bool lookUp(std::string ipAddress);
    void deleteHash(std::string ipAddress);
    int hash(std::string ipAddress);
    void stat();
  
  private:
    int tableSize;
    
    int insertSuccess = 0;
    int deleteSuccess = 0;
    std::vector<Node*> table;
    std::vector<int> col;  //store the length of collision chain at each index of table
    std::vector<int> as;  //store the random coefficient a's
    int b;
};
#endif