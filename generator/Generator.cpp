#include <iostream>
#include <cmath>
#include <vector>
#include "Generator.hpp"
using namespace std; 
Example::Example(int answer):answer(answer),left(0),right(0),oper(0){
   if (answer>=0)
      result=to_string(answer);
   else
      result = "("+to_string(answer)+")";
   priority=5;
}
Example::Example(Example &right) : oper(oper), left(nullptr),right(&right){
   priority=0;
   result='-';
   if (answer<0) 
      result+='('+right.result+')';
   else 
      result+=right.result;
   answer=-right.answer;
}
Example::Example(Example &left,char oper,Example &right) : oper(oper), left(&left), right(&right){
   switch(oper){
      case '+':
         priority=1;
         answer=left.answer+right.answer;
         break;
      case '-':
         priority=2;
         answer=left.answer-right.answer;
         break;
      case '*':
         priority=3;
         answer=left.answer*right.answer;
         break;
      case ':':
         priority=4;
         answer=left.answer/right.answer;
         break;
   }
   if(priority > left.priority && left.priority != 0)
      result+='('+left.result+')';
   else
      result+=left.result;
   result+=' ';
   result+=oper;
   result+=' ' ;
   if(priority >= right.priority || right.priority==2 || right.priority==4)
      result+='('+right.result+')';
   else 
      result+=right.result;
}
Example::~Example(){
   if(left != nullptr)
      delete left;
   if(right != nullptr)
      delete right;
}
void Generator::input(){
   cout << "���������� ��������: ";
   cin >> examples;
   cout << "���������� ��������: ";
   cin >> operations;
   cout << "�������� �����, �������: ";
   cin >> Min;
   cout << "�������� �����, ��������: ";
   cin >> Max;
   cout << "���������� �������������� ��������:\n";
   cout << "2+2?\t";
   cin >> checkbox[0];
   cout << "2-2?\t";
   cin >> checkbox[1];
   cout << "2*2?\t";
   cin >> checkbox[2];
   cout << "2:2?\t";
   cin >> checkbox[3];
   cout << "-(-2)?\t";
   cin >> checkbox[4];
   cout << "��� ����� ��� ������: ";
   cin >> file;
   if(examples < 0 || operations < 0 || Min > Max)
      throw DataError();
   for(int i = 0; i < 5; i++)
      if(checkbox[i])
         return;
   throw DataError();
}
void Generator::generate(){
   Example *instance;
   ofstream to(file.c_str());	
   for(int i = 0; i < examples; i++){
      instance=generateExample();
      to << instance->result << " =\n"<<"�����: " << instance->answer << "\n\n";
      delete instance;
   }
}
Example* Generator::operand(int num,int operations){
   int op1,op2; //������ � ������ ��������
   int N,M,random;    
   char operation;
   string ops="+-*:(";
   if(operations==0)
      return new Example(num);
   while(true){ 
      //1.������� �������������� ��������
      random=rand()%5;
      if(!checkbox[random])
         continue;
      operation=ops[random];
      //2.������� ����� � ��������� ��������� - ��� 1-� �������
      op1=Min+rand()%(Max-Min+1);
      //3.���������� 2-� �������
      if(operation=='+')
         op2=num-op1;
      if(operation=='-')
         op2=op1-num;
      
      if(operation=='*'){
         if(op1 == 0)
            continue;
         op2 = num/op1;
         if(num%op1 && op2 == 0)
            continue;
         op1 = num/op2;
         if(op1 < Min || op1 > Max)
            continue;
      }
      
      if(operation==':'){
         if(num==0)
            continue;
         op2 = op1/num;
         if(op2 == 0)
            continue;
         op1 = num*op2;
         if(op1 < Min || op1 > Max)
            continue;
      }
      //4.���� 2-� ������� ��� ���������, ������� � ���� 1
      if(operation=='(' && (-num>Max || -num<Min || num==0))
         continue;
      if(op2 > Max || op2 < Min) 
         continue;
      break;
   }
   if(operation=='(')
      return new Example(*operand(-num,--operations));
   
   N=rand()%operations; //5.������� �������� N �� 0 �� ����������������-1
   M=operations-N-1;      //6. M=����������������-N-1
   //N - ����� �������� ��� ���������� 1-�� �������� 
   //M - ����� �������� ��� ���������� 2-�� ��������
   return new Example(*operand(op1,N),operation,*operand(op2,M));
}
Example* Generator::generateExample(){
   //������ ��������� ������� ��������� � ��������� ���������.
   int num=Min+rand()%(Max-Min+1);
   return operand(num,operations);
}
