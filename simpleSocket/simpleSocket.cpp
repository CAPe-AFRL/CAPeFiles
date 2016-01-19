/* A Simple Socket Example
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include "network/SocketClient.h"
#include <stdlib.h>
#include <string>
#include <cstring>
using namespace std;
using namespace exploringBB;

int main(){
   string cmdString = "";
   string SickData = "";
   string SickInfo[1024];
   char stx = (char)2;
   char etx = (char)3;
   int z;
   float f;
   long l;
   cout << "Starting EBB Socket Example" << endl;
   SocketClient sc("10.99.11.18",2112);
   sc.connectToServer();
   cmdString += (char)2;
   cmdString += "sRN LMDscandata";
   cmdString += (char)3;
   cout << cmdString << endl;
   sc.send(cmdString);

   if (sc.isClientConnected()) { cout << "Still connected " << endl; }
   while(1){
   cout << "Receiving Data" << endl;
   string s = sc.receive(1024);
   for(int i = 0; i <= 1024;i++)
   {
      if(s[i] == stx)
      {
        for (int j = i; j <= 1024; j++)
        { 
	   if(s[j] != etx)
           {
              SickData += s[j];
           }
        }
        break;
      }
   }
   char * cstr = new char[SickData.length()+1];
   strcpy(cstr,  SickData.c_str());
   char * p = strtok(cstr," ");
   z = 0;
   while(p!=0)
   {
      //cout << "[" << p << "]" << endl;
      SickInfo[z] = p;
      p = strtok(NULL," ");
      z++;
   }
   //delete[] cstr;
   for(int n = 0; n <= 255; n++){
      
      cout << SickInfo[n] << " " << (int)strtol(SickInfo[n].c_str(),0,16)  << endl;
   }
   break;
   }
   
}
