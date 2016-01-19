/*
 * This program is to collect data from laser scanner
 */
#include <iostream>
#include "network/SocketClient.h"
#include <stdlib.h>
#include <string>
#include <cstring>
using namespace std;
using namespace exploringBB;

//Declare global variables
struct SickData
{
	int angle;
	int distance;
};
char stx = (char)2;
char etx = (char)3;


// Declare prototypes
string getData(string addr, int port, string cmd, int buf);
struct SickData * parseSickData(string raw, int startAddr, int endAddr, int dataSize, int buf);


int main()
{
   //Declaring variables
   string sickAddr = "10.99.11.18";
   int sickPort = 2112;
   int startAddr = 26;
   int endAddr = 206;
   int bufferSize = 1024;
   int dataSize = 181;
   string cmdString = "sRN LMDscandata";
   string SickDataRaw = "";

   struct SickData * SickOutput;



   SickDataRaw = getData(sickAddr,sickPort,cmdString,bufferSize);
   SickOutput = parseSickData(SickDataRaw, startAddr, endAddr, dataSize, bufferSize);
   for(int i = 0; i < dataSize; i++)
   {
	   cout << SickOutput[i].angle << " " << SickOutput[i].distance << endl;
   }

}



string getData(string addr, int port, string cmd, int buf)
{
	string cmdString = "";
	string SickDataRaw = "";

	//Declares socket
	SocketClient sc(addr,port);
	//Connect to scanner
	sc.connectToServer();
	//Build command string
	cmdString += stx;
	cmdString += cmd;
	cmdString += etx;
	//Sends command to scanner
	sc.send(cmdString);

	//if (sc.isClientConnected()) { cout << "Still connected " << endl; }

	string s = sc.receive(buf);
	for(int i = 0; i <= buf;i++)
	{
		if(s[i] == stx)
		{
			for (int j = i; j <= buf; j++)
			{
			   if(s[j] != etx)
			   {
				   SickDataRaw += s[j];
			   }
			}

		}
	}
	return SickDataRaw;
}

struct SickData * parseSickData(string raw, int startAddr, int endAddr, int dataSize, int buf)
{
	string SickInfo[buf];
	struct SickData SickOutput[dataSize];
	int y = 0;
	int z = 0;
	//Creates parsed data
	char * cstr = new char[raw.length()+1];
	strcpy(cstr,  raw.c_str());
	char * p = strtok(cstr," ");
	while(p!=0)
	{
	   SickInfo[z] = p;
	   p = strtok(NULL," ");
	   z++;
	}
	delete[] cstr;
	for(int n = startAddr; n <= endAddr; n++)
	{
	   SickOutput[n-startAddr].angle = y;
	   y++;
	   SickOutput[n-startAddr].distance = (int)strtol(SickInfo[n].c_str(),0,16);
	}
	return SickOutput;
}





