#ifndef _CODEWRITER_
#define	_CODEWRITER_
#include<fstream>
#include"Parser.h"
#include<map>

static size_t eq_n=0,lt_n=0,gt_n=0;
using namespace std;
class CodeWriter{

public:
	CodeWriter();
	
	void setFileName(const string&);
	
	void writeArithmetic(const string&);
	void writePushPop(Parser::typeC,const string&, int);

	void Close();
private:
	enum mathType{not_MATH,ADD,SUB,NEG,OR,AND,NOT,EQ,LT,GT};
	enum memoType{not_MEMO,M_CONSTANT, M_ARGUMENT,M_LOCAL,M_TEMP,M_THIS, M_THAT, M_STATIC,M_POINTER};
	
	std::string fileNaStr;
	std::ofstream outPutF;
	map<string,mathType> mathMap;
	map<string,memoType> memoMap;
};


#endif
