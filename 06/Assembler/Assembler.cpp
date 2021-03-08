#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<fstream>
#include"Parser.h"
#include"Code.h"
#include"SymbolTable.h"

using namespace std;
string TransDetoBin(const string &);
void first_Pass(Parser &, SymbolTable &);

int main(int argc ,char	*argv[])
{
//	ifstream infile(".\\ADD\\Add.asm"); //test
//	ofstream outfile("a.hack");//test

	ifstream infile(argv[1]);
	
	string s(argv[1]);			// the format of the name of the output file 
	string sf(s,0,s.find("."));
		
	ofstream outfile(sf+".hack");

		
	
	Parser instructions(infile);			// input file
	SymbolTable symTab;						//symbol table
	Code iCode;								//map for mapping part of instruction to binary
	
/************ first Pass***************/

	first_Pass(instructions,symTab);


/************ End of first Pass********/
	
	int addressV = 16;					//the address location of variables 
							
	string symVal("");							//temp for symbol of A command
	
	while(instructions.hasMoreCommands())
	{
		instructions.advance();
		string commandBin("");				//binary command
		switch(instructions.commandType())
		{
			case Parser::A_COMMAND:
				commandBin.append("0");
				symVal = instructions.symbol();
				
				
				if(!isdigit(symVal[0])){
					if(symTab.contains(symVal))				//Lable or Variable that loaded in 
					{
					cout<<  "command = " << symVal <<endl;//test
					symVal = to_string(symTab.GetAddress(symVal));	
					cout << "symVal = "<< symVal <<endl; //test
					}
					else{									//Variable that first meet
						symTab.addEntry(symVal,addressV);
						symVal = to_string(addressV++);
				
					}
				}
				symVal = TransDetoBin(symVal);
			
				commandBin.append(symVal);
				break;
				
			case Parser::L_COMMAND:
				continue;
				
			case Parser::C_COMMAND:
				commandBin.append("111");
				commandBin.append(iCode.comp(instructions.comp()));							
				
				commandBin.append(iCode.dest(instructions.dest()));
			
				commandBin.append(iCode.jump(instructions.jump()));
				
				cout<<  "command = " << instructions.dest() << " = "<< instructions.comp() << ";"<<instructions.jump() <<endl;//t
				
				break;
		}
		
		outfile << commandBin << endl;
	}	
	return 0;
}


/* First Pass
*
	declear crrPC to track the address of current instruction . 
when meet the L_command ,the load < symbol, ++address> into SymbolTable.

	
*
	Second Pass
*
 	L_command . Skip 
	A_command :	translate inderectly,check the Symbol table , 
						if the symbol already exist ,then translate it by replace the value correspondent to its value
						else replace it with new memory address which allocate begin with 16 
				
	C_command:  translate derectly
*/

void first_Pass(Parser &is, SymbolTable &symT)
{
	size_t crrPC = 0;
	
	while(is.hasMoreCommands())
	{	
		is.advance();
		if(is.commandType()==Parser::L_COMMAND)
		{
			cout << "is.symbol() = "<< is.symbol() <<endl; //test	
			symT.addEntry(is.symbol(),crrPC);
			cout << "PC = "<< crrPC <<endl; //test		
		}
		else
		{
			++crrPC;
			
		}	
		
	}
	is.reStart();
}

string TransDetoBin(const string &DecS)
{
	size_t decimal = 0;
	string rbinS("");
	
	int i = 0;
	for(string::const_reverse_iterator r_iter = DecS.rbegin(); r_iter != DecS.rend(); ++r_iter , ++i)
	{
		decimal = decimal + ((*r_iter-'0') * pow(10,i) ) ;
	}
	
	while(decimal!=0)
	{
		if(decimal%2)
			rbinS.append("1");
		else
			rbinS.append("0");
		decimal /= 2;
	}
	
	while(rbinS.size()<15)
	{
		rbinS.append("0");
	}
	
	return string(rbinS.rbegin(),rbinS.rend());
}
