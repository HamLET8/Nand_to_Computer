#include <iostream>
#include <cstring>
#include <windows.h>
#include <vector>
#include<cctype>
#include<sstream>
#include<string>
#include<fstream>
#include<map>
using namespace std;
string currentFileName();			//current file name
#include"CodeWriter.h"


string listFiles(const char *,vector<string> &);		//access the folders to find files

int main(int argc  , char *argv[])
{   
    vector<string> vmFile;  
	string Tpath = listFiles(argv[1],vmFile);
			
	string fileName;
   
    if(vmFile.size()==1)									// only one .vm file ,named by file name
    {
    	fileName = string(vmFile[0],vmFile[0].find_last_of('\\')+1);	//*.vm
    	fileName.erase(fileName.find("."));	
    	Tpath.append("\\" + fileName);	
	}else													// more than one , named by directory
	{
    	fileName = string(Tpath,Tpath.find_last_of('\\')+1);	//get name of directory
    	Tpath.append("\\" + fileName);
	}
	
	
	
	CodeWriter Coder(Tpath);
	Coder.writeInit();
    
    
    string currentFileName;
    for(const string c: vmFile)
    {
    	
    	Parser vmInstructions(c);
    	
    	currentFileName = string(c,c.find_last_of('\\')+1);
    	currentFileName.erase(currentFileName.find("."));
    	
    	Coder.setFileName(currentFileName);  				//static variable need the name of current file
		 	
    	while(vmInstructions.hasMoreCommands()){
    		
			vmInstructions.advance();
    		
			switch(vmInstructions.commandType())
	    	{
	    	
	    		case Parser::C_NULL:
	    			cout << "never happen" << endl;
	    			break;
	    			
	    		case Parser::C_ARITHMETIC:
	    			Coder.writeArithmetic(vmInstructions.Arg1());
	    			break;
	    			
	    		case Parser::C_PUSH:
	    		
	    			Coder.writePushPop(Parser::C_PUSH, vmInstructions.Arg1(), vmInstructions.Arg2());
	    			break;
	    			
	    		case Parser::C_POP:
	    			Coder.writePushPop(Parser::C_POP, vmInstructions.Arg1(), vmInstructions.Arg2());
	    			break;
	    			
				case Parser::C_CALL:
						Coder.writeCall(vmInstructions.Arg1(), vmInstructions.Arg2());
					break;
					
				case Parser::C_FUNCTION:
					Coder.writeFunction(vmInstructions.Arg1(), vmInstructions.Arg2());
					break;
					
				case Parser::C_GOTO:
					Coder.writeGoto(vmInstructions.Arg1());
					break;
					
				case Parser::C_IF:
					Coder.writeIf(vmInstructions.Arg1());
					break;
					
				case Parser::C_LABEL:
					Coder.writeLabel(vmInstructions.Arg1());
					break;
						
				case Parser::C_RETURN:
					Coder.writeReturn();
					break;
			
	    		default:
	    			break;
			}
		
		}
    	
	}
    
    
    return 0;
}




string listFiles(const char *dir,vector<string> &Vfile)
{
    using namespace std;
    
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    char dirNew[100];
    
    // ��Ŀ¼��ͨ���������������һ���ļ� 
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.vm");
    
    hFind = FindFirstFile(dirNew, &findData);    //search handle
    do
    {
    	string filePath = dir;
    	filePath.append("\\");
        // �Ƿ����ļ��У��������Ʋ�Ϊ"."��".." 
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0
        && strcmp(findData.cFileName, ".") != 0
        && strcmp(findData.cFileName, "..") != 0
        )
        {
            // ��dirNew����Ϊ��������Ŀ¼����������һ������ 
            strcpy(dirNew, dir);
            strcat(dirNew, "\\");
            strcat(dirNew, findData.cFileName);
            listFiles(dirNew,Vfile);
        }
        else
        {
			filePath.append(findData.cFileName);
            Vfile.push_back(filePath);
        }
    }while (FindNextFile(hFind, &findData));
    
    FindClose(hFind);
    return dir;
}
