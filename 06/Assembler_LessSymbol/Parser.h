#ifndef _PARSER_
#define _PARSER_
#include<string>
#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
using namespace std;

class Parser{

public:
	Parser(ifstream &);
	enum type_command { A_COMMAND , C_COMMAND, L_COMMAND };
	
	bool hasMoreCommands();			
	void advance();					//read next command
	type_command commandType();		//return the type of crr command
	std::string symbol();				//return the real value of a symbol(lable or variable)
	
	string dest();					//return the dest part of C instructiom
	string comp();					//return the comp part of C instruction
	string jump();					//return the jump part of C instruction
private:
	vector<string> file;		//the line number begin from 1
	size_t crrCom;
	
	

};


#endif 
