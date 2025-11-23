/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26K83
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#define CAN_MSG_LEN 14
#define SERIAL_BUF_LEN CAN_MSG_LEN*100

enum TX_State {
  SIGNATURE1,
  SIGNATURE2,
  IDH,
  IDL,
  DLC,
  DATA,
  CONTROL
};

uint8_t circular_buffer[SERIAL_BUF_LEN];
uint16_t top_pointer = 0;
uint16_t bot_pointer = 0;
uint16_t buf_length = 0;

uint8_t status = 0;
/*
                         Main application
 */

void serial_buffer_add(uint8_t *buffer_ptr, uint8_t length)
{
    if (buf_length+length <= SERIAL_BUF_LEN)
    {
        buf_length += length;
        for(uint8_t counter = 0; counter < length; counter++)
        {        
            circular_buffer[top_pointer] = buffer_ptr[counter];
            top_pointer = (top_pointer<SERIAL_BUF_LEN) ? top_pointer+1 : 0;
        }
    }
    else
        status |= 0x01;
}
/*
void serial_buffer_add(uint8_t *buffer_ptr)
{
    if (buf_length+CAN_MSG_LEN <= SERIAL_BUF_LEN)
    {
        buf_length += CAN_MSG_LEN;
        for(uint8_t counter = 0; counter < CAN_MSG_LEN; counter++)
        {        
            circular_buffer[top_pointer] = buffer_ptr[counter];
            top_pointer = (top_pointer<SERIAL_BUF_LEN) ? top_pointer+1 : 0;
        }
    }
    else
        status |= 0x01;
}*/

static void RXB0InterruptHandler(void) 
{
    uint8_t counter = 0;
    uint16_t identificator = RXB0SIDH;
    identificator = (identificator<<3) | (RXB0SIDL>>5);
    uint8_t buffer[CAN_MSG_LEN];
    volatile unsigned char* data[8] = 
    {
        &RXB0D0,
        &RXB0D1,
        &RXB0D2,
        &RXB0D3,
        &RXB0D4,
        &RXB0D5,
        &RXB0D6,
        &RXB0D7
    };
    
    IO_RB4_Toggle();
    
    buffer[0] = 0x55;
    buffer[1] = 0xAA;
    
    buffer[2] = (identificator>>8)&0xFF;
    buffer[3] = identificator&0xFF;
    buffer[4] = RXB0DLC;
    
    for (counter = 0; counter < buffer[4]; counter++)
    {
        buffer[5+counter] = *data[counter];
    }
    //buffer[5] = RXB0D0;
    //buffer[6] = RXB0D1;
    //buffer[7] = RXB0D2;
    //buffer[8] = RXB0D3; 
    //buffer[9] = RXB0D4;
    //buffer[10] = RXB0D5;  
    //buffer[11] = RXB0D6;  
    //buffer[12] = RXB0D7;  
    buffer[5+counter] = COMSTAT;
    
    COMSTAT = 0;
    RXB0CONbits.RXFUL = 0;
    PIR5bits.RXB0IF = 0;
    
    serial_buffer_add(buffer, (6+counter));
}

void ECAN_Initialize_user(void)
{
    CANCON = 0x80;
    while (0x80 != (CANSTAT & 0xE0)); // wait until ECAN is in config mode
    
    /**
    Mode 0
    */
    ECANCON = 0x00;
    
    /**
    Initialize CAN I/O
    */
    CIOCON = 0x00;
    
    /**
    Mask and Filter definitions
    ........................................................    
    CAN ID		ID Type		Mask				Filter		Buffer    
    ........................................................    
    ........................................................
    */
 
/**    
    Initialize Receive Masks
*/   
    RXM0EIDH = 0x00;
    RXM0EIDL = 0x00;
    RXM0SIDH = 0x00;
    RXM0SIDL = 0x00;
    RXM1EIDH = 0x00;
    RXM1EIDL = 0x00;
    RXM1SIDH = 0x00;
    RXM1SIDL = 0x00;
 
    /**
    Initialize Receive Filters
    */   
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x00;
    RXF0SIDL = 0x00;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x00;
    RXF1SIDL = 0x00;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x00;
    RXF2SIDL = 0x00;
    RXF3EIDH = 0x00;
    RXF3EIDL = 0x00;
    RXF3SIDH = 0x00;
    RXF3SIDL = 0x00;
    RXF4EIDH = 0x00;
    RXF4EIDL = 0x00;
    RXF4SIDH = 0x00;
    RXF4SIDL = 0x00;
    RXF5EIDH = 0x00;
    RXF5EIDL = 0x00;
    RXF5SIDH = 0x00;
    RXF5SIDL = 0x00;

    /**
    Initialize CAN Timings
    */
    
  	/**
        Baud rate: 100kbps
        System frequency: 64000000
        ECAN clock frequency: 64000000
        Time quanta: 8
        Sample point: 1-1-4-2
        Sample point: 75%
	*/ 
    
    BRGCON1 = 0x27;
    BRGCON2 = 0x98;
    BRGCON3 = 0x81;
    
    ECAN_SetRXB0InterruptHandler(RXB0InterruptHandler);
    PIR5bits.RXB0IF = 0;
    PIE5bits.RXB0IE = 1;
    
    CANCON = 0x60; //Request listen only mode
    while (0x60 != (CANSTAT & 0xE0)); // wait until ECAN is in Normal mode    
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    ECAN_Initialize_user();
    //UART1_Initialize_user();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    while (1)
    {
        // Add your application code
        //IO_RB4_Toggle();
        __delay_ms(50);
        while(!UART1_is_tx_ready()) {}
        //UART1_Write('A');
        while(buf_length>0)
        {
            while(!UART1_is_tx_ready());
            UART1_Write(circular_buffer[bot_pointer]);
            buf_length--;  
            bot_pointer = (bot_pointer<SERIAL_BUF_LEN) ? bot_pointer+1 : 0;
        }
    }
}
/**
 End of File
*/