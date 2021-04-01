#ifndef _JACKTOKENIZER_
#define _JACKTOKENIZER_
#include <vector>
#include "TokenMap.h"
#include "KeywordMap.h"
#include "SymbolTable.h"

class JackTokenizer{
	
public:
	enum nextToken{
		N_NULL,PARA,DOT,TAN,BINOP,NOTOP,MINOP	//  (   .   [ unaryOP binaryOp
	};
	
	JackTokenizer(const string &);		
	bool hasMoreTokens();
	void advance();

	int intVal();
	string symbol();
	string keywordVal();
	string stringVal();	
	string identifier();
	
	nextToken nextTokenType();		//lookahead for LL(2)
	nextToken currSymbolType();		//term(op term)
	
	TokenMap::typeOfToken tokenType();		
	KeywordMap::typeOfKeyword keyword();
	string getCurrToken();//api for SymbolTable

private:
	KeywordMap keywordMap;
	TokenMap tokenMap;
	map<string ,nextToken> operatorMap;
	std::vector<string> tokenFile;
	size_t crrToken;

	
};




#endif
