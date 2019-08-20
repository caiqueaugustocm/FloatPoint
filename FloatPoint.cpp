#include <stdio.h> 
#include<iostream>
#include<string>
#include <stdlib.h>
#include<bitset>
#include <cstring>
#include <math.h>

using namespace std;

string converterBinary(long long int n, long long int i) 
{
    int k;
    string finalValue;
    for (k = i - 1; k >= 0; k--) { 
  
        if ((n >> k) & 1){
            finalValue += "1";
		}
        else{
            finalValue += "0";
		}
    }
    return finalValue;
}

typedef union { 
  
    float fsimple; 
    struct
    {  
        unsigned int mantissaSF : 4; 
        unsigned int exponentSF : 3; 
        unsigned int signSF : 1; 
    } raw; 
} mySimpleFloat; 

typedef union { 
  
    float f; 
    struct
    {  
        unsigned long int mantissaF : 23; 
        unsigned long int exponentF : 8; 
        unsigned long int signF : 1; 
  
    } raw; 
} myFloat; 

typedef union { 
  
    double d; 
    struct
    {  
        unsigned long long int mantissaD : 52; 
        unsigned long long int exponentD : 11; 
        unsigned long long int signD : 1;  
    } raw; 
} myDouble; 

void printHEX(long long int binaryNumber){
	int hex[100];
	int i = 1, j = 0;
	long long int rem, dec = 0;
	while (binaryNumber > 0) 
	{
		rem = binaryNumber % 2;
		dec = dec + rem * i;
		i = i * 2;
   		binaryNumber = binaryNumber / 10;
  	}//primeiro
	i = 0;
	while (dec != 0) 
	{
		hex[i] = dec % 16;
	   	dec = dec / 16;
	   	i++;
	}//segundo
	for (j = i - 1; j >= 0; j--)
	{//printar
		if (hex[j] > 9) 
		{	
			cout<<(char)(hex[j] + 55);
		} 
	   	else
	   	{
	    	cout<<hex[j];
	   	}
	}
}

void printIEEE8(mySimpleFloat var) 
{
	int i, j, k;  
  	string bin8Sin, bin8Exp, bin8Man, bin8Total, bin8TotalAux;
	bitset<8> bit(var.fsimple);
	bin8Total = bit.to_string();
	
	for(int i = 0; i <=7; i++){
		if(i == 0){
			bin8Sin += bin8Total[i];
		}
		if(i>=1 & i<=3){
			bin8Exp += bin8Total[i];
		}
		if(i>=4 & i<=7){
			bin8Man += bin8Total[i];
		}
	}
	
    cout << bin8Sin << " | " << bin8Exp << " | " << bin8Man << endl;
    
    string bin8Aux1, bin8Aux2;
    bin8Aux1.append(bin8Total,0,4);
    bin8Aux2.append(bin8Total,4,4);
    char bin8Aux1C[bin8Aux1.size() + 1], bin8Aux2C[bin8Aux2.size() + 1];
	strcpy(bin8Aux1C, bin8Aux1.c_str());
	strcpy(bin8Aux2C, bin8Aux2.c_str());
    
    unsigned long int hex8Int = strtol(bin8Aux1C, NULL, 2);
    unsigned long int hex8End = strtol(bin8Aux2C, NULL, 2);
    if(!hex8End){
    	cout << "Em hexa eh: "<< uppercase << hex << hex8Int << "00" << endl;
	}else cout << "Em hexa eh: "<< uppercase << hex << hex8Int << hex << hex8End << endl;
    
    
}

void printIEEE32(myFloat var) 
{  
	string bin32Sin, bin32Exp, bin32Man, bin32Total;
	bin32Sin = converterBinary(var.raw.signF, 1);
    bin32Exp = converterBinary(var.raw.exponentF, 8);
    bin32Man = converterBinary(var.raw.mantissaF, 23);
    bin32Total = bin32Sin + bin32Exp + bin32Man;
    
    string bin32Aux1, bin32Aux2;
    bin32Aux1.append(bin32Total,0,16);
    bin32Aux2.append(bin32Total,16,16);
    char bin32Aux1C[bin32Aux1.size() + 1], bin32Aux2C[bin32Aux2.size() + 1];
	strcpy(bin32Aux1C, bin32Aux1.c_str());
	strcpy(bin32Aux2C, bin32Aux2.c_str());
	
    cout << bin32Sin << " | " << bin32Exp << " | " << bin32Man << endl;
    
    unsigned long int hex32Int = strtol(bin32Aux1C, NULL, 2);
    unsigned long int hex32End = strtol(bin32Aux2C, NULL, 2);
    if(!hex32End){
    	cout << "Em hexa eh: "<< uppercase << hex << hex32Int << "0000" << endl;
	}else cout << "Em hexa eh: " << uppercase << hex << hex32Int << hex << hex32End << endl;
}

void printIEEE64(myDouble var) 
{  
  	string bin64Sin, bin64Exp, bin64Man, bin64Total; 
	bin64Sin = converterBinary(var.raw.signD, 1);
    bin64Exp = converterBinary(var.raw.exponentD, 11);
    bin64Man = converterBinary(var.raw.mantissaD, 52);
    bin64Total = bin64Sin + bin64Exp + bin64Man;
    
    string bin64Aux1, bin64Aux2;
    bin64Aux1.append(bin64Total,0,32);
    bin64Aux2.append(bin64Total,32,32);
    char bin64Aux1C[bin64Aux1.size() + 1], bin64Aux2C[bin64Aux2.size() + 1];
	strcpy(bin64Aux1C, bin64Aux1.c_str());
	strcpy(bin64Aux2C, bin64Aux2.c_str());
	
	cout << bin64Sin << " | " << bin64Exp << " | " << bin64Man << endl;
	
	bin64Aux1C[0] = '0';
	unsigned long int hex64Int = strtol(bin64Aux1C, NULL, 2);
	if(var.raw.signD) hex64Int += pow(2,31);
    unsigned long int hex64End = strtol(bin64Aux2C, NULL, 2);    
    if(!hex64End){
    	cout << "Em hexa eh: 0x"<< uppercase << hex << hex64Int << "00000000" << endl;
	}else cout << "Em hexa eh: 0x"<< uppercase << hex << hex64Int << hex << hex64End << endl;
}

int main() 
{ 
  
    myFloat var;
    myDouble var2;
    mySimpleFloat var3;
    cout << "Digite o valor desejado:" << endl;
    cin >> var.f; 
	var2.d = var.f; var3.fsimple = var.f;
    system("cls");
    cout << "A representação em binario do " << var.f << " eh:" << endl << endl;
//    print com 8 bits
	cout << "8 Bits: ";
	printIEEE8(var3);
    cout << endl;
//    print com 32 bits
    cout << "32 Bits: ";
	printIEEE32(var);
	cout << endl;
//    printi com 64 bits
    cout << "64 Bits: ";
	printIEEE64(var2);
	cout << endl;
  
    return 0; 
}
