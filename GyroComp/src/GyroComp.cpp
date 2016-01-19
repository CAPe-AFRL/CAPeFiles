//============================================================================
// Name        : TestARM.cpp
// Author      : Donald
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "BlackLib.h"
#include "BlackI2C/BlackI2C.h"
#include <unistd.h>
#include <string.h>


using namespace std;
using namespace BlackLib;

#define CTRL_REG1 0x20
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define GYRO_ADDR 0x68
static short raw[3] = {0,0,0};
static short offset[3] ={0,0,0};

void readData()
{
	BlackLib::BlackI2C gyro(BlackLib::I2C_1, GYRO_ADDR);
	gyro.open( BlackLib::ReadWrite | BlackLib::NonBlock );
	char temp[6];
	temp[0] = gyro.readByte(0x28);
	temp[1] = gyro.readByte(0x29);
  	temp[2] = gyro.readByte(0x2A);
   	temp[3] = gyro.readByte(0x2B);
   	temp[4] = gyro.readByte(0x2C);
   	temp[5] = gyro.readByte(0x2D);
   	raw[0] = (short)(temp[1] << 8 | temp[0]);
   	raw[1] = (short)(temp[3] << 8 | temp[2]);
  	raw[2] = (short)(temp[5] << 8 | temp[4]);
}

void calibration()
{
	float Gyro_Calib[3] = {0,0,0};
	const int count = 50;
	for(int i = 0; i < count; i++)
	{
		readData();
		for(int j = 0; j < 3; j++)
		{
			Gyro_Calib[j] += raw[j];
		}
	}
	for(int i = 0; i < 3; i++)
	{
		offset[i] = Gyro_Calib[i]/count;
	}

}

int main() {

	int x,y,z;
	short rx,ry,rz;

	BlackLib::BlackI2C gyro(BlackLib::I2C_1, GYRO_ADDR);
	gyro.open( BlackLib::ReadWrite | BlackLib::NonBlock );

	bool result = gyro.writeByte(CTRL_REG3,0x08);
	result = gyro.writeByte(CTRL_REG4,0x80);
	result = gyro.writeByte(CTRL_REG1,0x1F);

    calibration();
    while(1)
    {
    	readData();
    	x = raw[0] - offset[0];
    	y = raw[1] - offset[1];
    	z = raw[2] - offset[2];

    	cout << "x: " << (short)x << endl;
    	cout << "y: " << (short)y << endl;
    	cout << "z: " << (short)z << endl;
    }

	return 0;
}
