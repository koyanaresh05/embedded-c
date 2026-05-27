//Initialize the UART functionality in port A
void Init_UARTA(int iport, float baudrate, int iparity);
//Initialize the PORT F
void Init_PortF(void);
//provides delay of n milli secs
void delayMs(int n);
//Writes the charecter c on the terminal
void UART_Write(int iport, char c);
// Writes string s on the terminal
void putString(char * s);
// processes the string with * inplace of space and takes the arguments separate in the blink functionality
void processString(char * str);
