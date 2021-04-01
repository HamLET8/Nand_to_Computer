#ifndef _VMWRITER_
#define _VMWRITER_

class VMWriter
{
public:
//	enum segment{
//		CONST,ARG,LOCAL,STATIC,THIS,THAT,POINTER,TEMP)
//	};
	
	VMWriter(const string& outFileName);
	void writePush(string , int );
	void writePop(const string , int);
	void writeArithmetic(const string);
	void writeLabel(const string&);
	void writeGoto(const string&);
	void writeIf(const string&);
	void writeCall(const string,int );
	void writeFunction(const string,int);
	void writeReturn();
	void close();
	bool voidFunc = 0;
private:
	ofstream outVMFile;	
	map<string,string> segmentMap;
	map<string,string> commandMap;
};





#endif
