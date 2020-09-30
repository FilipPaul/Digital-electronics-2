<h1> lab1 </h1>
<h2> Preparation TASK </h2>

<h3> LEDs in common wiring</h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab2/pictures/LEDs.PNG">
<br>
<h3> Pushbuttons in common wiring</h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab2/pictures/Pbtns.PNG">
<br>

<h3> computation of current limiting resistors </h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab2/pictures/Equat.gif">

| **LED color** | **Supply voltage** | **LED current** | **LED voltage** | **Resistor value** |
| :-: | :-: | :-: | :-: | :-: |
| red | 5&nbsp;V | 20&nbsp;mA | 1,7&nbsp;V | 660&nbsp;&Omega; |
| blue | 5&nbsp;V | 20&nbsp;mA | 3&nbsp;V| 100&nbsp;&Omega; |

<h2> Lab results </h2>

| **DDRB** | **Description** |
| :-: | :-- |
| 0 | Input pin |
| 1 | Output pin |

| **PORTB** | **Description** |
| :-: | :-- |
| 0 | Output low value |
| 1 | Output HIGH value|

| **DDRB** | **PORTB** | **PUD (in MCUCR)**| **Direction** | **Internal pull-up resistor** | **Description** |
| :-:| :-: | :-: | :-: | :-: | :-- |
| 0 | 0 |X| input | no | Tri-state, high-impedance |
| 0 | 1 |0| input | yes | PBx will source current if ext.pulled low.|
| 0 | 1 |1| input | no | Tri-state, high-impedance |
| 1 | 0 |X| output | no | Output low (sink) |
| 1 | 1 |1| output | no | Output high (source) |
 
 <h3> Arduiono UNO Schematics </h3>
 <img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab2/pictures/Arduino_PINOUT.jpg">



| **Port** | **Pin** | **Input/output usage?** |
| :-: | :-: | :-- |
| A | x | Microcontroller ATmega328P does not contain port A |
| B | 0 | Yes (Arduino pin 8,CLKO,ICP1)|
|   | 1 | Yes (Arduino pin 9,PWM) |
|   | 2 | Yes (Arduino pin 10,SS,PWM) |
|   | 3 | Yes (Arduino pin 11,MOSI,PWM) |
|   | 4 | Yes (Arduino pin 12,MISO) |
|   | 5 | Yes (Arduino pin 13, internal LED, SCK) |
|   | 6 | Yes (Arduino pin OSC1,XTAL1,) |
|   | 7 | Yes (Arduino pin OSC2,XTAL2,) |
| C | 0 | Yes (Arduino pin A0(14)) |
|   | 1 | Yes (Arduino pin A1(15)) |
|   | 2 | Yes (Arduino pin A2(16)) |
|   | 3 | Yes (Arduino pin A3(17)) |
|   | 4 | Yes (Arduino pin A4(18)),SDA |
|   | 5 | Yes (Arduino pin A5(19)),SCL |
|   | 6 | Yes (Arduino pin RST)  |
|   | 7 | Input only (Arduino pin Undefined ) |
| D | 0 | Yes (Arduino pin RXD<-0) |
|   | 1 | Yes (Arduino pin TXD(1) |
|   | 2 | Yes (Arduino pin 2) |
|   | 3 | Yes (Arduino pin 3,PWM) |
|   | 4 | Yes (Arduino pin 4) |
|   | 5 | Yes (Arduino pin 5, PWM) |
|   | 6 | Yes (Arduino pin 6. PWM) |
|   | 7 | Yes (Arduino pin 7, PWM) |
