#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_
#include <iostream>
#include <map>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class SymbolTable;


struct InfoSymbol{	
	//	enum idKind{
	//	NONE,STATIC,FIELD,ARG,VAR
	//	}; 
		InfoSymbol()=default;
		InfoSymbol(string a,string b,int c)
		:type(a) , kind(b) ,index(c)
		{}
	
		string type;
		string kind;
		int index;
};


	
class SymbolTable{

public:
	SymbolTable();
	

	

	
	void startSubroutine();
	
	void Define(const string&,const string&,const string&);
	
	int VarCount(string kind);
	
	string KindOf(const string&);
	
	string TypeOf(const string &);
	
	int IndexOf(const string &);
	


private:
	int staCnt,fieldCnt,varCnt,argCnt;
	map<string,InfoSymbol> classSymbolTable;
	map<string,InfoSymbol> subrtSymbolTable;
};



#endif 
