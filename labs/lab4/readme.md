<h1> Lab 4 </h1>
<h2> Preparation tasks </h2>

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16us | 128us | -- |1.024ms | -- | 4.096ms | 16.384ms |
| Timer/Counter1 | 16 | 4.096ms | 32.768ms | -- | 262.144ms | -- | 1.048576s | 4.194304s |
| Timer/Counter2 | 8  | 16us | 128us | 512us | 1.024ms | 2.048ms | 4.096ms | 16.384ms |


| **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
| :-: | :-- | :-: | :-- |
| Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | <br><br><br> | <br><br><br> |
| Timer/Counter1 | Prescaler<br><br>16-bit data value<br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
| Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | <br><br><br> | <br><br><br> |



| **Program address** | **Source** | **Vector name** | **Description** |
| :-: | :-- | :-- | :-- |
| 0x0000 | RESET | -- | Reset of the system |
| 0x0002 | INT0  | `INT0_vect`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | External interrupt request number 0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|  | INT1 |  |  |
|  | PCINT0 |  |  |
|  | PCINT1 |  |  |
|  | PCINT2 |  |  |
|  | TIMER2_OVF |  |  |
|  | TIMER1_OVF |  |  |
|  | TIMER0_OVF |  |  |
|  | ADC |  |  |
|  | TWI |  |  |

