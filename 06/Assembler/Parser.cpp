#include<cctype>
#include<sstream>
#include"Parser.h"

/* How to process the white space and comment

by default , the assembly instruction begin with / or real word ,
the instruction is blank when first char is white space

*/	

Parser::Parser(ifstream &is) : crrCom(0) 
{
	file.push_back("Zero line");
	
	string line;
	
	while(getline(is,line)) {
		
		char firstC = line[0];

		if(firstC!='/')	
		{
			istringstream word(line);
			if(word>>line)
			{
				line = string(line,0,line.find("/")); //omit comments
				file.push_back(line);
			}
				
		}
	
		
	}
	
//	for(string &c: file)
		cout << crrCom <<endl;	
}

Parser::type_command Parser::commandType()
{
	string crr_command = file[crrCom];
	char firstC = crr_command[0];
	
	if(firstC == '@')
	{
		return A_COMMAND;
	}		
	else if(firstC == '(')
	{
		return L_COMMAND;	
	}
	else
		return C_COMMAND;
		
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

void Parser::reStart(){
	crrCom = 0;
}

string Parser::symbol()								// return the value of val in  @val
{
	string crrCommand = file[crrCom];
	
	if(commandType() == Parser::A_COMMAND)			//A_command @val
	{
		return string(crrCommand,1);
	}
	else if(commandType() == Parser::L_COMMAND)		//L_command (val)
	{	
		return string(crrCommand,1,crrCommand.find(")")-1);
		
	}else
		cout << "Not an A or L commmand"	<<endl;
}

string Parser::dest()
{
	if( commandType() == Parser::C_COMMAND)
	{
		size_t eqPos = file[crrCom].find("=");
		if (eqPos!= string::npos)				// if '=' exist ,dest is not null
		{
		 	return string(file[crrCom],0,eqPos);
		}else
			return string("null");
		
	
			
	}
	else
		cout << "error! current command is an A type" << endl;
}

string Parser::comp()
{
	if( commandType() == Parser::C_COMMAND)
	{
		size_t eqPos = file[crrCom].find("=");		//position of '='
		
		if (eqPos== string::npos) eqPos =0;			//M;jmp
		else ++eqPos;								//the begining of comp part 
		
		size_t cmPos = file[crrCom].find(";");		//the pos of comma
		
		if(cmPos != string::npos)				//   the pos of ';'
		{
			return string(file[crrCom],eqPos,(cmPos-eqPos));	//string(s,pos,len)	
		}
		else									//D=M
			return string(file[crrCom],eqPos);			//string(s,pos)
	}
	else
		cout << "error! current command is an A type" << endl;
}

string Parser::jump()
{
	size_t cmPos = file[crrCom].find(";");
	
	if(cmPos != string::npos)
	{
		return string(file[crrCom],cmPos+1);
	}
	else
		return string("null");
}
