#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <fstream>

using namespace std;
#include "VMWriter.h"


VMWriter::VMWriter(const string& outputF)
{
	outVMFile.open(outputF);
	
	if(outVMFile) 			
		cout << "open output file successfully" << endl;
	else
	{
			cout << "open output failed" << endl;
	}
	
	segmentMap["VAR"]  = "local";
	segmentMap["CONST"]  = "constant";
	segmentMap["STATIC"]  = "static";
	segmentMap["FIELD"]  = "this";
	segmentMap["THAT"]  = "that";
	segmentMap["POINTER"]  = "pointer";
	segmentMap["TEMP"]  = "temp";
	segmentMap["ARG"]  = "argument";
	
		commandMap["+"] = "add";
		commandMap["-"] = "sub";
		commandMap["n"] = "neg";
		
		commandMap["&"] = "and";
		commandMap["|"]	= "or";
		commandMap["<"] = "lt";
		commandMap[">"] = "gt";
		commandMap["="] = "eq";
		commandMap["~"] = "not";
			
}



void VMWriter::close()
{
	outVMFile.close();
}

void VMWriter::writePush(const string segName, int index )
{
	outVMFile << "push " << segmentMap[segName] << " "<< index << endl;
}


void VMWriter::writePop(const string segName, int index)
{
	outVMFile << "pop " << segmentMap[segName] << " "<< index << endl;	
}

void VMWriter::writeArithmetic(const string com)
{		
	if(com == "*")
		writeCall("Math.multiply", 2);
	else if(com == "/")
		writeCall("Math.divide", 2);	
	else
		outVMFile << commandMap[com] << endl;
}

void VMWriter::writeLabel(const string& labelName)
{
	outVMFile << "label " << labelName << endl;	
}

void VMWriter::writeGoto(const string& labelName)
{
	outVMFile << "goto " << labelName << endl;	
}

void VMWriter::writeIf(const string& labelName)
{
	outVMFile << "if-goto " << labelName << endl;
}

void VMWriter::writeCall(const string  funcName , int nArgs)
{
	outVMFile << "call " << funcName << " " << nArgs << endl;
}

void VMWriter::writeFunction(const string funcName , int nLocals)
{
	outVMFile << "function " << funcName << " " << nLocals << endl;
}

void VMWriter::writeReturn()
{

	outVMFile << "return" << endl;	
}
