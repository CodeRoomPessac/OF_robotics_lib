/*
  capteur_temperature.h

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


#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include <Arduino.h>
#include <math.h>

class Temp_sensor
{
public :

	Temp_sensor();
	void setup(int pin1, int pin2);
	float binSearch(long x); // this function used for measure the surrounding temperature
	float arraysearch(float x,float y); //x is the surrounding temperature,y is the object temperature
	float measureSurTemp();
	float measureObjectTemp();

private :

	int sur_temp_pin; // Analog input pin connect to temperature sensor SUR pin
	int obj_temp_pin;// Analog input pin connect to temperature sensor OBJ pin

	float temp_calibration;			//this parameter was used to calibrate the temperature
	//float objt_calibration=0.000; //this parameter was used to calibrate the object temperature
	float temperature_range;		//we make a map of temperature-voltage according to sensor datasheet. 10 is the temperature step when sensor and 
								   //object distance is 9CM.
	float offset_vol;				//this parameter was used to set the mid level voltage,when put the sensor in normal environment after 10 min,
								   //the sensor output 0.For example,the surrounding temperature is 29℃，but the result is 27℃ via the sensor,
								   //you should set the reerence to 0.520 or more,according to your sensor to change.
								   //the unit is V
	float tempValue; 
	float objtValue;  
	float current_temp;
	float temp;
	float temp1;
	float temp2;
	unsigned int temp3;
	const float reference_vol;
	unsigned char clear_num;		//when use lcd to display
	float R;
	float voltage;

	long res[100]={
					 318300,302903,288329,274533,261471,249100,237381,226276,215750,205768,
					 196300,187316,178788,170691,163002,155700,148766,142183,135936,130012,
					 124400,119038,113928,109059,104420,100000,95788,91775,87950,84305,
					 80830,77517,74357,71342,68466,65720,63098,60595,58202,55916,
					 53730,51645,49652,47746,45924,44180,42511,40912,39380,37910,
					 36500,35155,33866,32631,31446,30311,29222,28177,27175,26213,
					 25290,24403,23554,22738,21955,21202,20479,19783,19115,18472,
					 17260,16688,16138,15608,15098,14608,14135,13680,13242,12819,
					 12412,12020,11642,11278,10926,10587,10260,9945,9641,9347,
					 9063,8789,8525,8270,8023,7785,7555,7333,7118,6911};
					 
	float obj [13][12]={
	/*0*/             { 0,-0.274,-0.58,-0.922,-1.301,-1.721,-2.183,-2.691,-3.247,-3.854,-4.516,-5.236}, //
	/*1*/             { 0.271,0,-0.303,-0.642,-1.018,-1.434,-1.894,-2.398,-2.951,-3.556,-4.215,-4.931},  //→surrounding temperature,from -10,0,10,...100
	/*2*/             { 0.567,0.3,0,-0.335,-0.708,-1.121,-1.577,-2.078,-2.628,-3.229,-3.884,-4.597},   //↓object temperature,from -10,0,10,...110
	/*3*/             { 0.891,0.628,0.331,0,-0.369,-0.778,-1.23,-1.728,-2.274,-2.871,-3.523,-4.232},
	/*4*/             { 1.244,0.985,0.692,0.365,0,-0.405,-0.853,-1.347,-1.889,-2.482,-3.13,-3.835},
	/*5*/             { 1.628,1.372,1.084,0.761,0.401,0,-0.444,-0.933,-1.47,-2.059,-2.702,-3.403},
	/*6*/             { 2.043,1.792,1.509,1.191,0.835,0.439,0,-0.484,-1.017,-1.601,-2.24,-2.936},
	/*7*/             { 2.491,2.246,1.968,1.655,1.304,0.913,0.479,0,-0.528,-1.107,-1.74,-2.431},
	/*8*/             { 2.975,2.735,2.462,2.155,1.809,1.424,0.996,0.522,0,-0.573,-1.201,-1.887},
	/*9*/             { 3.495,3.261,2.994,2.692,2.353,1.974,1.552,1.084,0.568,0,-0.622,-1.301},
	/*10*/            { 4.053,3.825,3.565,3.27,2.937,2.564,2.148,1.687,1.177,0.616,0,-0.673},
	/*11*/            { 4.651,4.43,4.177,3.888,3.562,3.196,2.787,2.332,1.829,1.275,0.666,0},
	/*12*/            { 5.29,5.076,4.83,4.549,4.231,3.872,3.47,3.023,2.527,1.98,1.379,0.72}
	};

};

inline Temp_sensor::Temp_sensor() : 
	temp_calibration(0), temperature_range(10), 
	offset_vol(0.014), tempValue(0), 
	objtValue(0), current_temp(0),
	temp(0), temp1(0), temp2(0), temp3(0),
	reference_vol(0.500), clear_num(0), 
	R(0), voltage(0)
{}


#endif