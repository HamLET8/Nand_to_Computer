#ifndef _COMPILATIONENGINE_
#define _COMPILATIONENGINE_
#include "TokenMap.h"
#include "KeywordMap.h"
#include "JackTokenizer.h"
#include "SymbolTable.h"
#include "VMWriter.h"

class CompilationEngine
{
public:
	CompilationEngine(const string &,const string &);
	
	void CompileClass();//get
	void CompileClassVarDec();//get
	void CompileSubroutine();//get
	void CompileParameterList();//get
	void CompileVarDec();//get
	void CompileStatements();//get
	void CompileDo();//get
	void CompileLet();//get
	void CompileWhile();//get
	void CompileReturn();//get
	void CompileIf();//get
	void CompileExpression();//
	void CompileTerm();//string const
	void CompileExpressionList(int &);//get
	string MatchToken();	// advance
	string getVarKind();
private:
	JackTokenizer tokenizer;
	VMWriter Vwriter;	
//	ofstream outSyntaxFile;
	SymbolTable symTab;
	string crr_className;
	size_t wh_lab,if_lab;
	int nArgs;
	
};


#endif
