#include"SymbolTable.h"

SymbolTable::SymbolTable()
:staCnt(0),fieldCnt(0),varCnt(0),argCnt(0)
{ }
	
void SymbolTable::startSubroutine()
{
	varCnt = argCnt = 0;
	subrtSymbolTable.clear();
}

void SymbolTable::Define(const string& name,const string& type,const string& kind)
{
		if(kind == "FIELD")
			classSymbolTable[name] = InfoSymbol(type,kind,fieldCnt++);
		else if(kind == "STATIC")
			classSymbolTable[name] = InfoSymbol(type,kind,staCnt++);
		else if(kind == "VAR")	
			subrtSymbolTable[name] = InfoSymbol(type,kind,varCnt++);
		else if(kind == "ARG")	
			subrtSymbolTable[name] = InfoSymbol(type,kind,argCnt++);			
}
	
int SymbolTable::VarCount(string kind)
{
	if(kind == "FIELD")
			return fieldCnt;
	if(kind == "STATIC")			
			return staCnt;
	if(kind == "VAR")
			return varCnt;
 	if(kind == "ARG")			
			return argCnt;
	return 0;

}
	
string SymbolTable::KindOf(const string& varName)
{
	if(subrtSymbolTable.find(varName) !=  subrtSymbolTable.end())	// sub symbol table dont have the var
	{
		InfoSymbol typeInfo = subrtSymbolTable[varName];
		return typeInfo.kind;			
	}
	else if(classSymbolTable.find(varName) !=  classSymbolTable.end() )	// not in class level	
	{
		InfoSymbol typeInfo(classSymbolTable[varName]);
		return typeInfo.kind;
	}
	else
		return "NONE";
	
	
}
	
string SymbolTable::TypeOf(const string &varName)
{
	if(subrtSymbolTable.find(varName) !=  subrtSymbolTable.end())	// sub symbol table dont have the var
	{
		InfoSymbol typeInfo = subrtSymbolTable[varName];
		return typeInfo.type;			
	}
	else if(classSymbolTable.find(varName) !=  classSymbolTable.end() )	// not in class level	
	{
		InfoSymbol typeInfo(classSymbolTable[varName]);
		return typeInfo.type;
	}
	else
		return string("not variable");
}
	
int SymbolTable::IndexOf(const string &varName)
{
	if(subrtSymbolTable.find(varName) !=  subrtSymbolTable.end())	// sub symbol table dont have the var
	{
		InfoSymbol typeInfo = subrtSymbolTable[varName];
		return typeInfo.index;			
	}
	else if(classSymbolTable.find(varName) !=  classSymbolTable.end() )	// not in class level	
	{
		InfoSymbol typeInfo(classSymbolTable[varName]);
		return typeInfo.index;
	}
	else
		return -1;
}

