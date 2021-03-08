#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_

#include<map>

class SymbolTable{

public:
	SymbolTable()
	{
		sym_table["R0"] = 0;
		sym_table["R1"] = 1;
		sym_table["R2"] = 2;
		sym_table["R3"] = 3;
		sym_table["R4"] = 4;
		sym_table["R5"] = 5;
		sym_table["R6"] = 6;
		sym_table["R7"] = 7;
		sym_table["R8"] = 8;
		sym_table["R9"] = 9;
		sym_table["R10"] = 10;
		sym_table["R11"] = 11;
		sym_table["R12"] = 12;
		sym_table["R13"] = 13;
		sym_table["R14"] = 14;
		sym_table["R15"] = 15;
		
		sym_table["KBD"] = 24576;
		sym_table["SCREEN"] = 16384;
		sym_table["SP"] = 0;
		sym_table["LCL"] = 1;
		sym_table["ARG"] = 2;
		sym_table["THIS"] = 3;
		sym_table["THAT"] = 4;

	}
	
	void addEntry(const string& key, int line_no) { sym_table[key]=line_no; }

	bool contains(const string& key) const {		
		if(sym_table.find(key) == sym_table.end())
			return false;
		return true;
	}
	
	int GetAddress(const string& key) const
	{
		if(contains(key))
			return sym_table[key];
		return -1;
	}
	
private:
	map<string,size_t> sym_table;	
	
};




#endif
