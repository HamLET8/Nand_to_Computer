#include<cctype>
#include<sstream>
#include<string>
#include"CodeWriter.h"

CodeWriter::CodeWriter()
:fileNaStr("aout.asm")
{
	
	mathMap["add"] = CodeWriter::ADD;
	mathMap["sub"] = CodeWriter::SUB;
	mathMap["neg"] = CodeWriter::NEG;
	mathMap["not"] = CodeWriter::NOT;
	mathMap["and"] = CodeWriter::AND;
	mathMap["or"]  =  CodeWriter::OR;
	mathMap["eq"]  = CodeWriter::EQ;
	mathMap["gt"]  = CodeWriter::GT;
	mathMap["lt"]  = CodeWriter::LT;
	
	memoMap["constant"] = CodeWriter::M_CONSTANT;
	memoMap["argument"] = CodeWriter::M_ARGUMENT;
	memoMap["local"]    = CodeWriter::M_LOCAL;
	memoMap["temp"] 	= CodeWriter::M_TEMP;
	memoMap["this"]		= CodeWriter::M_THIS;
	memoMap["that"] 	= CodeWriter::M_THAT;
	memoMap["pointer"] 	= CodeWriter::M_POINTER;	
	memoMap["static"] 	= CodeWriter::M_STATIC;
	
}

void CodeWriter::setFileName(const string& nameF)
{
	ofstream t(nameF);
	outPutF.open(nameF);
	fileNaStr = nameF;	
}	
void CodeWriter::writeArithmetic(const string& command) 
{
	CodeWriter::mathType comType = mathMap[command];
	outPutF << "//" << command <<endl;
	switch(comType)
	{
		case ADD:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nM=M+D" << endl;
			break;
		case SUB:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D" << endl;
			break;
		case AND:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D" << endl;
			break;
		case OR:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D" << endl;
			break;
		case NEG:
			outPutF << "@SP\nA=M-1\nM=-M" << endl;
			break;
		case NOT:
			outPutF << "@SP\nA=M-1\nM=!M" << endl;
			break;
		case EQ:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nD=D-M\n@EQUAL_" << eq_n++ 
			<<"\nD;JEQ\n@SP\nA=M-1\nM=0\n@BREAK_"<< eq_n << "\n0;JMP\n(EQUAL_" << eq_n
			<<")\n@SP\nA=M-1\nM=-1\n(BREAK_" << eq_n << ")" << endl;
			break;
		case GT:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@GREAT_" << gt_n++ 
			<<"\nD;JGT\n@SP\nA=M-1\nM=0\n@GTBREAK_"<< gt_n << "\n0;JMP\n(GREAT_" << gt_n
			<<")\n@SP\nA=M-1\nM=-1\n(GTBREAK_" << gt_n << ")" << endl;
			break;
		case LT:
			outPutF << "@SP\nAM=M-1\nD=M\nA=A-1\nD=M-D\n@LESST_" << lt_n++ 
			<<"\nD;JLT\n@SP\nA=M-1\nM=0\n@LTBREAK_"<< lt_n << "\n0;JMP\n(LESST_" << lt_n
			<<")\n@SP\nA=M-1\nM=-1\n(LTBREAK_" << lt_n << ")" << endl;
			break;
		
		default:
			break;	
			
	}
}
void CodeWriter::writePushPop(Parser::typeC type_P,const string& segment, int index)
{
	memoType seg = memoMap[segment];
	
	string popPush = (type_P == Parser::C_POP)? "pop" :"push";
	outPutF <<"//" << popPush << " " << segment << " "<< index <<endl;	//current command
	
	if(type_P == Parser::C_POP){
		switch(seg){
			
			case M_ARGUMENT:
				outPutF << "@" << index << "\nD=A\n@ARG\nD=D+M\n@R13\nM=D\n@SP\nAM= M-1\nD=M\n@R13\nA=M\nM=D" <<endl;
				break;
			case M_LOCAL:
				outPutF << "@" << index << "\nD=A\n@LCL\nD=D+M\n@R13\nM=D\n@SP\nAM= M-1\nD=M\n@R13\nA=M\nM=D" <<endl;
				break;
			case M_TEMP:
				outPutF << "@" << index << "\nD=A\n@5\nD=D+A\n@R13\nM=D\n@SP\nAM= M-1\nD=M\n@R13\nA=M\nM=D" <<endl;
				break;
			case M_THIS:
				outPutF << "@" << index << "\nD=A\n@THIS\nD=D+M\n@R13\nM=D\n@SP\nAM= M-1\nD=M\n@R13\nA=M\nM=D" <<endl;
				break;
			case M_THAT:
				outPutF << "@" << index << "\nD=A\n@THAT\nD=D+M\n@R13\nM=D\n@SP\nAM= M-1\nD=M\n@R13\nA=M\nM=D" <<endl;
				break;
			case M_POINTER:
				outPutF << "@" << index << "\nD=A\n@3\nD=D+A\n@R14\nM=D\n@SP\nAM=M-1\nD=M\n@R14\nA=M\nM=D" <<endl;
				break;
			case M_STATIC:
				outPutF << "@SP\nAM=M-1\nD=M\n@" << fileNaStr << "." << index << "\nM=D" << endl;
				break;
		}
	}else{ //type_P == Parser::C_PUSH
		switch(seg){
			case M_CONSTANT:
				outPutF << "@" << index <<"\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1" <<endl;
				break;
			case M_ARGUMENT:
				outPutF << "@" << index <<"\nD=A\n@ARG\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
			case M_LOCAL:
				outPutF << "@" << index <<"\nD=A\n@LCL\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
			case M_TEMP:
				outPutF << "@" << index <<"\nD=A\n@5\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
			case M_THIS:
				outPutF << "@" << index <<"\nD=A\n@THIS\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
			case M_THAT:
				outPutF << "@" << index <<"\nD=A\n@THAT\nA=D+M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
			case M_POINTER:
				outPutF << "@" << index <<"\nD=A\n@3\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1" << endl;
				break;
		
			case M_STATIC:
				outPutF << "@" << fileNaStr << "." <<index <<"\nD=M\n@SP\nA=M\n\nM=D\n@SP\nM=M+1" << endl;
				break;
		}
	}
		
}


