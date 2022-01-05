# MTA F Line Real-Time Tracker
Arduino-nano powered circuit for fetching and displaying the current location of
active trains running along the NYC MTA's F line.

## Circuit

### Components

| Purpose | Part name | Data sheet | Num used |
| ------- | --------- | ---------- | -------- |
| Microprocessor | Arduino Nano (ATmega328P)| n/a | 1 |
| WiFi module | ESP8266-05 | www.estudioelectronica.com/wp-content/uploads/2018/09/SHT-ESP05i.pdf | 1 |
| 3-8 Demultiplexer | 74HCT138N | www.ti.com/lit/ds/symlink/sn74hct138.pdf | 1 |
| 4-16 Demultiplexer | 74HCT154N | www.assets.nexperia.com/documents/data-sheet/74HC_HCT154.pdf | 6 |
| 3.3V LDO Voltage Regulator | LM1117T-33V | https://www.jameco.com/Jameco/Products/ProdDS/242114NAT.pdf | 1 | 
| Light | Orange LED | n/a | 90 |

Total cost of components: ~$63 on Jameco.

### Explanation

The core microprocessor is an Arduino Nano. To power 90 LEDs without having 90
I/O pins, 6 4-16 demultiplexers are used. These are selected between by using
a single 3-8 demultiplexer with 2 unused outputs. This effectively allows us
to map a binary number (via output pins) to a single LED.

For WiFi, an ESP8266-05 unit is used. The Rx, Tx pins here operate at 3.3V, so
a LDO is used to step down the Arduino Nano's 5V I/O pin. The Arduino can read
3V as HIGH just fine, so a step-up converter is not needed.
