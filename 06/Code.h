#ifndef _CODE_
#define _CODE_
/* this is the hash table that mapping C_command part to binary )*/  

#include<map>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<fstream>

using namespace std;

class Code{

public:
	Code()
	{
		// M : memory;		A : A register;		D : D register
        destMap["null"] = "000";
        destMap["M"] = "001";
        destMap["D"] = "010";
        destMap["MD"] = "011";
        destMap["A"] = "100";
        destMap["AM"] = "101";
        destMap["AD"] = "110";
        destMap["AMD"] = "111";

        compMap["0"] = "0101010";
        compMap["1"] = "0111111";
        compMap["-1"] = "0111010";
        compMap["D"] = "0001100";
        compMap["A"] = "0110000";
        compMap["!D"] = "0001101";
        compMap["!A"] = "0110001";
        compMap["-D"] = "0001111";
        compMap["-A"] = "0110001";


        compMap["D+1"] = "0011111";
        compMap["A+1"] = "0110111";
        compMap["D-1"] = "0001110";
        compMap["A-1"] = "0110010";
        compMap["D+A"] = "0000010";
        compMap["D-A"] = "0010011";
        compMap["A-D"] = "0000111";
        compMap["D&A"] = "0000000";
        compMap["D|A"] = "0010101";

        compMap["1+D"] = "0011111";
        compMap["1+S"] = "0110111";
        compMap["A+D"] = "0000010";
        compMap["A&D"] = "0000000";
        compMap["A|D"] = "0010101";


        compMap["M"] = "1110000";
        compMap["!M"] = "1110001";
        compMap["-M"] = "1110001";
        compMap["M+1"] = "1110111";
        compMap["M-1"] = "1110010";
        compMap["D+M"] = "1000010";
        compMap["D-M"] = "1010011";
        compMap["M-D"] = "1000111";
        compMap["D&M"] = "1000000";
        compMap["D|M"] = "1010101";

        compMap["1+M"] = "1110111";
        compMap["M+D"] = "1000010";
        compMap["M&D"] = "1000000";
        compMap["M|D"] = "1010101";

        jumpMap["null"] = "000";
        jumpMap["JGT"] = "001";
        jumpMap["JEQ"] = "010";
        jumpMap["JGE"] = "011";
        jumpMap["JLT"] = "100";
        jumpMap["JNE"] = "101";
        jumpMap["JLE"] = "110";
        jumpMap["JMP"] = "111";		
	}
	
	string dest(string opr)  {return destMap[opr];}
	string comp(string opr)  {return compMap[opr];}
	string jump(string opr)  {return jumpMap[opr];}
	

private:
	map<string, string> destMap;
	map<string, string> compMap;
	map<string, string> jumpMap;
};

#endif
