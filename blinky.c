/*	blinky.c
 * Adrian Prananda Lincong Li
 * 30 / Sept / 2015
 *
 *	Blinks and external LED from gpio0[8] = x70 pin 27
 */

#include <stdio.h>      // for File IO and printf
#include <time.h>       // for usleep
#include <math.h>

#define GPIO_PIN_45 45   
#define GPIO_PIN_115 47
#define GPIO_PIN_117 27   // LED pin
int main() {

	// Creates the File pointers to create the gpio file system,
	// set the direction of the GPIO, and change the data stored there.
	FILE *sys, *sys2, *dir45, *dir115, *dir117, *dirduty, *dirT, *val45, *val115, *val117;

	// Specifies the file that the pointer will be used for (w = //write)
	sys = fopen("/sys/class/gpio/export", "w");
	sys2 = fopen("/sys/devices/bone_capemgr.9/slots", "w");
   
   // int fseek(FILE *stream, long int offset, int whence)
   // 	sets the file position of the stream to the given offset.
   //		Whence has the following constants:
   //			SEEK_SET = Beginning of file
   //			SEEK_CUR = Current position of the file pointer
   //			SEEK_END = End of file
   //
   //		In this instance fseek is not necessarily needed.
	fseek(sys, 0, SEEK_SET);
	fseek(sys2, 0, SEEK_END);

	// prints value inside quotes into given file.
	// %d means it will print some variable as a decimal.
	// GPIO_PIN is the variable refered to by %d.
	fprintf(sys, "%d", GPIO_PIN_45);
	fflush(sys);
	fprintf(sys, "%d", GPIO_PIN_115);
	fflush(sys);
	fprintf(sys, "%d", GPIO_PIN_117);
	fflush(sys);
	// Clears the FILE stream for sys file object.
	fprintf(sys2, "am33xx_pwm");
	fflush(sys2);
	fprintf(sys2, "bone_pwm_P8_19");
	fflush(sys2);

	//Set the gpio to output
	dir45 = fopen("/sys/class/gpio/gpio45/direction", "w");
	fseek(dir45, 0, SEEK_SET);
	fprintf(dir45, "%s", "out");
	fflush(dir45);
	
	dir115 = fopen("/sys/class/gpio/gpio47/direction", "w");
	fseek(dir115, 0, SEEK_SET);
	fprintf(dir115, "%s", "out");
	fflush(dir115);

	dir117 = fopen("/sys/class/gpio/gpio27/direction", "w");
	fseek(dir117, 0, SEEK_SET);
	fprintf(dir117, "%s", "out");
	fflush(dir117);

	dirduty = fopen("/sys/devices/ocp.3/pwm_test_P8_19.15/duty", "w");
	dirT = fopen("/sys/devices/ocp.3/pwm_test_P8_19.15/period", "w");

	//Opens the file that controls if the pin is high or low
	val45 = fopen("/sys/class/gpio/gpio45/value", "w");
	fseek(val45, 0, SEEK_SET);

	val115 = fopen("/sys/class/gpio/gpio47/value", "w");
	fseek(val115, 0, SEEK_SET);

	val117 = fopen("/sys/class/gpio/gpio27/value", "w");
	fseek(val117, 0, SEEK_SET);
	
	int counter[3] = {0, 0, 0};
	int count = 0;

	//Blinks the LED
	while(1) {
		//int note = roundf(220000 * pow(2, count / 8));
		//int dutyc = note / 2;
		int note = 200000 + (25000 * count);		
		int dutyc = note / 2;
		int temp0 = counter[0];
		int temp1 = counter[1];
		int temp2 = counter[2];
		counter[0] = ~temp0;
		counter[1] = temp0 ^ temp1;
		counter[2] = (~temp0 & temp2) | (~temp1 & temp2) | (temp0 & temp1 & ~temp2);
		fprintf(val45, "%d", counter[0]);
		fflush(val45);
		fprintf(val115, "%d", counter[1]);
		fflush(val115);
		fprintf(val117, "%d", counter[2]);
		fflush(val117);
		fprintf(dirduty, "%d", dutyc);
		fflush(dirduty);
		fprintf(dirT, "%d", note);
		fflush(dirT);
		count = (count + 1) % 8;
      // delays for given length of time in microseconds.
      usleep(500000);		
	
	}

   // close all files
	fclose(sys);
	fclose(sys2);
	fclose(dir45);
	fclose(dir115);
	fclose(dir117);
	fclose(dirT);
	fclose(dirduty);
	fclose(val45);
	fclose(val115);
	fclose(val117);
	return 0;
}
