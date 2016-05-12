#include <iostream>
#include <string>
#include <vector>
#include "InternalFun.h"

#define ROTL(qword, n) ((qword) << (n) ^ ((qword) >> (64 - (n))))
#define ROTR(qword, n) ((qword) >> (n) ^ ((qword) << (64 - (n))))

using namespace std;



bitset<64> RC[24] =
{
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};






Binary internalFun(Binary stateVar)
{

	for(int i=0; i<1; i++)
		stateVar = roundFun( stateVar, RC[i] ) ;

	return stateVar ;
}




/*** Round function in SHA-3 ***/
Binary roundFun(Binary stateVar, bitset<64> singleRC)
{

	/*** TODO: Implement your SHA3's 5 functions as follows ***/
	//break down the stateVar into lanes
	bitset<64> L[25];
	string stateVarStr = stateVar.to_string();
	for(int y=0;y<5;y++){
		for(int x=0;x<5;x++){
			bitset<64> tmp( stateVarStr.substr((x+5*y)<<6,64) );
			L[24-(x+5*y)] = tmp;
		}
	}

	/*** Theta ***/
	bitset<64> C[5];
	bitset<64> D[5];
	for(int x=0;x<5;x++){
		C[x]=L[x] ^ L[x+5] ^ L[x+10] ^ L[x+15] ^ L[x+20];
	}

	for(int i=0;i<5;i++){
		D[i]=C[ (i-1)%5 ] ^ ROTL( C[(i+1) % 5], 1);
	}

	for(int x=0;x<5;x++){
		/*
		for(int z=0;z<64;z++){
			stateVar[((x)<<6)+z] =stateVar[((x)<<6)+z] ^ D[x][z];
			stateVar[((x+5)<<6)+z] =stateVar[((x+5)<<6)+z] ^ D[x][z];
			stateVar[((x+10)<<6)+z] =stateVar[((x+10)<<6)+z] ^ D[x][z];
			stateVar[((x+15)<<6)+z] =stateVar[((x+15)<<6)+z] ^ D[x][z];
			stateVar[((x+20)<<6)+z] =stateVar[((x+20)<<6)+z] ^ D[x][z];
		}
		*/
		L[x] 	= L[x] 		^ D[x];
		L[x+5] 	= L[x+5] 	^ D[x+5];
		L[x+10] = L[x+10] 	^ D[x+10];
		L[x+15] = L[x+15] 	^ D[x+15];
		L[x+20] = L[x+20] 	^ D[x+20];
	}

	for(int i=0;i<25;i++){
		cout<<L[24-i];
	}

	/*** Rho  ***/


	/*** Pi ***/


	/*** Xi ***/


	/*** Iota ***/

}
