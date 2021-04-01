#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;
#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(const string &inputF,const string &outputF)
:tokenizer(inputF) ,Vwriter(outputF),wh_lab(0),if_lab(0),nArgs(0)
{	
//string tempWatch = tokenizer.getCurrToken();
	CompileClass();			//Begining
	Vwriter.close();	
}
	
void CompilationEngine::CompileClass(){
	
//	// outSyntxFile << "<class>" << endl;
	
	MatchToken();		//class
	crr_className = MatchToken();		//IDENTIFIER
	MatchToken();		//"{"
	CompileClassVarDec();
	CompileSubroutine();
	MatchToken();		//"}"

//	Vwriter.writeFunction(className,)		
//	// outSyntxFile << "</class>" << endl;
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
		
		//// outSyntxFile << "<classVarDec>" << endl;
		 
		string Kind = MatchToken(); // kind FIELD or STATIC	
		
		string typeVarName = MatchToken(); // type int char boolean 
				
		string VarName = MatchToken(); // varName
		
		symTab.Define(VarName,typeVarName,Kind);
		
		
		
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() != ";")
		{		
			MatchToken(); // ,
			string VarName = MatchToken(); // varName
		
			symTab.Define(VarName,typeVarName,Kind);		
		}		
		
		MatchToken(); // ;
	
		// outSyntxFile << "</classVarDec>" << endl;	
	}
	
}

void CompilationEngine::CompileSubroutine()
{
	bool notMatch = false;
		
	while(true){	// ()*
		
		int varNum = -1;	
		switch(tokenizer.keyword())
		{		
			case KeywordMap::METHOD:
				varNum = 1;
				//symTab.setArg(); // argCnt ++ ;
				break;
			case KeywordMap::FUNCTION:
				varNum = 0;				
				break;
			case KeywordMap::CONSTRUCTOR:
				varNum = 0;			
				break;
			
			default:
				notMatch = true;
				break;				
		}
		
		if(notMatch) break; //if  current char dont belong to First()
		
		// outSyntxFile << "<subroutineDec>" << endl;
		
		string funcKind = MatchToken(); // method . constructor , function
		
		string funcType = MatchToken(); // (void|type)

		
		if(funcKind == "METHOD"){
			symTab.Define(string("this"),funcType,string("ARG"));	
		}
		
		
		string funcName  = 	MatchToken();	// subroutineName
		
		MatchToken();	//"("
		
		CompileParameterList(); //ParameterList
		
		MatchToken();	//")"

		
	/* subroutineBody  */
	//	// outSyntxFile << "<subroutineBody>" << endl;
		
		MatchToken();	//"{"
				
		CompileVarDec(); //varDeclaration
		
		Vwriter.writeFunction(crr_className + "." + funcName, symTab.VarCount("VAR")); 	// function name index
		
		if(funcKind == "METHOD"){
			if(symTab.VarCount("ARG")!=0){
				Vwriter.writePush("ARG",0);	// this = &className
				Vwriter.writePop("POINTER",0);
			}		
		}
		
	//	Vwriter.writeCall(funcKind,1);//test
		if(funcKind == "CONSTRUCTOR"){
			Vwriter.writePush("CONST",symTab.VarCount("FIELD"));
			Vwriter.writeCall("Memory.alloc",1);
			Vwriter.writePop("POINTER",0);
		}
		
	
		CompileStatements();	//statements
		
		MatchToken();	//"}"
			
		symTab.startSubroutine(); // clear the subTable
		

		
	}
}

void CompilationEngine::CompileParameterList()
{
	// outSyntxFile << "<parameterList>" << endl;
	bool notMatch = false;
		
	while(true){	// ()*
			
		switch(tokenizer.keyword())		//primitive type
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
				break;
			default:
				notMatch = true;
				break;	
			} 	
		}
		
		
				
		if(notMatch) break; //if  current char dont belong to First()
		
		string typeVarName = tokenizer.getCurrToken();
		
		MatchToken();	// type	
		
		string VarName = tokenizer.getCurrToken();
		
		MatchToken();	// varName
		
		symTab.Define(VarName,typeVarName,string("ARG"));
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ",")
		{		
			MatchToken(); // ,
			string typeVarName 	= MatchToken(); // type
			string VarName 		= MatchToken(); // varName	
			
			symTab.Define(VarName,typeVarName,string("ARG"));
		}			
			
	}
	// outSyntxFile << "</parameterList>" << endl;	
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
		
		// outSyntxFile << "<varDec>" << endl;
		
		string kindVarName 	= MatchToken();; // var
				
		string typeVarName 	= MatchToken(); // type
		
		string VarName 		= MatchToken(); // varname
		
		symTab.Define(VarName,typeVarName,kindVarName);
		
		while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() != ";")
		{		
			MatchToken(); // ,
			string VarName = MatchToken(); // varName
			
		    symTab.Define(VarName,typeVarName,kindVarName);	
		}		
		
		MatchToken(); // ;
	
		// outSyntxFile << "</varDec>" << endl;	
		
	}
}

void CompilationEngine::CompileStatements()
{
	// outSyntxFile << "<statements>" << endl;
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

}

void CompilationEngine::CompileDo()	
{
	// outSyntxFile << "<doStatement>" << endl;
	MatchToken(); // do 
	
	/** sunroutine call **/
	string className,subName,classVarName;
	
	switch(tokenizer.nextTokenType())
	{
		case JackTokenizer::PARA:		//sub(),or function()
			subName = MatchToken(); // subroutine name
			MatchToken(); // (
			Vwriter.writePush("POINTER",0);
			nArgs = 0;
			CompileExpressionList(nArgs);
			
			MatchToken(); // )

			Vwriter.writeCall(crr_className+ "."  + subName,nArgs+1);	//sys
			break;
			
		case JackTokenizer::DOT:
			
			if(symTab.KindOf(tokenizer.getCurrToken()) == "NONE")		//sys.sub();		
						{
							string ClasstName = MatchToken(); // className
							MatchToken(); // .
							string methodName = MatchToken(); // subroutineName
							MatchToken(); // (
							nArgs = 0;
							CompileExpressionList(nArgs);	// push arg 1,2....
							MatchToken(); // )
					
							Vwriter.writeCall(ClasstName + "." + methodName , nArgs);	
						}else	// obj.sub()
						{
							string objectName = MatchToken(); // className  or objectName 
							
							Vwriter.writePush(symTab.KindOf(objectName),symTab.IndexOf(objectName));	// push arg0
						//	Vwriter.writePop("ARG",0);	
							MatchToken(); // .
							string methodName = MatchToken(); // subroutineName
							MatchToken(); // (
							nArgs = 0;
							CompileExpressionList(nArgs);	// push arg 1,2....
							MatchToken(); // )
												
							Vwriter.writeCall(symTab.TypeOf(objectName)+ "." + methodName , nArgs+1); // call class_subroutine nArgs 
						}
		
			break;	
			
		default:
			break;				
	}
		MatchToken(); // ;
		Vwriter.writePop("TEMP",0);	
	// outSyntxFile << "</doStatement>" << endl;
	
		
}

void CompilationEngine::CompileLet()
{
	// outSyntxFile << "<letStatement>" << endl;
		MatchToken(); // let
		
		string varName = MatchToken(); // varName
		
		if(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == "[")	//let a[exp] = exp 
		{
			Vwriter.writePush(symTab.KindOf(varName),symTab.IndexOf(varName));	
			MatchToken(); // [
			CompileExpression();
			MatchToken(); // ]
			Vwriter.writeArithmetic(string("+"));
			Vwriter.writePop("TEMP",1);
			
			MatchToken(); // =
		
			CompileExpression();
			
			Vwriter.writePush("TEMP",1);
			Vwriter.writePop("POINTER",1);
				
			Vwriter.writePop("THAT",0);		
		}
		else
		{
			MatchToken(); // =
		
			CompileExpression();
		
			Vwriter.writePop(symTab.KindOf(varName),symTab.IndexOf(varName));
		}				
		
			MatchToken(); // ;
		
	// outSyntxFile << "</letStatement>" << endl;
}

void CompilationEngine::CompileWhile()
{
	string exitLabel = "WHILE_END" + to_string(wh_lab);
	string loopLabel = "WHILE_EXP" + to_string(wh_lab++);
	// outSyntxFile << "<whileStatement>" << endl;
	MatchToken(); //while
	MatchToken(); //(
	
	Vwriter.writeLabel(loopLabel);	//loop to check condition
	CompileExpression();
	Vwriter.writeArithmetic("~");	
	Vwriter.writeIf(exitLabel);
	
	MatchToken(); //)
	MatchToken(); //{
	CompileStatements();
	MatchToken(); //}
	Vwriter.writeGoto(loopLabel);
	
	Vwriter.writeLabel(exitLabel);
	// outSyntxFile << "</whileStatement>" << endl;

}

void CompilationEngine::CompileReturn()
{
	// outSyntxFile << "<returnStatement>" << endl;
	MatchToken(); // return
	
	if(tokenizer.getCurrToken() != ";" )
	{
		CompileExpression();
		
	}else{
		Vwriter.writePush("CONST",0);
	}
	
	MatchToken(); // ;
	Vwriter.writeReturn();
	// outSyntxFile << "</returnStatement>" << endl;
}

void CompilationEngine::CompileIf()
{
	string trueLabel = "IF_TRUE_"  + to_string(if_lab);
	string elseLabel = "IF_FALSE_" + to_string(if_lab);
	string exitLabel = "IF_END_"  + to_string(if_lab++);
	// outSyntxFile << "<ifStatement>" << endl;
	MatchToken(); //if
	MatchToken(); //(
	CompileExpression();

	Vwriter.writeIf(trueLabel);
	
	Vwriter.writeGoto(elseLabel);
	Vwriter.writeLabel(trueLabel);
	
	MatchToken(); //)
	MatchToken(); //{
	CompileStatements();
	MatchToken(); //}
	

	
	if(tokenizer.tokenType() == TokenMap::KEYWORD && tokenizer.keyword()== KeywordMap::ELSE)
	{	
		Vwriter.writeGoto(exitLabel);
		Vwriter.writeLabel(elseLabel);	
		MatchToken(); //else
		MatchToken(); //{
		CompileStatements();
		MatchToken(); //}
		Vwriter.writeLabel(exitLabel);
	}
	else{
		Vwriter.writeLabel(elseLabel);	
	}
	
}

void CompilationEngine::CompileExpression()
{

	
	CompileTerm();
	while(tokenizer.currSymbolType() == JackTokenizer::BINOP|| tokenizer.currSymbolType() == JackTokenizer::MINOP )	// (op term)*
	{
		string binOp = MatchToken(); // binary op
		CompileTerm();	
		Vwriter.writeArithmetic(binOp);
	}
	
	// outSyntxFile << "</expression>" << endl;	
}


void CompilationEngine::CompileTerm()
{
	// outSyntxFile << "<term>" << endl;
	
	switch(tokenizer.tokenType()){
			
			case TokenMap::IDENTIFIER:	// next token  : 1,Varname() 2, varName.call()  3,varName[] 4,NAME
			
				
				switch(tokenizer.nextTokenType())	//lookahead
				{		
					case JackTokenizer::DOT:	
						{
									
						if(symTab.KindOf(tokenizer.getCurrToken()) == "NONE")		
						{
							string ClasstName = MatchToken(); // className
							MatchToken(); // .
							string methodName = MatchToken(); // subroutineName
							MatchToken(); // (
							nArgs = 0;
							CompileExpressionList(nArgs);	// push arg 1,2....
							MatchToken(); // )
							
					//		if(methodName != "new") nArgs++;
							
							if(symTab.TypeOf(methodName) != "not variable") nArgs++;;
						//	Vwriter.writeLabel("Here error!");
							Vwriter.writeCall(ClasstName + "." + methodName , nArgs);	
						}else
						{
							string objectName = MatchToken(); // className  or objectName 
							Vwriter.writePush(symTab.KindOf(objectName),symTab.IndexOf(objectName));	// push arg0
							MatchToken(); // .
							string methodName = MatchToken(); // subroutineName
							MatchToken(); // (
							nArgs = 0;
							CompileExpressionList(nArgs);	// push arg 1,2....
							MatchToken(); // )
						//	Vwriter.writeLabel("Here error!");
							Vwriter.writeCall(symTab.TypeOf(objectName) +"."+ methodName , nArgs+1); // call class_subroutine nArgs 
						}
						
						break;	
						}
						
						
					case JackTokenizer::TAN:	//array index
					{
						string VarName = MatchToken(); // varName
						Vwriter.writePush(symTab.KindOf(VarName),symTab.IndexOf(VarName));		
						MatchToken(); // [
						CompileExpression();
						MatchToken(); // ]
						Vwriter.writeArithmetic(string("+"));
						Vwriter.writePop("POINTER",1);
						Vwriter.writePush("THAT",0);	
						break;
					}
					
						
					default:
						{
						string VarName = MatchToken(); // varName
						Vwriter.writePush(symTab.KindOf(VarName),symTab.IndexOf(VarName));
						break;
						}
						
				}
				
				break;
								
			case TokenMap::KEYWORD:
				{		
				string currKeyC = MatchToken(); // Keyconstant
				
			//	Vwriter.writeFunction(currKeyC,0);//test
				
				if(currKeyC == "FALSE" || currKeyC == "NULL")
				{
					Vwriter.writePush("CONST",0);
				}		
				else if(currKeyC == "TRUE"){
					Vwriter.writePush("CONST",0);
					Vwriter.writeArithmetic(string("~"));
					}
				else if(currKeyC == "THIS"){
					Vwriter.writePush("POINTER",0);
				}						
				}
			break;
	
			case TokenMap::SYMBOL:				//  1 "(" expression,  2 binary op  , 3 unary op 
				
				switch(tokenizer.currSymbolType())
				{
					case JackTokenizer::PARA:
						MatchToken(); // (
						CompileExpression();
						MatchToken(); // )												
						break;
						
					case JackTokenizer::NOTOP:	//~
					{
						string op = MatchToken();
						CompileTerm();
						Vwriter.writeArithmetic(op);
						break;
					}
							
							
					case JackTokenizer::MINOP:	//-
					{
						string op = "n";
						MatchToken(); // unary op
						CompileTerm();
						Vwriter.writeArithmetic(op);
						break;
					}
						
					
					default:
						break;						
				}
				break;
	
			case TokenMap::INT_CONST:
				{
				int varInt = stoi(MatchToken()); // INT_CONST:
				Vwriter.writePush("CONST",varInt);
				break;	
				}
				
				
			case TokenMap::STRING_CONST:
				{
				string str = tokenizer.stringVal();
				
				MatchToken(); // STRING_CONST:
				Vwriter.writePush("CONST", str.length());
				Vwriter.writeCall("String.new", 1);
				
				for(auto c : str){
					Vwriter.writePush("CONST",c);
					Vwriter.writeCall("String.appendChar", 2);	
				}
				
				break;
				}
				
				
				
			default:
				break;	
		}		
		
}



void CompilationEngine::CompileExpressionList(int &nArg)
{

	bool notMatch = false;
	
	if(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ")")
		notMatch = true;
	
	if(notMatch)
	{
	
		return;
	 } 	
	
	CompileExpression();
	++nArg;
	while(tokenizer.tokenType() == TokenMap::SYMBOL && tokenizer.symbol() == ",")
	{
		MatchToken(); // ,
		CompileExpression();
		++nArg;
	}
	

}

string CompilationEngine::MatchToken(){

		string tempCrrToken =  tokenizer.getCurrToken();

		if(tokenizer.tokenType() == TokenMap::KEYWORD)	// upper the key word
		{
			for(auto &c : tempCrrToken)
				c = toupper(c);
		}
		tokenizer.advance();
		return tempCrrToken;
		
}



