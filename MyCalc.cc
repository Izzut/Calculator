#include "Calculator.h"
#include <iostream>
#include <istream>
#include <sstream>
using namespace std;

int main(int argc, char** argv)
{
   if (argc == 2){
      string filepath = argv[1];
      Calculator calc;
      calc.run_from_file(filepath);
   }
   else if (argc == 1){
      Calculator calc;
      calc.run_from_terminal();
   }
   else{
      cerr << "Too many input arguments, please write only one filename" << endl;
   }
   return 0;
}

