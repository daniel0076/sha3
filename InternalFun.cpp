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

	for(int i=0; i<24; i++)
		stateVar = roundFun( stateVar, RC[i] ) ;

	return stateVar ;
}


/*** Round function in SHA-3 ***/
Binary roundFun(Binary stateVar, bitset<64> singleRC)
{

	/*** TODO: Implement your SHA3's 5 functions as follows ***/
	//break down the stateVar into lanes 5x5x64
	bitset<64> L[25];
	string stateVarStr = stateVar.to_string();
	for(int y=0;y<5;y++){
		for(int x=0;x<5;x++){
			bitset<64> tmp( stateVarStr.substr((x+5*y)<<6,64) );
			L[x+5*y] = tmp;
		}
	}


	/*** Theta ***/
	bitset<64> C[5];
	bitset<64> D[5];
	for(int x=0;x<5;x++){
		C[x]=L[x] ^ L[x+5] ^ L[x+10] ^ L[x+15] ^ L[x+20];
	}

	D[0]=C[4] ^ ROTR( C[1], 1);
	D[1]=C[0] ^ ROTR( C[2], 1);
	D[2]=C[1] ^ ROTR( C[3], 1);
	D[3]=C[2] ^ ROTR( C[4], 1);
	D[4]=C[3] ^ ROTR( C[0], 1);


	for(int x=0;x<5;x++){
		L[x] ^=D[x];
		L[x+5] ^=D[x];
		L[x+10] ^=D[x];
		L[x+15] ^=D[x];
		L[x+20] ^=D[x];
	}

	/*** Rho  ***/
	int rot_pos[25]={0,1,62,28,27,36,44,6,55,20,3,10,43,25,39,41,45,15,21,8,18,2,61,56,14};
	for(int i=0;i<25;i++){
		L[i] = ROTR(L[i],rot_pos[i]);
	}

	/*** Pi ***/

	//0 not change
	int pi_order[24]={16,8,21,24,4,15,23,19,13,12,2,20,14,22,9,6,1,10,7,11,17,18,3,5};
	bitset<64> L5=L[5];
	for(int i=23;i>0;i--){
		L[ pi_order[i] ]=L[ pi_order[i-1] ];
	}
	L[16]=L5;

  /*** Xi ***/
	for(int y=0;y<5;y++){
		bitset<64>tmpL[2];
		tmpL[0]=L[0+5*y];
		tmpL[1]=L[1+5*y];
		L[0+5*y] ^= ( ~L[1+5*y] & L[2+5*y] );
		L[1+5*y] ^= ( ~L[2+5*y] & L[3+5*y] );
		L[2+5*y] ^= ( ~L[3+5*y] & L[4+5*y] );
		L[3+5*y] ^= ( ~L[4+5*y] & tmpL[0] );
		L[4+5*y] ^= ( ~tmpL[0] & tmpL[1] );
	}

	/*** Iota ***/
	L[0]^=singleRC;

	string metaString;
	for(int i=0;i<25;i++){
		metaString+=L[i].to_string();
	}
	return Binary(metaString);
}
