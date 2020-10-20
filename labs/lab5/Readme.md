<h1> Lab 5 </h1>
<h2> Preparation Task</h2>
<ul>
   <li>Common Cathode 7-segment display (CC SSD) - active HIGH</li> 
   <li>* Common Anode 7-segment display (CA SSD) - active LOW</li> 
 </ul>  

<p>In the following table, write the binary values of the segments for display 0 to 9 on a common anode 7-segment display.</p>

   | **Digit** | **A** | **B** | **C** | **D** | **E** | **F** | **G** | **DP** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
   | 1 | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 1 |
   | 2 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 1 |
   | 3 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 |
   | 4 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 1 |
   | 5 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 1 |
   | 6 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 |
   | 7 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 1 |
   | 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
   | 9 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |
   
   <p>Use schematic of the Multi-function shield and find out the connection of seven-segment display. What is the purpose of two shift registers 74HC595? <br>
   Shift registers are used for creating more output pins, this component alow us to create (8 output pins for each register) using only 3 wires (CLK, LATCH and Data), more registers can be connected in series where Q7' of first shift register is connected to data pin of second shift register</p>