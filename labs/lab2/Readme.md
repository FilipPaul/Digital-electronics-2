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
<br>
| **DDRB** | **Description** |
| :-: | :-- |
| 0 | Input pin |
| 1 | Output pin |

| **PORTB** | **Description** |
| :-: | :-- |
| 0 | Output low value |
| 1 | Output HIGH value|

| **DDRB** | **PORTB** | **Direction** | **Internal pull-up resistor** | **Description** |
| :-: | :-: | :-: | :-: | :-- |
| 0 | 0 | input | no | Tri-state, high-impedance |
| 0 | 1 | | | |
| 1 | 0 | | | |
| 1 | 1 | | | |


| **Port** | **Pin** | **Input/output usage?** |
| :-: | :-: | :-- |
| A | x | Microcontroller ATmega328P does not contain port A |
| B | 0 | Yes (Arduino pin 8) |
|   | 1 |  |
|   | 2 |  |
|   | 3 |  |
|   | 4 |  |
|   | 5 |  |
|   | 6 |  |
|   | 7 |  |
| C | 0 | Yes (Arduino pin A0) |
|   | 1 |  |
|   | 2 |  |
|   | 3 |  |
|   | 4 |  |
|   | 5 |  |
|   | 6 |  |
|   | 7 |  |
| D | 0 | Yes (Arduino pin RX<-0) |
|   | 1 |  |
|   | 2 |  |
|   | 3 |  |
|   | 4 |  |
|   | 5 |  |
|   | 6 |  |
|   | 7 |  |
