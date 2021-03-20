#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;
#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(const string &inputF,const string &outputF)
:tokenizer(inputF)
{
	outSyntaxFile.open(outputF);
	
	
	if(outSyntaxFile) 			
		cout << "open output file successfully" << endl;
	else
	{
			cout << "open output failed" << endl;
	}
	CompileClass();			//Begining
	
	outSyntaxFile.close();
	
}
	
void CompilationEngine::CompileClass(){
	
	outSyntaxFile << "<class>" << endl;
	
	MatchToken();		//class
	MatchToken();		//IDENTIFIER
	MatchToken();		//"{"
	CompileClassVarDec();
	CompileSubroutine();
	MatchToken();		//"}"
		
	outSyntaxFile << "</class>" << endl;
}

void CompilationEngine::CompileClassVarDec()
{
	bool notMatch = false;
	
	while(true){
		
		switch(tokenizer.keyword())
		{
			case KeywordMap::STATIC:
			case KeywordMap::FIELD:
				break;
			default:
				notMatch = true;
				break;
		}
		if(notMatch) break; //if  current char dont belong to First()
		
		outSyntaxFile << "<classVarDec>" << endl;
		MatchToken(); // static field 		
		MatchToken(); // type int void 
		MatchToken(); // varName
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() != ";")
		{		
			MatchToken(); // ,
			MatchToken(); // varName		
		}		
		
		MatchToken(); // ;
	
		outSyntaxFile << "</classVarDec>" << endl;	
	}
	
}

void CompilationEngine::CompileSubroutine()
{
	bool notMatch = false;
		
	while(true){	// ()*
			
		switch(tokenizer.keyword())
		{
			case KeywordMap::METHOD:
			
			case KeywordMap::FUNCTION:			
				
			case KeywordMap::CONSTRUCTOR:			
				break;
			
			default:
				notMatch = true;
				break;				
		}
		
		if(notMatch) break; //if  current char dont belong to First()
		
		outSyntaxFile << "<subroutineDec>" << endl;
		
		MatchToken(); // method . constructor , function
		
		MatchToken(); // (void|type)
		
		MatchToken();	// subroutineName
		
		MatchToken();	//"("
	
		CompileParameterList(); //ParameterList
		
		MatchToken();	//")"
		
	/* subroutineBody  */
		outSyntaxFile << "<subroutineBody>" << endl;
		
		MatchToken();	//"{"
				
		CompileVarDec(); //varDeclaration
		
		CompileStatements();	//statements
		
		MatchToken();	//"}"	 
		outSyntaxFile << "</subroutineBody>" << endl;
		outSyntaxFile << "</subroutineDec>" << endl;
	}
}

void CompilationEngine::CompileParameterList()
{
	outSyntaxFile << "<parameterList>" << endl;
	bool notMatch = false;
		
	while(true){	// ()*
			
		switch(tokenizer.keyword())
		{
			case KeywordMap::INT:
			
			case KeywordMap::CHAR:			
				
			case KeywordMap::BOOLEAN:
				break;
				
			
			default:
				notMatch = true;
				break;				
		}
		
		if(notMatch){
					
			switch(tokenizer.tokenType())
			{
			case TokenMap::IDENTIFIER:			//className
				notMatch = false;			
			
			default:
				notMatch = true;
				break;	
			} 	
		}
		
		
				
		if(notMatch) break; //if  current char dont belong to First()
		
		MatchToken();	// type	
		MatchToken();	// varName
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ",")
		{		
			MatchToken(); // ,
			MatchToken(); // type
			MatchToken(); // varName		
		}
				
			
	}
	outSyntaxFile << "</parameterList>" << endl;	
}

void CompilationEngine::CompileVarDec()
{
	bool notMatch = false;
	while(true){
		
		switch(tokenizer.keyword())
		{
			case KeywordMap::VAR:
				break;
				
			default:
				notMatch = true;
				break;				
		}
		
		if(notMatch) break; //if  current char dont belong to First() set of VarDec
		
		outSyntaxFile << "<varDec>" << endl;		
		MatchToken(); // var
		MatchToken(); // type
		MatchToken(); // varname
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() != ";")
		{		
			MatchToken(); // ,
			MatchToken(); // varName		
		}		
		
		MatchToken(); // ;
	
		outSyntaxFile << "</varDec>" << endl;	
		
	}
}
void CompilationEngine::CompileStatements()
{
	outSyntaxFile << "<statements>" << endl;
	bool notMatch = false;
	while(true){
		switch(tokenizer.keyword())
		{
			case KeywordMap::LET:
				
				CompileLet();	
				
				break;			
								
			case KeywordMap::IF:
			
				CompileIf();
		
				break;
				
			case KeywordMap::WHILE:
			
				CompileWhile();
			
				break;
				
			case KeywordMap::DO:
			
				CompileDo();
					
				break;
					
			case KeywordMap::RETURN:
			
				CompileReturn();
			
				break;
								
			default:
				notMatch = true;
				break;				
		}
		
		if(notMatch) break; //if  current char doesn`t belong to First() set of VarDec			
	}
	outSyntaxFile << "</statements>" << endl;
}
void CompilationEngine::CompileDo()
{
	outSyntaxFile << "<doStatement>" << endl;
	MatchToken(); // do 
	
	/** sunroutine call **/
	
	
	
	switch(tokenizer.nextTokenType())
	{
		case JackTokenizer::PARA:
			MatchToken(); // subroutine name
			MatchToken(); // (
			CompileExpressionList();
			MatchToken(); // )
				MatchToken(); // ;
			break;
			
		case JackTokenizer::DOT:
			MatchToken(); // subroutine name
			MatchToken(); // .
			MatchToken(); // subroutineName
			MatchToken(); // (
			CompileExpressionList();
			MatchToken(); // )
			MatchToken(); // ;
			break;	
			
		default:
			break;
				
	}
	outSyntaxFile << "</doStatement>" << endl;
		
}

void CompilationEngine::CompileLet()
{
	outSyntaxFile << "<letStatement>" << endl;
		MatchToken(); // let
		MatchToken(); // varName
		if(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == "[")
		{
			MatchToken(); // [
			CompileExpression();
			MatchToken(); // ]		
		}
							
		MatchToken(); // =
		CompileExpression();
		MatchToken(); // ;
		
	outSyntaxFile << "</letStatement>" << endl;
}

void CompilationEngine::CompileWhile()
{
	outSyntaxFile << "<whileStatement>" << endl;
	MatchToken(); //while
	MatchToken(); //(
	CompileExpression();
	MatchToken(); //)
	MatchToken(); //{
	CompileStatements();
	MatchToken(); //}
	outSyntaxFile << "</whileStatement>" << endl;

}

void CompilationEngine::CompileReturn()
{
	outSyntaxFile << "<returnStatement>" << endl;
	MatchToken(); // return
	
	if(tokenizer.tokenType() == TokenMap::IDENTIFIER || tokenizer.tokenType() == TokenMap::KEYWORD )
	{
		CompileExpression();
	}
	
	MatchToken(); // ;
	outSyntaxFile << "</returnStatement>" << endl;
}

void CompilationEngine::CompileIf()
{
	outSyntaxFile << "<ifStatement>" << endl;
	MatchToken(); //if
	MatchToken(); //(
	CompileExpression();
	MatchToken(); //)
	MatchToken(); //{
	CompileStatements();
	MatchToken(); //}
	
	if(tokenizer.tokenType() == TokenMap::KEYWORD && tokenizer.keyword()== KeywordMap::ELSE)
	{
		MatchToken(); //else
		MatchToken(); //{
		CompileStatements();
		MatchToken(); //}
	}
	outSyntaxFile << "</ifStatement>" << endl;	
}

void CompilationEngine::CompileExpression()
{
	outSyntaxFile << "<expression>" << endl;
	
	CompileTerm();
	while(tokenizer.currSymbolType() == JackTokenizer::BINOP|| tokenizer.currSymbolType() == JackTokenizer::MINOP )	// (op term)*
	{
		MatchToken(); // binary op
		CompileTerm();	
	}
	
	outSyntaxFile << "</expression>" << endl;	
}


void CompilationEngine::CompileTerm()
{
	outSyntaxFile << "<term>" << endl;
	
	switch(tokenizer.tokenType()){
			
			case TokenMap::IDENTIFIER:	// next token  : 1,Varname() 2, varName.call()  3,varName[] 4,NAME
			
				
				switch(tokenizer.nextTokenType())	//lookahead
				{
					case JackTokenizer::PARA:	//call
						MatchToken(); // varName
						MatchToken(); // (
						CompileExpressionList();
						MatchToken(); // )
						break;
						
					case JackTokenizer::DOT:
						MatchToken(); // varName
						MatchToken(); // .
						MatchToken(); // subroutineName
						MatchToken(); // (
						CompileExpressionList();
						MatchToken(); // )
						break;
						
					case JackTokenizer::TAN:	//array index
						MatchToken(); // varName
						MatchToken(); // [
						CompileExpression();
						MatchToken(); // ]
						break;
						
					default:
						MatchToken(); // varName
						break;
				}
				
				break;
								
			case TokenMap::KEYWORD:
			
				MatchToken(); // Keyconstant
				break;
				
				
			case TokenMap::SYMBOL:				//  1 "(" expression,  2 binary op  , 3 unary op 
				
				switch(tokenizer.currSymbolType())
				{
					case JackTokenizer::PARA:
						MatchToken(); // (
						CompileExpression();
						MatchToken(); // )												
						break;
						
					case JackTokenizer::NOTOP:
					case JackTokenizer::MINOP:
						MatchToken(); // unary op
						CompileTerm();
						break;
					
					default:
						break;						
				}
				break;
	
			case TokenMap::INT_CONST:
				MatchToken(); // INT_CONST:
				break;
				
			case TokenMap::STRING_CONST:
				MatchToken(); // STRING_CONST:
				break;
				
			default:
				break;	
		}		
	outSyntaxFile << "</term>" << endl;		
}



void CompilationEngine::CompileExpressionList()
{
	outSyntaxFile << "<expressionList>" << endl;
	bool notMatch = false;
	
	if(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ")")
		notMatch = true;
	
	if(notMatch)
	{
		outSyntaxFile << "</expressionList>" << endl;
		return;
	 } 
	
	
	CompileExpression();
	
	while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ",")
	{
		MatchToken(); // ,
		CompileExpression();
	}
	
	outSyntaxFile << "</expressionList>" << endl;
}

void CompilationEngine::MatchToken(){
	
		switch(tokenizer.tokenType()){
			
			case TokenMap::IDENTIFIER:
				outSyntaxFile<< "<identifier> " << tokenizer.identifier() << " </identifier>" << endl;
				break;
								
			case TokenMap::KEYWORD:
				outSyntaxFile << "<keyword> " << tokenizer.keywordVal() << " </keyword>" << endl;  ///
				break;
				
			case TokenMap::SYMBOL:
				outSyntaxFile << "<symbol> " << tokenizer.symbol() << " </symbol>" << endl;
				break;
	
			case TokenMap::INT_CONST:
				outSyntaxFile << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << endl;
				break;
				
			case TokenMap::STRING_CONST:
				outSyntaxFile << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << endl;
				break;
				
			default:
				cout << "error ! " << endl;
				break;	
		}
		
		tokenizer.advance();
}

