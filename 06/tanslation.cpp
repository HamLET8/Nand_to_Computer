#include<iostream>
#include<iterator>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

string TransDetoBin(const string &DecS)
{
	size_t decimal = 0;
	string rbinS("");
	
	int i = 0;
	for(string::const_reverse_iterator r_iter = DecS.rbegin(); r_iter != DecS.rend(); ++r_iter , ++i)
	{
		decimal = decimal + ((*r_iter-'0') * pow(10,i) ) ;
		cout << "dec = " << decimal <<endl;;
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


int main(int argc ,char	*argv[])
{
	ifstream infile(argv[1]);
	
	if(argc == 1){						// the name of output file
		ofstream outfile("aout.hack");
	}else{
		string s(argv[1]);
		string sf(s,0,s.find("."));
		
		ofstream outfile(sf+".hack");
	}
	

}
