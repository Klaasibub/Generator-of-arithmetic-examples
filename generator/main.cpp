#include <iostream>
#include <ctime>
#include "Generator.hpp"
using namespace std; 
int main(){
   srand(time(NULL));
   Generator gen;
   try{
      gen.input();
      gen.generate();
   }
   catch(GeneratorError &e){
      cout<<"\n";
      cout<<e.message()<<"\n";
   }
}
