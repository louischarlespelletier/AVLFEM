#include <iostream>

#include "AvlfemTable.h"

using namespace std;

int main()
{
  cout << "Hello world!" << endl;
  //unsigned char * test = new unsigned char[4];
  //*test = 0x18;
  //*(test+1) = 0x99;
  //*(test+2) = 0x99;
  //*(test+3) = 0x99;
  //float output;
  //*((unsigned char*)&output) = *test;
  //*((unsigned char*)&output+1) = *(test+1);
  //*((unsigned char*)&output+2) = *(test+2);
  //*((unsigned char*)&output+3) = *(test+3);
  //cout << output << endl;

  AvlfemTable* avlfem_02_coord_table = new AvlfemTable(AvlfemTable::Static, "X F8 Y F8 Z F8", 5);

  AvlfemTable* avlfem_02_elem_table  = new AvlfemTable(AvlfemTable::Static, "COORID1 I4 COORID2 I4 COORID3 I4", 5);

  AvlfemTable* avlfem_02_edge_table  = new AvlfemTable(AvlfemTable::Static, "COORID1 I4 COORID2 I4 ELEMID1 I4 COORID3 I4 ELEMID2 I4 COORID5 I4", 5);

  return 0;
}
