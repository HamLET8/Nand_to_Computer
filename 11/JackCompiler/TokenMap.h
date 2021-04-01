#ifndef _TOKENMAP_
#define _TOKENMAP_

class TokenMap{
public:
	enum typeOfToken{
		KEYWORD,SYMBOL,IDENTIFIER,INT_CONST,STRING_CONST
	};
	
	
	TokenMap(){
		
		TokenTypeMap["class"] 		= KEYWORD;
		TokenTypeMap["method"] 		= KEYWORD;
		TokenTypeMap["int"] 		= KEYWORD;
		TokenTypeMap["function"] 	= KEYWORD;
		TokenTypeMap["boolean"] 	= KEYWORD;
		TokenTypeMap["constructor"] = KEYWORD;
		TokenTypeMap["char"]		= KEYWORD;
		TokenTypeMap["void"] 		= KEYWORD;
		TokenTypeMap["var"] 		= KEYWORD;
		TokenTypeMap["static"] 		= KEYWORD;
		TokenTypeMap["field"] 		= KEYWORD;
		TokenTypeMap["let"] 		= KEYWORD;
		TokenTypeMap["do"] 			= KEYWORD;
		TokenTypeMap["if"] 			= KEYWORD;
		TokenTypeMap["else"] 		= KEYWORD;
		TokenTypeMap["while"] 		= KEYWORD;
		TokenTypeMap["return"] 		= KEYWORD;
		TokenTypeMap["true"] 		= KEYWORD;
		TokenTypeMap["false"] 		= KEYWORD;
		TokenTypeMap["null"] 		= KEYWORD;
		TokenTypeMap["this"] 		= KEYWORD;
		
		TokenTypeMap["{"] 			= SYMBOL;
		TokenTypeMap["}"] 			= SYMBOL;
		TokenTypeMap["("] 			= SYMBOL;
		TokenTypeMap[")"] 			= SYMBOL;
		TokenTypeMap["["] 			= SYMBOL;
		TokenTypeMap["]"] 			= SYMBOL;
		TokenTypeMap["."] 			= SYMBOL;
		TokenTypeMap[","] 			= SYMBOL;
		TokenTypeMap[";"] 			= SYMBOL;
		TokenTypeMap["+"] 			= SYMBOL;
		TokenTypeMap["-"] 			= SYMBOL;
		TokenTypeMap["*"] 			= SYMBOL;
		TokenTypeMap["/"] 			= SYMBOL;
		TokenTypeMap["&"] 			= SYMBOL;
		TokenTypeMap["|"] 			= SYMBOL;
		TokenTypeMap["<"] 			= SYMBOL;
		TokenTypeMap[">"] 			= SYMBOL;
		TokenTypeMap["="] 			= SYMBOL;
		TokenTypeMap["~"] 			= SYMBOL;	
	}
	
	bool findVal(const string&val)
	{
		if(TokenTypeMap.find(val)!=TokenTypeMap.end())
			return true;
		else
			return false;
	}
	
	typeOfToken getVal(const string&val){
		return TokenTypeMap[val];
	}
	
private:
	
	map<string,typeOfToken> TokenTypeMap;
	
};


#endif
