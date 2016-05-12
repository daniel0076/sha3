#include <iostream>
#include <string>
#include <string.h>
#include "Sponge.h"
#include "InternalFun.h"

using namespace std;

#define BITRATE 576
#define CAPACITY 1024

string pad="100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";


void SpongeConstruction(string inputString, int outputLen)
{
	// Transform the input string into binary bits
	BinaryTransfer( inputString ) ;

	// Padding using Multirate
	vector< Binary > Message = Padding( inputString ) ;

	//Initialize the state variable
	Binary stateVar ;


	// Absorbing phase
	/*** TODO: Implement your SHA3's absorbing phase here ***/
	for(auto & block: Message){
		block<<=CAPACITY;
		//XOR with statevar
		stateVar^=block;
		stateVar=internalFun(stateVar);
	}


	// Squeezing phase
	string hashVal ; // The final output value
	/*** TODO: Implement your SHA3's squeezing phase here ***/


	// Print the hash value to the stdout
	PrintHex( hashVal.substr(0, outputLen) ) ;
}


void BinaryTransfer(string& inputString)
{
	string binary = "" ;

	for(int i=0; i<inputString.length(); i++)
	{
		for(int k=7; k>=0; k--)
			if( ((inputString[i] >> k) & 0x01) )
				binary += "1" ;
			else
				binary += "0" ;
	}

	inputString = binary ;
}



vector< Binary > Padding(string inputString)
{
	/*** TODO: Implement with Multirate padding ***/
	vector< Binary > output;
	unsigned int len=inputString.length();
	if(len % BITRATE == 0){
		inputString.append(pad);
	}else{
		inputString.push_back('1');
		while(inputString.length() % BITRATE != 0){
			inputString.push_back('0');
		}
		inputString.back()='1';
	}
	for(unsigned int i=0; i<inputString.length()/BITRATE; i++){
		Binary tmp( inputString.substr(BITRATE * i, BITRATE) );
		output.push_back(tmp);
	}
	return output;
}


/*** Print the hash value in hex ***/
void PrintHex(string hashVal)
{

	for(int i=0; i<hashVal.length(); i+=4)
	{
		string Ahex = hashVal.substr(i, 4) ;
		int Val = 0 ;

		for(int k=0; k<4; k++)
			if( Ahex[k]-'0' )
				Val += (1 << (3-k)) ;

		if( Val < 10 )	cout << Val ;
		else	cout << (char)(Val+55) ;
	}
}
