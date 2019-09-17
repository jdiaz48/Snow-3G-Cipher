#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <bitset>
#include <unordered_map>

using namespace std;

bitset<32> FSM(bitset<32> input1, bitset<32> input2, int (&Sr)[256], int (&Sq)[256]);
void LFSR(bitset<32> F,  vector<bitset<32> >& SStuff, int initialization);
bitset<8> mulX(bitset<8> V, bitset<8> c);
bitset<8> mulY(bitset<8> V, int i, bitset<8> c);
bitset<32> mulA(bitset<8> c);
bitset<32> DIV(bitset<8> c);
bitset<32> SR(bitset<32> w, int (&Sr)[256]);
bitset<32> SQ(bitset<32> w, int (&Sq)[256]);
string hexToBinary(string address);
string binaryToHex(string address);
bitset<32> R1(0);
bitset<32> R2(0);
bitset<32> R3(0);

int main(int argc, char* argv[]){
	bitset<32> IV0;
	bitset<32> IV1;
	bitset<32> IV2;
	bitset<32> IV3;

	bitset<32> k0;
	bitset<32> k1;
	bitset<32> k2;
	bitset<32> k3;

	int NUM;
	string temp2 = "0xffffffff";
	temp2 = hexToBinary(temp2);
	bitset<32> one(temp2);
	temp2 = "0x00000000";
	temp2 = hexToBinary(temp2);
	bitset<32> zero(temp2);

	vector<bitset<32> > SStuff;
	int Sr[256] =
 {0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76
 ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0
 ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
 ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
 ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
 ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
 ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
 ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
 ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
 ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
 ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
 ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
 ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
 ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
 ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
 ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16};

 int Sq[256] =
{0x25 ,0x24 ,0x73 ,0x67 ,0xd7 ,0xae ,0x5c ,0x30 ,0xa4 ,0xee ,0x6e ,0xcb ,0x7d ,0xb5 ,0x82 ,0xdb
,0xe4 ,0x8e ,0x48 ,0x49 ,0x4f ,0x5d ,0x6a ,0x78 ,0x70 ,0x88 ,0xe8 ,0x5f ,0x5e ,0x84 ,0x65 ,0xe2
,0xd8 ,0xe9 ,0xcc ,0xed ,0x40 ,0x2f ,0x11 ,0x28 ,0x57 ,0xd2 ,0xac ,0xe3 ,0x4a ,0x15 ,0x1b ,0xb9
,0xb2 ,0x80 ,0x85 ,0xa6 ,0x2e ,0x02 ,0x47 ,0x29 ,0x07 ,0x4b ,0x0e ,0xc1 ,0x51 ,0xaa ,0x89 ,0xd4
,0xca ,0x01 ,0x46 ,0xb3 ,0xef ,0xdd ,0x44 ,0x7b ,0xc2 ,0x7f ,0xbe ,0xc3 ,0x9f ,0x20 ,0x4c ,0x64
,0x83 ,0xa2 ,0x68 ,0x42 ,0x13 ,0xb4 ,0x41 ,0xcd ,0xba ,0xc6 ,0xbb ,0x6d ,0x4d ,0x71 ,0x21 ,0xf4
,0x8d ,0xb0 ,0xe5 ,0x93 ,0xfe ,0x8f ,0xe6 ,0xcf ,0x43 ,0x45 ,0x31 ,0x22 ,0x37 ,0x36 ,0x96 ,0xfa
,0xbc ,0x0f ,0x08 ,0x52 ,0x1d ,0x55 ,0x1a ,0xc5 ,0x4e ,0x23 ,0x69 ,0x7a ,0x92 ,0xff ,0x5b ,0x5a
,0xeb ,0x9a ,0x1c ,0xa9 ,0xd1 ,0x7e ,0x0d ,0xfc ,0x50 ,0x8a ,0xb6 ,0x62 ,0xf5 ,0x0a ,0xf8 ,0xdc
,0x03 ,0x3c ,0x0c ,0x39 ,0xf1 ,0xb8 ,0xf3 ,0x3d ,0xf2 ,0xd5 ,0x97 ,0x66 ,0x81 ,0x32 ,0xa0 ,0x00
,0x06 ,0xce ,0xf6 ,0xea ,0xb7 ,0x17 ,0xf7 ,0x8c ,0x79 ,0xd6 ,0xa7 ,0xbf ,0x8b ,0x3f ,0x1f ,0x53
,0x63 ,0x75 ,0x35 ,0x2c ,0x60 ,0xfd ,0x27 ,0xd3 ,0x94 ,0xa5 ,0x7c ,0xa1 ,0x05 ,0x58 ,0x2d ,0xbd
,0xd9 ,0xc7 ,0xaf ,0x6b ,0x54 ,0x0b ,0xe0 ,0x38 ,0x04 ,0xc8 ,0x9d ,0xe7 ,0x14 ,0xb1 ,0x87 ,0x9c
,0xdf ,0x6f ,0xf9 ,0xda ,0x2a ,0xc4 ,0x59 ,0x16 ,0x74 ,0x91 ,0xab ,0x26 ,0x61 ,0x76 ,0x34 ,0x2b
,0xad ,0x99 ,0xfb ,0x72 ,0xec ,0x33 ,0x12 ,0xde ,0x98 ,0x3b ,0xc0 ,0x9b ,0x3e ,0x18 ,0x10 ,0x3a
,0x56 ,0xe1 ,0x77 ,0xc9 ,0x1e ,0x9e ,0x95 ,0xa3 ,0x90 ,0x19 ,0xa8 ,0x6c ,0x09 ,0xd0 ,0xf0 ,0x86};

	string temp;
	ifstream file;
  file.open(argv[1]);

	if (file.is_open()){
		getline(file, temp, ' ' );
		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t0(temp);
		k0 = t0;

		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t1(temp);
		k1 = t1;

		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t2(temp);
		k2 = t2;

		getline(file, temp);
		temp = hexToBinary(temp);
		bitset<32> t3(temp);
		k3 = t3;

		getline(file, temp, ' ' );
		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t4(temp);
		IV0 = t4;

		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t5(temp);
		IV1 = t5;

		getline(file, temp, ' ');
		temp = hexToBinary(temp);
		bitset<32> t6(temp);
		IV2 = t6;

		getline(file, temp);
		temp = hexToBinary(temp);
		bitset<32> t7(temp);
		IV3 = t7;

		getline(file, temp, ' ');
		getline(file, temp);
		NUM = stoi(temp);

	}
	file.close();

	bitset<32> yo;
	yo = (k0 ^ one);
	SStuff.push_back(yo);

	yo = (k1 ^ one);
	SStuff.push_back(yo);

	yo = (k2 ^ one);
	SStuff.push_back(yo);

	yo = (k3 ^ one);
	SStuff.push_back(yo);

	SStuff.push_back(k0);
	SStuff.push_back(k1);
	SStuff.push_back(k2);
	SStuff.push_back(k3);

	yo = (k0 ^ one);
	SStuff.push_back(yo);

	yo = ((k1 ^ one) ^ IV3);
	SStuff.push_back(yo);

	yo = ((k2 ^ one) ^ IV2);
	SStuff.push_back(yo);

	yo = (k3 ^ one);
	SStuff.push_back(yo);

	yo = (k0 ^ IV1);
	SStuff.push_back(yo);

	SStuff.push_back(k1);
	SStuff.push_back(k2);

	yo = (k3 ^ IV0);
	SStuff.push_back(yo);


	for(int i = 0; i < 32; i++){
		LFSR(FSM(SStuff[15], SStuff[5], Sr, Sq), SStuff, 1);
	}

	//keystream?
	FSM(SStuff[15], SStuff[5], Sr, Sq);
	LFSR(zero, SStuff, 0);

	for(int i = 0; i < NUM; i++){
		bitset<32> F = FSM(SStuff[15], SStuff[5], Sr, Sq);
		bitset<32> output = F ^ SStuff[0];
		LFSR(zero, SStuff, 0);
		cout << binaryToHex(output.to_string()) << endl;
	}

}

bitset<32> FSM(bitset<32> input1, bitset<32> input2, int (&Sr)[256], int (&Sq)[256]){
	//cout << input1.to_string() << endl;
	bitset<32> F = (bitset<32>)((input1.to_ulong() + R1.to_ulong()) % 4294967296) ^ R2;
	bitset<32> r = (bitset<32>)((R2.to_ulong() + (R3 ^ input2).to_ulong()) % 4294967296);
	R3 = SQ(R2, Sq);
	R2 = SR(R1, Sr);
	R1 = r;
	return F;
}

void LFSR(bitset<32> F,  vector<bitset<32> >& SStuff, int initialization){
	bitset<32> divider(0b00000000000000000000000011111111);
	bitset<8> s33 = (divider & SStuff[0]).to_ulong();
	bitset<8> s22 = (divider & (SStuff[0] >> 8)).to_ulong();
	bitset<8> s11 = (divider & (SStuff[0] >> 16)).to_ulong();
	bitset<8> s00 = (divider & (SStuff[0] >> 24)).to_ulong();

	bitset<8> s113 = (divider & SStuff[11]).to_ulong();
	bitset<8> s112 = (divider & (SStuff[11] >> 8)).to_ulong();
	bitset<8> s111 = (divider & (SStuff[11] >> 16)).to_ulong();
	bitset<8> s110 = (divider & (SStuff[11] >> 24)).to_ulong();

	if(initialization == 1){
		bitset<32> v(s11.to_string() + s22.to_string() + s33.to_string() + "00000000");
		v = ((v ^ mulA(s00)) ^ SStuff[2]);
		bitset<32> temp("00000000" + s110.to_string() + s111.to_string() + s112.to_string());
		v = (((v ^ temp) ^ DIV(s113)) ^ F);

		for(int i = 0; i < SStuff.size()-1; i++){
			SStuff[i] = SStuff[i+1];
		}
		SStuff[15] = v;
	}
	else{
		bitset<32> v(s11.to_string() + s22.to_string() + s33.to_string() + "00000000");
		v = ((v ^ mulA(s00)) ^ SStuff[2]);
		bitset<32> temp("00000000" + s110.to_string() + s111.to_string() + s112.to_string());
		v = ((v ^ temp) ^ DIV(s113));
		for(int i = 0; i < SStuff.size()-1; i++){
			SStuff[i] = SStuff[i+1];
		}
		SStuff[15] = v;
	}
}

bitset<32> SR(bitset<32> w, int (&Sr)[256]){
	bitset<32> divider(0b00000000000000000000000011111111);
	bitset<8> w3 = (divider & w).to_ulong();
	bitset<8> w2 = (divider & (w >> 8)).to_ulong();
	bitset<8> w1 = (divider & (w >> 16)).to_ulong();
	bitset<8> w0 = (divider & (w >> 24)).to_ulong();
	string temp = hexToBinary("0x1b");
	bitset<8> oneB(temp);

	bitset<8> r0 = (((((mulX((bitset<8>)Sr[w0.to_ulong()], oneB)) ^ (bitset<8>)Sr[w1.to_ulong()])) ^ ((bitset<8>)Sr[w2.to_ulong()])) ^ ((mulX((bitset<8>)Sr[w3.to_ulong()], oneB) ^ (bitset<8>)Sr[w3.to_ulong()])));
	bitset<8> r1 = (((((mulX((bitset<8>)Sr[w0.to_ulong()], oneB)) ^ (bitset<8>)Sr[w0.to_ulong()]) ^ (mulX((bitset<8>)Sr[w1.to_ulong()], oneB))) ^ (bitset<8>)Sr[w2.to_ulong()]) ^ (bitset<8>)Sr[w3.to_ulong()]);
	bitset<8> r2 = (((((bitset<8>)Sr[w0.to_ulong()]) ^ ((mulX((bitset<8>)Sr[w1.to_ulong()], oneB)) ^ (bitset<8>)Sr[w1.to_ulong()])) ^ (mulX((bitset<8>)Sr[w2.to_ulong()], oneB))) ^ (bitset<8>)Sr[w3.to_ulong()]);
	bitset<8> r3 = (((((bitset<8>)Sr[w0.to_ulong()]) ^ ((bitset<8>)Sr[w1.to_ulong()])) ^ ((mulX((bitset<8>)Sr[w2.to_ulong()], oneB)) ^ (bitset<8>)Sr[w2.to_ulong()])) ^ (mulX((bitset<8>)Sr[w3.to_ulong()], oneB)));
	bitset<32> retVal(r0.to_string() + r1.to_string() + r2.to_string() + r3.to_string());

	return retVal;
}

bitset<32> SQ(bitset<32> w, int (&Sq)[256]){
	bitset<32> divider(0b00000000000000000000000011111111);
	bitset<8> w3 = (divider & w).to_ulong();
	bitset<8> w2 = (divider & (w >> 8)).to_ulong();
	bitset<8> w1 = (divider & (w >> 16)).to_ulong();
	bitset<8> w0 = (divider & (w >> 24)).to_ulong();

	string temp = hexToBinary("0x69");
	bitset<8> six9(temp);

	bitset<8> r0 = (((((mulX((bitset<8>)Sq[w0.to_ulong()], six9)) ^ (bitset<8>)Sq[w1.to_ulong()])) ^ ((bitset<8>)Sq[w2.to_ulong()])) ^ ((mulX((bitset<8>)Sq[w3.to_ulong()], six9) ^ (bitset<8>)Sq[w3.to_ulong()])));
	bitset<8> r1 = (((((mulX((bitset<8>)Sq[w0.to_ulong()], six9)) ^ (bitset<8>)Sq[w0.to_ulong()]) ^ (mulX((bitset<8>)Sq[w1.to_ulong()], six9))) ^ (bitset<8>)Sq[w2.to_ulong()]) ^ (bitset<8>)Sq[w3.to_ulong()]);
	bitset<8> r2 = (((((bitset<8>)Sq[w0.to_ulong()]) ^ ((mulX((bitset<8>)Sq[w1.to_ulong()], six9)) ^ (bitset<8>)Sq[w1.to_ulong()])) ^ (mulX((bitset<8>)Sq[w2.to_ulong()], six9))) ^ (bitset<8>)Sq[w3.to_ulong()]);
	bitset<8> r3 = (((((bitset<8>)Sq[w0.to_ulong()]) ^ ((bitset<8>)Sq[w1.to_ulong()])) ^ ((mulX((bitset<8>)Sq[w2.to_ulong()], six9)) ^ (bitset<8>)Sq[w2.to_ulong()])) ^ (mulX((bitset<8>)Sq[w3.to_ulong()], six9)));
	bitset<32> retVal(r0.to_string() + r1.to_string() + r2.to_string() + r3.to_string());

	return retVal;
}

bitset<8> mulX(bitset<8> V, bitset<8> c){
	bitset<8> temp;
	temp = V >> 7;
	if(temp.to_ulong() == 1){
		return ((V << 1) ^ c);
	}
	else{
		return (V << 1);
	}
}

bitset<8> mulY(bitset<8> V, int i, bitset<8> c){
	if(i == 0){
		return V;
	}
	else{
		return mulX(mulY(V, i-1, c), c);
	}
}

bitset<32> mulA(bitset<8> c){
	string temp = hexToBinary("0xa9");
	bitset<8> anine(temp);
	bitset<32> retVal(mulY(c, 23, anine).to_string() + mulY(c, 245, anine).to_string() + mulY(c, 48, anine).to_string() + mulY(c, 239, anine).to_string());
	return retVal;
}

bitset<32> DIV(bitset<8> c){
	string temp = hexToBinary("0xa9");
	bitset<8> anine(temp);
	bitset<32> retVal(mulY(c, 16, anine).to_string() + mulY(c, 39, anine).to_string() + mulY(c, 6, anine).to_string() + mulY(c, 64, anine).to_string());
	return retVal;
}

string hexToBinary(string address){
			string binary = "";
			for (int i = 2; i < address.length (); ++i)
			{
				switch (address [i])
				{
					case '0': binary.append ("0000"); break;
					case '1': binary.append ("0001"); break;
					case '2': binary.append ("0010"); break;
					case '3': binary.append ("0011"); break;
					case '4': binary.append ("0100"); break;
					case '5': binary.append ("0101"); break;
					case '6': binary.append ("0110"); break;
					case '7': binary.append ("0111"); break;
					case '8': binary.append ("1000"); break;
					case '9': binary.append ("1001"); break;
					case 'a': binary.append ("1010"); break;
					case 'b': binary.append ("1011"); break;
					case 'c': binary.append ("1100"); break;
					case 'd': binary.append ("1101"); break;
					case 'e': binary.append ("1110"); break;
					case 'f': binary.append ("1111"); break;
				}
			}
			return binary;
		}

string binaryToHex(string address){
			string binary = "";
			unordered_map<string, string> hexMap;
					hexMap["0000"] = "0";
					hexMap["0001"] = "1";
					hexMap["0010"] = "2";
					hexMap["0011"] = "3";
					hexMap["0100"] = "4";
					hexMap["0101"] = "5";
					hexMap["0110"] = "6";
					hexMap["0111"] = "7";
					hexMap["1000"] = "8";
					hexMap["1001"] = "9";
					hexMap["1010"] = "a";
					hexMap["1011"] = "b";
					hexMap["1100"] = "c";
					hexMap["1101"] = "d";
					hexMap["1110"] = "e";
					hexMap["1111"] = "f";

					for(int i = 0; i < address.length(); i += 4){
						binary += hexMap.at(address.substr(i, 4));
					}
			return binary;
		}
