/*	music.c
 * Brad Marquez, Joseph Rothlin, Aigerim Shintemirova
 * 10 / April / 2016
 *
 *	Blinks and external LED from gpio0[8] = x70 pin 27 // needs changing ************
 */

#include <stdio.h>      // for File IO and printf
#include <time.h>       // for usleep
#include <math.h>//********************************************* may delete later ****************//
#include <unistd.h> // for usleep


#define GPIO_PIN_45 45   // LED pin #1 for the down counter
#define GPIO_PIN_47 47	 // LED pin #2
#define GPIO_PIN_27 27   // LED pin #3
#define sleepTime 500000
int main() {

	// Creates pointers to interface with the files of the Beaglebone
	FILE *sys, *sys2, *dir45, *dir115, *dir117, *dirduty, *dirT, *val45, *val47, *val27;

	// Selects the files for writing in GPIO digital pins and the Pulse Width Modulation output
	sys = fopen("/sys/class/gpio/export", "w");
	sys2 = fopen("/sys/devices/bone_capemgr.9/slots", "w");
   
	// Sets the positions of the streams to the beginning for the GPIO digital pins
	// and the end for the Pulse Width Modulation output
	fseek(sys, 0, SEEK_SET); 
	fseek(sys2, 0, SEEK_END);

	// Writes the value corresponding to the GPIO digital pins used
	fprintf(sys, "%d", GPIO_PIN_45);
	fflush(sys);
	fprintf(sys, "%d", GPIO_PIN_47);
	fflush(sys);
	fprintf(sys, "%d", GPIO_PIN_27);
	fflush(sys);
	
	// Writes the PWM used and the corresponding PWM output pin
	fprintf(sys2, "am33xx_pwm");
	fflush(sys2);
	fprintf(sys2, "bone_pwm_P8_19");
	fflush(sys2);

	// Sets the direction of each GPIO to output
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
	
	// Sets the pointers to the appropriate duty and period files
	dirduty = fopen("/sys/devices/ocp.3/pwm_test_P8_19.15/duty", "w");
	dirT = fopen("/sys/devices/ocp.3/pwm_test_P8_19.15/period", "w");

	// Opens the file that controls if the pin is high or low
	val45 = fopen("/sys/class/gpio/gpio45/value", "w");
	fseek(val45, 0, SEEK_SET);

	val47 = fopen("/sys/class/gpio/gpio47/value", "w");
	fseek(val47, 0, SEEK_SET);

	val27 = fopen("/sys/class/gpio/gpio27/value", "w");
	fseek(val27, 0, SEEK_SET);
	
	// Displays the down counter, playing a distinct sound for each count value
	int counter[3] = {0, 0, 0};
	int count = 0;
	int noteSpace = 0;
	int note = 0;
	int dutyc = 0;
	while(1) {
		
		int noteAb = 2409639;
		int noteA = 2272727;
		int noteF = 2865330;
		int noteC = 1912046;
		int noteE = 1517451;
		int noteF2 = 1432665;
		
		
		// Sets note and duty cycle for the Pulse Width Modulation output
		if (noteSpace == 99) { // Plays a distinct note for each count
			note = 200000 + (25000 * count);		
			dutyc = note / 2;
		} else if (noteSpace % 2 == 0) { // Plays The Imperial March
			if (count < 4 || count == 5 || count > 6) { 
				note = noteA;
				dutyc = note / 4;
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			} else if (count == 4 || count == 6) {
				note = noteF;
				dutyc = note / 2;
				
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
				usleep(sleepTime * 3 / 4);
				
				note = noteC;
				dutyc = note / 2;
				
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			} 	
		} else {
			if (count < 4) {
				note = noteE;
				dutyc = note / 2;
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
				
			} else if (count == 4) {
				note = noteF2;
				dutyc = note / 2;
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
				usleep(sleepTime * 3 / 4);
				
				note = noteC;
				dutyc = note / 2;
				
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			} else if (count == 5) {
				note = noteAb;
				dutyc = note / 2;
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			} else if (count == 6){
				note = noteF;
				dutyc = note / 2;
				
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
				usleep(sleepTime * 3 / 4);
				
				note = noteC;
				dutyc = note / 2;
				
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			} else {
				note = noteA;
				dutyc = note / 2;
				fprintf(dirduty, "%d", dutyc); // make into method
				fflush(dirduty);
				fprintf(dirT, "%d", note);
				fflush(dirT);
			}	
		}
			
		// Increments time counters
		count = (count + 1) % 8;
		if (count == 0) {
			noteSpace = (noteSpace + 1) % 100;
		}
		
		// Creates the binary representation of the looping down counter
		fprintf(val45, "%d", counter[0]);
		fflush(val45);
		fprintf(val47, "%d", counter[1]);
		fflush(val47);
		fprintf(val27, "%d", counter[2]);
		fflush(val27);
		int temp0 = counter[0];
		int temp1 = counter[1];
		int temp2 = counter[2];
		counter[0] = ~temp0;
		counter[1] = temp0 ^ temp1;
		counter[2] = (~temp0 & temp2) | (~temp1 & temp2) | (temp0 & temp1 & ~temp2);
		
      // Delays for the given constant located at the top of the file in microseconds
      usleep(sleepTime);		
	}

    // Closes all accessed files
	fclose(sys);
	fclose(sys2);
	fclose(dir45);
	fclose(dir115);
	fclose(dir117);
	fclose(dirT);
	fclose(dirduty);
	fclose(val45);
	fclose(val47);
	fclose(val27);
	return 0;
}
