#include <avr/io.h>
#include <util/delay.h>

//For Arduino Mega 2560 (ATMega2560)

#define LED_PIN PH4 //Pin 7 on Arduino Mega is connected to Port H, bit 4

#define F_CPU 16000000UL  //16 MHz for CPU clock speed
#define BAUD 9600 //The set BAUD rate
#define MYUBRR F_CPU/16/BAUD-1 //Calculate the USART Baud Rate Register

void USART_init(unsigned int ubrr) {
    //Set baud rate
    //UBRR0H and UBRR0L are the high and low bytes of the USART Baud Rate Register
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    //Enable receiver and transmitter
    //UCSR0B is the USART Control and Status Register B
    //RXEN0: Receiver Enable
    //TXEN0: Transmitter Enable
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    //Set frame format: 8 data bits, 1 stop bit
    //UCSR0C is the USART Control and Status Register C
    //UCSZ00 and UCSZ01: Character Size (set to 3 for 8-bit data) 
    UCSR0C = (3<<UCSZ00);
}

void USART_transmit(unsigned char data) {
    //Wait for empty transmit buffer
    //UCSR0A is the USART Control and Status Register A
    //UDRE0: USART Data Register Empty
    while (!(UCSR0A & (1<<UDRE0)));

    //Put data into buffer, sends the data
    //UDR0 is the USART I/O Data Register
    UDR0 = data;
}

void USART_print_string(char *str) {
    while (*str) {
        USART_transmit(*str);
        str++;
    }
}

int main(void) {
    //Set pin 7 (PH4) as output
    //DDRH is the Data Direction Register for Port H
    DDRH |= (1 << LED_PIN);
   
    USART_init(MYUBRR);  //Initialize USART

    while(1) {
        //Turn LED on and off
        //PORTH is the Port H Data Register
        PORTH ^= (1 << LED_PIN);
        _delay_ms(1000);  //Wait for 1 second
       
        //Serial print
        USART_print_string("Hello, World!\r\n"); 
    }
    
    return 0;
}

