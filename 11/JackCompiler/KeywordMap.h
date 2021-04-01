#ifndef _KEYWORDMAP_
#define _KEYWORDMAP_

class KeywordMap{
public:
	enum typeOfKeyword{
		CLASS,METHOD,INT,FUNCTION,BOOLEAN,CONSTRUCTOR,CHAR,
		W_VOID,VAR,STATIC,FIELD,LET,DO,IF,ELSE,WHILE,RETURN,
		W_TRUE,W_FALSE,W_NULL,W_THIS
	};
	
	KeywordMap(){
		
			keywordMap["class"] 	= CLASS;
			keywordMap["method"] 	= METHOD;
			keywordMap["int"] 		= INT;
			keywordMap["function"] 	= FUNCTION;
			keywordMap["boolean"] 	= BOOLEAN;
			keywordMap["constructor"]= CONSTRUCTOR;
			keywordMap["char"]		= CHAR;
			keywordMap["var"] 		= VAR;
			keywordMap["static"] 	= STATIC;
			keywordMap["field"] 	= FIELD;
			keywordMap["let"] 		= LET;
			keywordMap["do"] 		= DO;
			keywordMap["if"] 		= IF;
			keywordMap["else"] 		= ELSE;
			keywordMap["while"] 	= WHILE;
			keywordMap["return"] 	= RETURN;
			keywordMap["true"] 		= W_TRUE;
			keywordMap["false"] 	= W_FALSE;
			keywordMap["null"] 		= W_NULL;
			keywordMap["this"] 		= W_THIS;
			keywordMap["void"] 		= W_VOID;		
	}
	
	bool findVal(const string &val){
		
		if(keywordMap.find(val)!=keywordMap.end())
			return true;
		else
			return false;
	}
	
	typeOfKeyword getVal(const string&val){
		return keywordMap[val];
	}
	
private:
	map<string,typeOfKeyword> keywordMap;
};


#endif
