/*
  capteur_temperature.cpp

  Author:Thibault THETIER
  2019-05-07

  Measure the measure the Surrounding temperature around the sensor
  and the temperature of the target which is in front of the sensor.
  
  Hardware: Grove - Infrared Temperature Sensor
  
  Copyright 2019 Orange

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  
  http://www.apache.org/licenses/LICENSE-2.0
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/



#include <math.h>
#include "capteur_temperature.h"


void Temp_sensor::setup(int pin1, int pin2) 
{
	//analogReference(INTERNAL);//Not for MEGA, set the refenrence voltage 1.1V,the distinguishability can up to 1mV.
	analogReference(INTERNAL1V1);//(mega only)set the refenrence voltage 1.1V,the distinguishability can up to 1mV.
	this->sur_temp_pin = pin1;
	this->obj_temp_pin = pin2;
}

float Temp_sensor::binSearch(long x)// this function used for measure the surrounding temperature
{
	int low,mid,high;
	low=0;
	//mid=0;
	high=100;
	while (low<=high)
	{
		mid=(low+high)/2;
		if(x<res[mid])
			low= mid+1;
		else//(x>res[mid])
			high=mid-1;
	}
	return mid;
}

float Temp_sensor::arraysearch(float x,float y)//x is the surrounding temperature,y is the object temperature
{
	int i=0;
	float tem_coefficient=100;//Magnification of 100 times	
	i=(x/10)+1;//Ambient temperature			
	voltage=(float)y/tem_coefficient;//the original voltage		
	//Serial.print("sensor voltage:\t");		
	//Serial.print(voltage,5);	
	//Serial.print("V");			
	for(temp3=0;temp3<13;temp3++)		
	{			
		if((voltage>obj[temp3][i])&&(voltage<obj[temp3+1][i]))				
		{			
			return temp3;					
		}			
	}
}
float Temp_sensor::measureSurTemp()
{  
	unsigned char i=0;
	float current_temp1=0;	  
	int signal=0;	  
	tempValue=0;

	for(i=0;i<10;i++)       //	  
	{		  
		tempValue+= analogRead(sur_temp_pin); 		  
		delay(10); 	  
	}	  
	tempValue=tempValue/10;	  
	temp = tempValue*1.1/1023;	  
	R=2000000*temp/(2.50-temp);	  
	signal=binSearch(R);	  
	current_temp=signal-1+temp_calibration+(res[signal-1]-R)/(res[signal-1]-res[signal]);
	/*Serial.print("Surrounding temperature:");
	Serial.print(current_temp);*/
	return current_temp;
}

float Temp_sensor::measureObjectTemp()
{
	unsigned char i=0;  
	unsigned char j=0;  
	float sur_temp=0;  
	unsigned int array_temp=0;  
	float temp1,temp2; 
	float final_temp=0;
	objtValue=0;	
	for(i=0;i<10;i++)
	{
		objtValue+= analogRead(obj_temp_pin); 
		delay(10); 
    }       
	objtValue=objtValue/10;//Averaging processing     
	temp1=objtValue*1.1/1023;//+objt_calibration; 
	sur_temp=temp1-(reference_vol+offset_vol);
	
	/*Serial.print("\t Sensor voltage:");		
	Serial.print(sur_temp,3);	
	Serial.print("V");*/
	
	array_temp=arraysearch(current_temp,sur_temp*1000);        
	temp2=current_temp;        
	temp1=(temperature_range*voltage)/(obj[array_temp+1][(int)(temp2/10)+1]-obj[array_temp][(int)(temp2/10)+1]);        
	final_temp=temp2+temp1;   
	
	/*
	if((final_temp>100)||(final_temp<=-10))
		{
			Serial.println ("\t out of range!");
		}
	else
		{
			Serial.print("\t object temperature:");		
			Serial.println(final_temp,2); 
		}
	*/
	return final_temp;
}