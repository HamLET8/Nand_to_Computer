#include <iostream>
#include <map>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
#include "JackTokenizer.h"
#include "CompilationEngine.h"
#include "SymbolTable.h"


void listFiles(const char *,vector<string> &);
string getFileName(string);
int main(int argc, char** argv) {	
	
	vector<string> vmFile;  			//vector for jack file 	
	
	listFiles(argv[1],vmFile);		//get the path and load files into vector
//	vmFile.push_back("C:\\Users\\q1428\\Desktop\\nand2tetris\\projects\\11\\ConvertToBin\\Main.jack");
	for(auto fileName : vmFile){
		
		cout <<"current file  " << fileName << endl; //test

		string outFileName = getFileName(fileName);
		CompilationEngine(fileName,outFileName);
		
//		cout <<"output  file  NO1 "  << endl; //test
	}
//		outToken.open(outFileName);

/*	
	outToken << "<tokens>" << endl;
		
	while(tokenizer.hasMoreTokens()){
	
		switch(tokenizer.tokenType()){
			
			case TokenMap::KEYWORD:
				outToken << "<keyword> " << tokenizer.keywordVal() << " </keyword>" << endl;  ///
				break;
			case TokenMap::SYMBOL:
				outToken << "<symbol> " << tokenizer.symbol() << " </symbol>" << endl;
				break;
			case TokenMap::IDENTIFIER:
				outToken << "<identifier> " << tokenizer.identifier() << " </identifier>" << endl;
				break;
			case TokenMap::INT_CONST:
				outToken << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << endl;
				break;
			case TokenMap::STRING_CONST:
				outToken << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << endl;
				break;
			default:
				cout << "error ! " << endl;
				break;
		}
		
		 tokenizer.advance();
	}	
	outToken << "</tokens>" << endl;
	outToken.close();
	}
*/	

	return 0;
}

string getFileName(string pathName){
	
//    	string fileName = string(pathName,pathName.find_last_of('\\')+1);	//*.jack
		
    	pathName.erase(pathName.find("."));	
    	pathName.append(".vm");	
	
	return pathName;
}

void listFiles(const char *dir,vector<string> &Vfile)
{
    using namespace std;
    
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    char dirNew[100];
    
    if(strchr(dir,'.')){			// if current dir is a file name ,return 
    	Vfile.push_back(dir);
		return ;
	}
	
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.jack");
    
    hFind = FindFirstFile(dirNew, &findData);    //search handle
    do
    {
    	string filePath = dir;
    	filePath.append("\\");
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0
        && strcmp(findData.cFileName, ".") != 0
        && strcmp(findData.cFileName, "..") != 0
        )
        {
            
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
}
