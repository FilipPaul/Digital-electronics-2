<h1> Lab 5 </h1>
<h2> Preparation Task</h2>

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | LOW - WRITE to the display, HIGH READ - read from display|
   | E | PB1 | enable. This loads the data into the HD44780 on the falling edge |
   | D[3:0] | PD3 - PD0 | data pins for custom characters |
   | D[7:4] | PD7 - PD4 | Upper nibble used in 4-bit mode |

What is the ASCII table? What are the values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

ASCII table is a way how to describe characters with numbers in DEC, BIN, HEX etc. Each special charracter or letter is assigned to a number. For example 'A' is represented by: DEC 65, HEX 41 and bin 100 0001.
<br>
<h3>ASCII table </h3>

<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab6/pictures/ASCII.PNG">


<h2> Lab results</h2>
<h3> Table of functions from LCD library</h3>

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off &nbsp;<br>Display on, cursor off &nbsp;<br> Display on, cursor on &nbsp;<br>Display on, cursor on, blink char &nbsp;| `lcd_init(LCD_DISP_OFF);` |
   | `lcd_clrscr` | none| Clear display and set cursor to home position. | `lcd_clrscr();` |
   | `lcd_gotoxy` | uint8_t x, uint8_t y | set cursor's position | `lcd_gotoxy(x,y);` |
   | `lcd_putc` | char c | Display character at current cursor position. | `lcd_putc(c);` |
   | `lcd_puts` | string s | Display string without auto linefeed. | `lcd_puts(s);` |
   | `lcd_command` |uint8_t cmd	instruction to send to LCD controller | Send LCD controller instruction command. | `lcd_command(cmd)`|
   | `lcd_data` | uint8_t data | Send data byte to LCD controller. | `lcd_data(data);`|

<h3> HD44780 communication, message: DE2</h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab6/pictures/message.jpg">

## Lab assignment

1. Preparation tasks (done before the lab at home). Submit:
   * Table with LCD signals,
   * ASCII values.

2. HD44780 communication. Submit:
   * (Hand-drawn) picture of time signals between ATmega328P and LCD keypad shield (HD44780) when transmitting data `DE2`.

3. Stopwatch. Submit:
   * Listing of `TIMER2_OVF_vect` interrupt routine with complete stopwatch code (`minutes:seconds.tenths`) and square value computation,
   * Screenshot of SimulIDE circuit when "Power Circuit" is applied.

4. Progress bar. Submit:
   * Listing of `TIMER0_OVF_vect` interrupt routine with a progress bar,
   * Screenshot of SimulIDE circuit when "Power Circuit" is applied.

The deadline for submitting the task is the day before the next laboratory exercise. Use [BUT e-learning](https://moodle.vutbr.cz/) web page and submit a single PDF file.


