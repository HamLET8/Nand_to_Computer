#ifndef _PARSER_
#define _PARSER_

#include<map>
#include <vector>

using namespace std;
class Parser{

public:
	Parser(const string&);
	
	bool hasMoreCommands();
	void advance();
	
	enum typeC{C_NULL,C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL };
	
	typeC commandType ();
	string  Arg1() const;
	int  Arg2() const;
	
private:
	vector<string> file;
	map<string ,typeC> typeMap;
	int crrCom;
	
};
#endif
