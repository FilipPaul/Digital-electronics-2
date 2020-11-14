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

<h2> UART</h2>

## Lab assignment
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab7/pictures/simulation.PNG"> 

1. Preparation tasks (done before the lab at home). Submit:
   * Table with voltage divider, calculated, and measured ADC values for all buttons.

2. ADC. Submit:
   * Listing of `ADC_vect` interrupt routine with complete code for sending data to the LCD/UART and identification of the pressed button.
   * Screenshot of SimulIDE circuit when "Power Circuit" is applied.

3. UART. Submit:
   * (Hand-drawn) picture of UART signal when transmitting data `DE2` in 4800 7O2 mode (7 data bits, odd parity, 2 stop bits, 4800&nbsp;Bd),
   * Listing of code for calculating/displaying parity bit.

