#ifndef _CODEWRITER_
#define	_CODEWRITER_
#include<fstream>
#include"Parser.h"
#include<map>
using namespace std;

static size_t eq_n=0,lt_n=0,gt_n=0,ret_n=0;

class CodeWriter{

public:
	CodeWriter(const string &);
	
	void setFileName(const string&);
	
	void writeInit();
	void writeReturn();
	
	void writeIf(const string&);	
	void writeGoto(const string&);		
	void writeLabel(const string&);
	
	void writeCall(const string&,int );	
	void writeArithmetic(const string&);
	void writeFunction(const string& ,int);	
	void writePushPop(Parser::typeC,const string&, int);

	void Close();
private:
	enum mathType{ADD,SUB,NEG,OR,AND,NOT,EQ,LT,GT};
	enum memoType{M_CONSTANT, M_ARGUMENT,M_LOCAL,M_TEMP,M_THIS, M_THAT, M_STATIC,M_POINTER};
	
	std::string crrFileName;
	std::ofstream outPutF;
	map<string,mathType> mathMap;
	map<string,memoType> memoMap;
};


#endif
