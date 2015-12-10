#ESP8266 I2S 32bit Realtime Shift Register Driver 

I believe I found a way to use just an ESP8266 module to control the stepper drivers directly. This code demonstrates how.

Background:
1 - Other projects show how to use ESP01 as a wifi-serial bridge to the arduinos, but serial is still a bottleneck and wifi uploads are impractical.
2 - Altough ESP8266 does 160MHz at 32bits processing (versus 16MHZ 8-bit from most Arduinos) it has insufficient realtime GPIO for controlling printers.
3 - Raspberry pi shared the realtime gpio limitation, but wallacoloo still did reprap control using DMA. Nice! [www.youtube.com]
4 - CNLohr did a really cool WS2812 led driver (weird one-wire serial protocol) using ESP8266 I2S audio output and DMA. [www.youtube.com]
5 - I2S and SPI look very much alike, and SPI can control shift registers. Hey! Opportunity!

I got the code from CNLohr on github, modified it to output a 32 bit counter (16 bit left + 16 bit right channels) via a circular DMA buffer, and created a small PCB with four cascaded 74HC595 shift registers. wiring is simple:
- I2S Data to '595 input data
- I2S Bitclock to '595 shift clock
- I2s word clock (left/right) to '595 buffer clock.

This is what my I2S signals look like: 

This is what word-clock and the 3LSBs look like:

The code and the PCB: [github.com]
What this does:
- Allows realtime bitbanging of 32 data bits via I2S and DMA.
- Demo code just outputs a 32bit counter at 185kHz sample rate.
- Reference shifter board is provided.

Limitations:
- 1MSB is actually delayed by 1 sample due to I2S signaling standard. This delay is constant so it could be compensated, but I didn't bother.

Hopes for the future: RepRap 3D Printing.
- No extra arduino necessary, ESP would control the drivers directly.
- SDcard uploads over wifi would be feasible for large files, no more serial connection bottleneck with wifi-serial bridging. 