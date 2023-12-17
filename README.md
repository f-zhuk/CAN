# CAN
## General description
The work is in progress and is currently not ready for real-life application.  
This repository contains hardware, firmware, and software dedicated to the creation of custom CANopen systems for vehicles.  
Such custom systems could fit old cars with heavily damaged harnesses and vehicles that do not have electronic equipment by default, for example, boats, kayaks, and bicycles.
## Hardware
The complete system should consist of multiple functional blocks. Blocks should be as cheap and simple as possible while implementing complete functions like combination switch assembly, left tail light assembly, and door controls.  
Each functional block should be designed around a unified MCU module and simple interconnection boards to adapt signals from the MCU module to the systems of the block.  
Interconnection boards may provide 24LC I2C EEPROM memory for identification and non-volatile parameter storage.  
### MCU
MCU module should be self-sufficient and electrically ready for insertion in the CAN bus system. To achieve this, the MCU module has a power supply converter and CAN driver aside from the controller.  
For the first prototype, the PIC18 family was selected. PIC18F83K26 has a built-in CAN periphery and a reasonable price.  
MCU module has +12V power input, +5V power input/output, CAN, UART, 8xGPIO(PC7:PC0)  
### USB-UART
Most important interconnection board. It provides a USB to UART bridge to provide a simple debug interface.  
USB-UART board is built with MCP2200. It is connected not only through UART but also 5xGPIO. Additionally, 24LC16 I2C EEPROM memory is connected to C6 and C7. C5 is connected to the bus termination control.  
## Firmware
Heavily updated code described in AN945. The application note code was written for an older MCU. PIC18F83K26AN945 is not supported by the compiler the code was written for and the code is not compatible with the new compiler.  
AN945 default config:  
ADC is on (probably unused)  
PORT D is all output (probably unused)  
PORT B pin 5 is bit 0 of TPDO1, pin 4 is bit 1  
State of PORTB pins 4 and 5 compared to their states on previous DemoProcessEvents() call, change, rise and fall events detected and distinguished, written to OD  
Dictionary object 0x6005subondex 1 (uIOinIntEnable) bits 0 and 1  
Async transmission for TPDO1 by default  
PDO transmission type could be changed by writing to TPDO1 subindex 2  
## Software
The software is written in Python.  
