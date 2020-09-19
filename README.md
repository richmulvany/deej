# Deej volume controller
This is an modified version of Deej [Original Deej](https://github.com/omriharel/deej). I always wanted some simple way of changing volume of different programs instead of using the mixer of Windows so I came across the Deej project and decided to give it a try.

# Build process
 My first idea was to use an LCD (I2C), an rotary encoder and an Arduino pro micro to display the slider values on the screen in %. I wrote an simple Arduino code that maps the value from 0-100 to 0-1023 the code was working a bit but it wasn't accurate. When decreasing by 5% on the lcd, it decreased sometimes by 4 or 6 in Windows. With some help from other people in the Deej Discord we tried to map correctly (the map function doesn't round the value). When achieving this the code still didn't work. So I moved on to modifying Deej. After hours of trying to understand how Deej works, I found some interessting lines in the serial.go file. In this file is the value read from the arduino transformed into a value Windows understands. I putted off the noise reduction, changed the mapping to 0-100 and removed the "normalize" feature. Created the modified build made my setup working.

# Parts needed
- 1 rotary encoder with pushbutton preferably a module so you do not need a extra filter circuit
- 1 Arduino pro micro (any other clone or Arduino board with an usb connection will do the job)
- 1 LCD (I used an I²C 16*2. When using an normal screen you need to change the library in the arduino code. If you modify the Arduino code you could use a bigger LCD)
- (if needed) filter circuit for rotary encoder
  - 4 10kohm resistors
  - 2 10nF (=0.01µF) ceramic capacitors
