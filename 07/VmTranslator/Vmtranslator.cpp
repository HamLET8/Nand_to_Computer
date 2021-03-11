#include <iostream>
#include <cstring>
#include <windows.h>
#include <vector>
#include<cctype>
#include<sstream>
#include<string>
#include<fstream>
#include<map>

#include"CodeWriter.h"

void listFiles(const char *,vector<string> &);		//access the folders to find files

using namespace std;

int main(int argc  , char *argv[])
{   
    vector<string> vmFile;  
    listFiles(argv[1],vmFile);
	
    CodeWriter Coder;
    Coder.setFileName("aout.asm");
    
    for(const string c: vmFile)
    {
    	
    	Parser vmInstructions(c);
    	   	
    	while(vmInstructions.hasMoreCommands()){
    		
			vmInstructions.advance();
    		
			switch(vmInstructions.commandType())
	    	{
	    		case Parser::C_ARITHMETIC:
	    			Coder.writeArithmetic(vmInstructions.Arg1());
	    			break;
	    		case Parser::C_PUSH:
	    			Coder.writePushPop(Parser::C_PUSH, vmInstructions.Arg1(), vmInstructions.Arg2());
	    			break;
	    		case Parser::C_POP:
	    			Coder.writePushPop(Parser::C_POP, vmInstructions.Arg1(), vmInstructions.Arg2());
	    			break;		
	    		default:
	    			break;
			}
		
		}
    	
	}
    
    
    return 0;
}




void listFiles(const char * dir,vector<string> &Vfile)
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
        	string filePath = strcat(dir, "\\");
			filePath.append(findData.cFileName);
			
            Vfile.push_back(filePath);
        }
    }while (FindNextFile(hFind, &findData));
    
    FindClose(hFind);
}
