#ifndef _COMPILATIONENGINE_
#define _COMPILATIONENGINE_
#include "TokenMap.h"
#include "KeywordMap.h"
#include "JackTokenizer.h"

class CompilationEngine
{
public:
	CompilationEngine(const string &,const string &);
	
	void CompileClass();
	void CompileClassVarDec();
	void CompileSubroutine();
	void CompileParameterList();
	void CompileVarDec();
	void CompileStatements();
	void CompileDo();
	void CompileLet();
	void CompileWhile();
	void CompileReturn();
	void CompileIf();
	void CompileExpression();
	void CompileTerm();
	void CompileExpressionList();
	void MatchToken();
private:
	JackTokenizer tokenizer; 	
	ofstream outSyntaxFile;

	
};


#endif
