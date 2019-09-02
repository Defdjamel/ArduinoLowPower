/*
  Blink Sleep Mode
  Made by Je fais des trucs sur Youtube
  à partager sans limitation  :)

*/

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>



// the setup function runs once when you press reset or power the board
void setup() {
  //init serial
   Serial.begin(115200);
   Serial.println("Blink Sleep Mode");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //Setup WacthDog interrupe
   setupWatchDogTimer();
 
  //init power Save
  initPowerSave();
 
  //mode sleep
  sleepPwrDown();
  
  
}

// the loop function runs over and over again forever
void loop() {
           
}


// Setup the Watch Dog Timer (WDT)
void setupWatchDogTimer() {
  // The MCU Status Register (MCUSR) is used to tell the cause of the last
  // reset, such as brown-out reset, watchdog reset, etc.
  // NOTE: for security reasons, there is a timed sequence for clearing the
  // WDE and changing the time-out configuration. If you don't use this
  // sequence properly, you'll get unexpected results.

  // Clear the reset flag on the MCUSR, the WDRF bit (bit 3).
  MCUSR &= ~(1<<WDRF);

  // Configure the Watchdog timer Control Register (WDTCSR)
  // The WDTCSR is used for configuring the time-out, mode of operation, etc

  // In order to change WDE or the pre-scaler, we need to set WDCE (This will
  // allow updates for 4 clock cycles).

  // Set the WDCE bit (bit 4) and the WDE bit (bit 3) of the WDTCSR. The WDCE
  // bit must be set in order to change WDE or the watchdog pre-scalers.
  // Setting the WDCE bit will allow updates to the pre-scalers and WDE for 4
  // clock cycles then it will be reset by hardware.
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /**
   *  Setting the watchdog pre-scaler value with VCC = 5.0V and 16mHZ
   *  WDP3 WDP2 WDP1 WDP0 | Number of WDT | Typical Time-out at Oscillator Cycles
   *  0    0    0    0    |   2K cycles   | 16 ms
   *  0    0    0    1    |   4K cycles   | 32 ms
   *  0    0    1    0    |   8K cycles   | 64 ms
   *  0    0    1    1    |  16K cycles   | 0.125 s
   *  0    1    0    0    |  32K cycles   | 0.25 s
   *  0    1    0    1    |  64K cycles   | 0.5 s
   *  0    1    1    0    |  128K cycles  | 1.0 s
   *  0    1    1    1    |  256K cycles  | 2.0 s
   *  1    0    0    0    |  512K cycles  | 4.0 s
   *  1    0    0    1    | 1024K cycles  | 8.0 s
  */
  WDTCSR  = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0); // 8.0s @16MHz
  // Enable the WD interrupt (note: no reset).
  WDTCSR |= _BV(WDIE);

 
}

void initPowerSave(){
  ADCSRA = 0;  // disable ADC to save 0.1mA
  //disable pin interrupt
  detachInterrupt(digitalPinToInterrupt(0));
  detachInterrupt(digitalPinToInterrupt(1));
}

void sleepPwrDown() {
   Serial.println("sleep Mode zzzz...zzz");
   delay(10);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();


    // First thing to do is disable sleep.
  sleep_disable();

  // Re-enable the peripherals.
  power_all_enable();
  Serial.println("Reveil");

    wakeCallback();
   delay(10);
   sleepPwrDown();
   
}

void wakeCallback() {
    /* Clignote et remise en veille */
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}


// Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect) {
 
  Serial.println("WatchDog TimeOut!");

  
  
}
