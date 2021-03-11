#include<cctype>
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>

#include"Parser.h"

Parser::Parser(const string& pathF) 
: crrCom(0)
{

	ifstream is(pathF);
	
	if(is)
		cout << "load file succeed !" <<endl; //test
	else
		cout << pathF << "  load file failed !" <<endl; //test
	
	file.push_back("NULL");
	
	string line;
	
	while(getline(is,line)) {
		
		char firstC = line[0];

		if(firstC!='/'&&line.size())	
		{
		//	istringstream word(line);
			//if(word>>line)
			line = string(line,0,line.find("/")-1); //omit comments
			file.push_back(line);
				
			cout << "command :\t" << line << endl; //test	
						
		}	
	}
	
	typeMap["add"] = Parser::C_ARITHMETIC;
	typeMap["sub"] = Parser::C_ARITHMETIC;
	typeMap["neg"] = Parser::C_ARITHMETIC;
	typeMap["eq"] = Parser::C_ARITHMETIC;
	typeMap["gt"] = Parser::C_ARITHMETIC;
	typeMap["lt"] = Parser::C_ARITHMETIC;
	typeMap["and"] = Parser::C_ARITHMETIC;
	typeMap["or"] = Parser::C_ARITHMETIC;
	typeMap["not"] = Parser::C_ARITHMETIC;
	
	typeMap["pop"] = Parser::C_POP;
	typeMap["push"] = Parser::C_PUSH;
		
}

Parser::typeC Parser::commandType()
{
	string type;
	istringstream iss(file[crrCom]);
	iss >> type;
	
	return typeMap[type];		
}

bool Parser::hasMoreCommands(){
	if(crrCom < file.size()-1)
		return true;
	else
		return false;
}

void Parser::advance()
{
	if(hasMoreCommands())
		++crrCom;
	else
		cout<< "the last one command" <<endl;
}

string Parser::Arg1() const{
	string type,arg1;
	istringstream iss(file[crrCom]);
	
		
	if(commandType()==Parser::C_ARITHMETIC)
	{	
		iss >> arg1;	
	
	}else
	{ 
		iss >> type >> arg1;
	}
	
	return arg1;	
}

int Parser::Arg2() const{
	string type,arg1,arg2;
	istringstream iss(file[crrCom]);
	iss >> type >> arg1 >> arg2;
		
	return atoi(arg2.c_str());		
}
	
