<h1> Lab 7 </h1>
<h2> Preparation Task</h2>

<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab7/pictures/Equat.PNG">

When none of pushbutton is pressed the voltage is 5V


   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0   | 0 |
   | Up     | 0.495&nbsp;V | 101 | 101 |
   | Down   | 1.203&nbsp;V | 246 | 245 |
   | Left   | 1.970&nbsp;V | 403 | 402 |
   | Select | 3.182&nbsp;V | 651 | 650 |
   | none   | 5&nbsp;V | 1023 | 1022 |

<h2> ADC</h2>

   | **Operation** | **Register(s)** | **Bit(s)** | **Description** |
   | :-: | :-- | :-- | :-- |
   | Voltage reference | ADMUX | REFS1:0 | 01: AVcc voltage reference, 5V |
   | Input channel | ADMUX | MUX3:0 | see fig. bellow |
   | ADC enable | ADCSRA | 7-ADEN | if 1: enable |
   | Start conversion | ADSCRA | 6-ADSC |  write this bit to one to start each conversion. In free running mode, write this bit to one to start the first conversion |
   | ADC interrupt enable | ADCSRA | 3-ADIE | When this bit is written to one and the I-bit in SREG is set, the ADC conversion complete interrupt is activated. |
   | ADC clock prescaler | ADCSRA | ADPS2:0 | see fig. bellow |
   | ADC result | ADCL and ADCH (depends on ADLAR) | ADC9:0 | result |

  <img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab7/pictures/MUX.PNG">
  <br>
  <img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab7/pictures/Prescaler.PNG"> 


<h2> UART</h2>

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd | `uart_init(UART_BAUD_SELECT(9600, F_CPU));` |
   | `uart_getc` | - | Returns in the lower byte the received character and in the higher byte the last receive error. UART_NO_DATA is returned when no data is available |`uart_getc()` |
   | `uart_putc` | unsigned char data | data	byte to be transmitted | `uart_putc(unsigned char data)` |
   | `uart_puts` | const char* s | s string to be transmitted | `uart_puts(const char* s)`|

Extend the application from the previous point and send information about the results of the analog to digital conversion to the UART transmitter. Use internal UART module in 9600 8N1 mode.


### Version: SimulIDE

In SimulIDE, right click to ATmega328 package and select **Open Serial Monitor**. In this window you can receive data from the microcontroller, but also send them back.

![SimulIDE](Images/screenshot_simulide_lcd_uart.png)


### Version: Real hardware

Use PuTTY SSH Client to receive values from Arduino board. Set connection type to **Serial** and check that the configuration is the same as in the ATmega328 application. Note that, serial line to connect to (here COM3 on Windows) could be different. In Linux, use `dmesg` command to verify your port (such as `/dev/ttyUSB0`).

![PuTTY](Images/screenshot_putty_type.png)
![PuTTY](Images/screenshot_putty_config.png)

> WARNING: Before Arduino board re-programming process, PuTTY SSH Client must be closed!
>


## Synchronize repositories

Use [git commands](https://github.com/tomas-fryza/Digital-electronics-2/wiki/Git-useful-commands) to add, commit, and push all local changes to your remote repository. Check the repository at GitHub web page for changes.


## Experiments on your own

1. Based on the converted values, write the part of the code that distinguishes which push button was pressed and display the information at LCD position `c` and send it to UART. Try to recalculate the input voltage values in mV. Hint: Use integer data types only; the absolute accuracy of the calculation is not important here.

   > Note: If you need to transmit a larger amount of data, it is necessary to increase the size of the transmit/receive buffer in the `uart.h` file, eg to 64.
   >
```c
/** @brief  Size of the circular receive buffer, must be power of 2
 *
 *  You may need to adapt this constant to your target and your application by adding
 *  CDEFS += -DUART_RX_BUFFER_SIZE=nn to your Makefile.
 */
#ifndef UART_RX_BUFFER_SIZE
# define UART_RX_BUFFER_SIZE 64
#endif

/** @brief  Size of the circular transmit buffer, must be power of 2
 *
 *  You may need to adapt this constant to your target and your application by adding
 *  CDEFS += -DUART_TX_BUFFER_SIZE=nn to your Makefile.
 */
#ifndef UART_TX_BUFFER_SIZE
# define UART_TX_BUFFER_SIZE 64
#endif
```

![SimulIDE](Images/screenshot_simulide_lcd_final.png)

2. Design a piece of code to calculate the parity bit from the specified value. Display the parity of ADC converted value on the LCD and UART.

Extra. Design your own library for working with analog to digital convertor.


### Version: Real hardware

3. What is the meaning of ASCII control characters `\r`, `\n`, and `\b`? What codes are defined for these characters in ASCII table?

4. Use [ANSI escape sequences](https://en.wikipedia.org/wiki/ANSI_escape_code) and modify color and format of transmitted strings according to the following code. Try other formatting styles.

   ```C
   /* Color/formatting sequence always starts by "\033[" and ends by "m" strings.
   * One or more formatting codes "#", separated by ";" can be used within
   * one line, such as:
   *    \033[#m      or
   *    \033[#;#m    or
   *    \033[#;#;#m  etc. */
   uart_puts("\033[4;32m");        // 4: underline style; 32: green foreground
   uart_puts("This is all Green and Underlined.");
   uart_puts("\033[0m");           // 0: reset all attributes
   uart_puts("This is Normal text again.");
   ```

5. Program an interactive console that communicates between ATmega328P and the computer (PuTTY application) via UART. Let the main screen of the console is as follows:

   ```bash
   --- Interactive UART console ---
   1: read current Timer/counter1 value
   2: reset Timer/counter1
   > 
   ```

   After pressing the '1' key on computer keyboard, ATmega328P receives ASCII code of the key and sends the current Timer1 value back to PuTTY. After pressing the '2' key, ATmega328P resets Timer1 value, etc. Use ANSI escape sequences to highlight information within PuTTY console.

   ```C
   uint8_t c;
   ...
    
   c = uart_getc();
   if (c != '\0') {        // Data available from UART
       if (c == '1') {     // Key '1' received
           ...
       }
   }
   ```

6. Program a software UART transmitter that will be able to generate UART data on any output pin of the ATmega328P microcontroller. Let the bit rate be approximately 9600&nbsp;Bd and do not use the delay library. Also consider the possibility of calculating the parity bit. Verify the UART communication with logic analyzer or oscilloscope.


## Lab assignment

1. Preparation tasks (done before the lab at home). Submit:
   * Table with voltage divider, calculated, and measured ADC values for all buttons.

2. ADC. Submit:
   * Listing of `ADC_vect` interrupt routine with complete code for sending data to the LCD/UART and identification of the pressed button.
   * Screenshot of SimulIDE circuit when "Power Circuit" is applied.

3. UART. Submit:
   * (Hand-drawn) picture of UART signal when transmitting data `DE2` in 4800 7O2 mode (7 data bits, odd parity, 2 stop bits, 4800&nbsp;Bd),
   * Listing of code for calculating/displaying parity bit.

The deadline for submitting the task is the day before the next laboratory exercise. Use [BUT e-learning](https://moodle.vutbr.cz/) web page and submit a single PDF file.


## References

1. [Voltage Divider Calculator](https://www.allaboutcircuits.com/tools/voltage-divider-calculator/)
2. [Introduction to Analog to Digital Converters (ADC Converters)](https://components101.com/articles/analog-to-digital-adc-converters)
3. Embedded projects from around the web. [ADC on Atmega328. Part 1](https://embedds.com/adc-on-atmega328-part-1/)
4. Circuit Basics. [Basics of UART Communication](https://www.circuitbasics.com/basics-uart-communication/)
5. [ASCII Table and Description](http://www.asciitable.com/)