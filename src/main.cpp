#include <Arduino.h>
#include <SPI.h>
#include <RH_RF69.h>

/*
 * Information regarding automatic meter reading is mostly taken from the following transmitTimeOffset
 * - https://www.mathworks.com/help/supportpkg/plutoradio/examples/automatic-meter-reading.html
 * - https://github.com/bemasher/rtlamr
 * RF hardware https://learn.adafruit.com/adafruit-rfm69hcw-and-rfm96-rfm95-rfm98-lora-packet-padio-breakouts
 * Library for that module http://www.airspayce.com/mikem/arduino/RadioHead/classRH__RF69.html
- Baudrate
Modulation
From http://www.smartmetereducationnetwork.com/uploads/how-to-tell-if-I-have-a-ami-dte-smart-advanced-meter/Itron%20Centron%20Meter%20Technical%20Guide1482163-201106090057150.pdf

Utilizing the 96-bit Itron® Standard Consumption Message protocol (SCM), the C1SR
provides the energy (kWh) consumption, module ID number, tamper indications, meter
type, and error checking information in each radio frequency transmission. Within the 96
-bit SCM, 26 bits are allocated to the module ID number for meter identification (also
referred to as ERT ID number). As of October 15, 1999, all CENTRON C1SR meters utilize 26
-bit identification numbers.
The C1SR uses frequency hopping and transmits within the unlicensed 910 to 920 MHz
band on an average of once per second. In order to avoid interference from other devices,
the transmission frequencies and time interval between transmission cycles are completely
random in nature.

The RF transmission is spread spectrum using Binary Phase Shift Keyed (BPSK) modulation. A chipping signal
is used to spread the carrier and actual data is on-off-keyed (OOK). The modulator output drives the
amplifier chain that provides a signal of approximately 100mW. The antenna is tuned for maximum efficiency
at the carrier frequency

Interval Data Message (IDM Message)
 * Training sync        0x5555  (2 byte, fix)
 * Frame sync           0x16a3  (2 byte, fix)
 * Packet type          0x1c    (1 byte, fix)
 * Packet length        0x5cc6  (2 byte, fix)
 * Application version  0x04    (1 byte, fix)
 * ERT type             0x17    (1 byte, last 4 bits determine type)
*/

#define RFM69_FREQ 915.0
#define RFM69_CS   16
#define RFM69_INT  21
#define RFM69_RST  17
#define LED        LED_BUILTIN

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

void setup() {
  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);
  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RFM69_FREQ)) {
    Serial.println("setFrequency failed");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}