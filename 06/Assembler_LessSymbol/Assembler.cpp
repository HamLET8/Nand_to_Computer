#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<fstream>
#include"Parser.h"
#include"Code.h"
using namespace std;
string TransDetoBin(const string &);

int main(int argc ,char	*argv[])
{
	ifstream infile(argv[1]);
	
	string s(argv[1]);			// the format of the name of the output file 
	string sf(s,0,s.find("."));
		
	ofstream outfile(sf+".hack");
	
	
	Parser instructions(infile);
	Code iCode;
	
	
	string valueA;
	while(instructions.hasMoreCommands())
	{
		instructions.advance();
		string commandBin("");
		
		switch(instructions.commandType())
		{
			case Parser::A_COMMAND:
				commandBin.append("0");
				valueA = TransDetoBin(instructions.symbol());
				commandBin.append(valueA);
				break;
			
			case Parser::C_COMMAND:
				commandBin.append("111");
				commandBin.append(iCode.comp(instructions.comp()));
				
				cout<<  "comp = "<< instructions.comp() <<endl;//t
				
				commandBin.append(iCode.dest(instructions.dest()));
				
				cout<<  "dest = "<< instructions.dest() <<endl;//t
				
				commandBin.append(iCode.jump(instructions.jump()));
				
				cout<<  "jump = "<< instructions.jump() <<endl;//t
				
				break;
		}
		
		outfile << commandBin << endl;
	}	
	return 0;
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
