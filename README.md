#ESP8266 I2S 32bit Realtime Shift Register Driver 

I believe I found a way to use just an ESP8266 module to control a set of 3D printer stepper drivers directly. This code demonstrates how.

Background:

1.  Other projects show how to use ESP01 as a wifi-serial bridge to the arduinos, but serial is still a bottleneck and wifi uploads are impractical.
2.  Altough ESP8266 does 160MHz at 32bits processing (versus 16MHZ 8-bit from most Arduinos) it has insufficient realtime GPIO for controlling printers.
3.  Raspberry pi shared the realtime gpio limitation, but wallacoloo still did reprap control using DMA. Nice! https://www.youtube.com/watch?v=g4UD5MRas3E
4.  CNLohr did a really cool WS2812 led driver (weird one-wire serial protocol) using ESP8266 I2S audio output and DMA. https://www.youtube.com/watch?v=6zqGwxqJQnw
5.  I2S and SPI look very much alike, and SPI can control shift registers. Hey! Opportunity!

I got the code from CNLohr on github, modified it to output a 32 bit counter (16 bit left + 16 bit right channels) via a circular DMA buffer, and created a small PCB with four cascaded 74HC595 shift registers. wiring is simple:
- I2S Data to '595 input data
- I2S Bitclock to '595 shift clock
- I2s word clock (left/right) to '595 buffer clock.

This is what RAW I2S output signals for the counter look like: word-clock (yellow), bit clock (cyan), data (purple). Notice how LSB of data is output after the word clock rising edge.

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/Fhat7x_vPLw/0.jpg)](http://www.youtube.com/watch?v=Fhat7x_vPLw)

Fixed the offset (software shifing) to match the parallel outputs, raised the frequency a bit (just cause), plugged in the shifter board. Now this is what word-clock (yellow) and the 3LSBs (cyan=1, purple=2, blue=4) look like:
![image of osciloscope](https://github.com/lhartmann/esp8266_reprap/blob/master/images/Counter%20-%20Word_clock%20and%203LSBs.png?raw=true)

The code and the PCB: (https://github.com/lhartmann/esp8266_reprap)

What this does:

- Allows realtime bitbanging of 32 data bits via I2S and DMA.
- Demo code just outputs a 32bit counter at 185kHz sample rate.
- Reference shifter board is provided.

Limitations:

- 1MSB is actually delayed by 1 sample due to I2S signaling standard. This delay is constant so it could be compensated, but I didn't bother.

Hopes for the future: RepRap 3D Printing.

- No extra arduino necessary, ESP would control the drivers directly.
- SDcard uploads over wifi would be feasible for large files, no more serial connection bottleneck with wifi-serial bridging. 
- Browser-side slicing with slic3r and (http://www.skulpt.org). No software install required on the client!
