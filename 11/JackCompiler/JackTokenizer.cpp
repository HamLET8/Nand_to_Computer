#include <iostream>
#include <sstream>
#include <map>
#include <string>

#include <fstream>
#include <algorithm>
using namespace std;
#include "JackTokenizer.h"

JackTokenizer::JackTokenizer(const string &pathF)
:crrToken(0)
{
	ifstream ifs(pathF);
	
	if(ifs)
		cout << "load file succeed !" <<endl; //test
	else
		cout << pathF << "  load file failed !" <<endl; //test
	
	string line;
	string white(" ");
	string blank("");
	bool commentA = false;				// comment  across line /**/
	bool stringSign = false;			//	string keep continuing
	
	while(getline(ifs,line)) {				//load file into vector
		
		int i=0;
		while(isspace(line[i])) ++i;
		
		if(line[i]=='/'){
				
			if(line[i+1] == '*')
			{
				commentA = ( line.find("*/") == string::npos ) ? true : false;		//check whethe the comments /**/ only one row
				
			}
			continue;
		}
		
		while(commentA){								//skip the comments wrap up by  /**/
			commentA = (line.find("*/") == string::npos ) ? true : false;
			getline(ifs,line);
		}
		
		if(!line.size()){			// if current row is blank 
			continue;	
		}
		
		bool symbolSign = false;  //dedicate last turn whether a symbol 		
		string word("");
		
		for(int i = 0 ; i != line.size() ; ++i)
		{		
			char ch = line[i];
	
			if(ch == '\"') {			//the begining or end of a string 
				if(stringSign == false){
					if(word.size())
						tokenFile.push_back(word);
					word = "\"";						
				}else{
					word.append("\"");
					tokenFile.push_back(word);
					word = "";
				}
				stringSign = !stringSign;
				continue;				
			}
				
			if(stringSign){				//if current char belong to string
				word.append(string(1,ch));
				continue;
			}
			
//			if(ch == 47 ) cout << "slash occurs" <<endl ; //test
			
			if(ch == 47  && line[i+1] == 47)	// ignor comments like "\\" , ascii 47 = '\'
				break;	
			
			if (isspace(ch)) {			//ignore the white space next char
				if(word.size())
					tokenFile.push_back(word);
				word = "";
				continue;			
			}

			if(tokenMap.findVal(string(1,ch)))	// current char is a symbol
			{
				if(word.size()&&!symbolSign)								//word is non-blank
				{
					tokenFile.push_back(word);
					word = "";
				}	
				tokenFile.push_back(string(1,ch));
				symbolSign = true;
			}
			else{
				word.append(string(1,ch));
				symbolSign = false;
			}
		}
	}
	
	for(auto c : tokenFile)		//test
	//	cout << c << endl;

		operatorMap["("] 			= JackTokenizer::PARA;
		operatorMap["["] 			= JackTokenizer::TAN;
		operatorMap["."] 			= JackTokenizer::DOT;
		operatorMap[","] 			= JackTokenizer::N_NULL;
		operatorMap["+"] 			= JackTokenizer::BINOP;
		operatorMap["-"] 			= JackTokenizer::MINOP;
		operatorMap["*"] 			= JackTokenizer::BINOP;
		operatorMap["/"] 			= JackTokenizer::BINOP;
		operatorMap["&"] 			= JackTokenizer::BINOP;
		operatorMap["|"] 			= JackTokenizer::BINOP;
		operatorMap["<"] 			= JackTokenizer::BINOP;
		operatorMap[">"] 			= JackTokenizer::BINOP;
		operatorMap["="] 			= JackTokenizer::BINOP;
		operatorMap["~"] 			= JackTokenizer::NOTOP;
}

JackTokenizer::nextToken JackTokenizer::nextTokenType(){
	
	if(hasMoreTokens()){
		
		return operatorMap[tokenFile[crrToken+1]];
		
	}
		return JackTokenizer::N_NULL;
}

JackTokenizer::nextToken JackTokenizer::currSymbolType()
{
	return operatorMap[tokenFile[crrToken]];
}

bool JackTokenizer::hasMoreTokens()
{
//	cout <<"crrToken\t " <<  crrToken << "\ttokenFile.size\t" << tokenFile.size() <<endl; //test
	return (crrToken < tokenFile.size());
	
}
	
void JackTokenizer::advance(){
	if(hasMoreTokens())
		++crrToken;
}
	
TokenMap::typeOfToken JackTokenizer::tokenType(){
	
		string currentToken = tokenFile[crrToken];
		if(tokenMap.findVal(currentToken))
			return tokenMap.getVal(currentToken);
		else if(currentToken[0] == '\"'){	//begin with a "
			return TokenMap::STRING_CONST;	
		}else if(isdigit(currentToken[0])){
			return TokenMap::INT_CONST;		//begin with a digit
		}else 							
			return TokenMap::IDENTIFIER;	// begin with a letter
}
	
KeywordMap::typeOfKeyword JackTokenizer::keyword(){
	return keywordMap.getVal(tokenFile[crrToken]);
}

string JackTokenizer::keywordVal(){
	return tokenFile[crrToken];
}

string JackTokenizer::symbol(){
/*	if(tokenFile[crrToken] == "<")
		return string("&lt;");
	if(tokenFile[crrToken] == ">")
		return string("&gt;");
	if(tokenFile[crrToken] == "&")
		return string("&amp;");
*/
	return tokenFile[crrToken];
}

string JackTokenizer::identifier(){
	return tokenFile[crrToken];
}

int JackTokenizer::intVal(){
	return stoi(tokenFile[crrToken]);
}

string JackTokenizer::stringVal(){
	string currentToken = tokenFile[crrToken];
	currentToken.erase(currentToken.find("\""),1);
	currentToken.erase(currentToken.find("\""),1);
	return 	currentToken;
}

string JackTokenizer::getCurrToken()
{
	return tokenFile[crrToken];
}


