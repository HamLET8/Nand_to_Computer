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
			
			line = string(line,0,line.find("/")-1); //omit comments
			file.push_back(line);						
		}	
	}
	
	typeMap["add"] = Parser::C_ARITHMETIC;
	typeMap["sub"] = Parser::C_ARITHMETIC;
	typeMap["neg"] = Parser::C_ARITHMETIC;
	typeMap["eq"]  = Parser::C_ARITHMETIC;
	typeMap["gt"]  = Parser::C_ARITHMETIC;
	typeMap["lt"]  = Parser::C_ARITHMETIC;
	typeMap["and"] = Parser::C_ARITHMETIC;
	typeMap["or"]  = Parser::C_ARITHMETIC;
	typeMap["not"] = Parser::C_ARITHMETIC;
	
	
	typeMap["if-goto"]  = Parser::C_IF;
	typeMap["pop"]  	= Parser::C_POP;
	typeMap["push"] 	= Parser::C_PUSH;
	typeMap["call"]  	= Parser::C_CALL;	
	typeMap["goto"] 	= Parser::C_GOTO;
	typeMap["label"] 	= Parser::C_LABEL;
	typeMap["return"]  	= Parser::C_RETURN;
	typeMap["function"] = Parser::C_FUNCTION;	
}

Parser::typeC Parser::commandType()
{
	string type;
	istringstream iss(file[crrCom]);
	iss >> type;
	
	if(typeMap.find(type)==typeMap.end()) 
	{ return Parser::C_LABEL; }
	
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
	string type,arg1,arg2;
	istringstream iss(file[crrCom]);
	
	switch(commandType())
	{

	    		case Parser::C_ARITHMETIC:	//command itself
	    			iss >> arg1;
	    			break;
	    		case Parser::C_PUSH:		//segment name
	    			iss >> type >> arg1;
	    			break;
	    		case Parser::C_POP:			//segment name
	    			iss >> type >> arg1;
	    			break;
				case Parser::C_CALL:		//function name 
					iss >> type >> arg1;
					break;
				case Parser::C_FUNCTION:	//function name 
					iss >> type >> arg1 ;   
					break;					
				case Parser::C_GOTO:		//label
					iss >> type >> arg1;	
					break;
				case Parser::C_IF:			//label
					iss >> type >> arg1;
					break;
				case Parser::C_LABEL:		//label
					iss >> type >> arg1;			
					break;
	    		default:
	    			break;	
	}	
	
	return arg1;	
}

int Parser::Arg2() const{
	
	string type,arg1,arg2;
	istringstream iss(file[crrCom]);
	
	iss >> type >> arg1 >> arg2;		
	return atoi(arg2.c_str());		
}
	
