#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <iostream>
#include <fstream>
using namespace std;
class Example;
class Generator;

struct GeneratorError { // ������� ����� ��� ������
   virtual ~GeneratorError() {} // ����������
   virtual const char *message() const=0; // ��������� ��� ������
};
struct DataError: GeneratorError {
   const char *message() const {return "������ ��������� �����.";} 
};
struct GenerationError: GeneratorError {
   const char *message() const {return "������ ���������";} 
};

class Generator{
   int examples,operations,Min,Max,checkbox[5];
   string file;
   Example* operand(int num,int decomp);
public:
   void generate();
   void input();
   Example* generateExample();
};
class Example{
   friend Generator;
   Example *left,*right;
   int priority,answer;
   char oper;
   string result;
public:
   Example(int answer);
   Example(Example& left,char oper,Example& right);
   Example(Example &right);
   ~Example();
};
#endif