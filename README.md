# deej volume mixer take using an OLED screen and rotary encoder

<table>
  <tr>
    <td width=30%>This is my take on the deej volume mixer. I opted to produce a modified verison of YaMoef's mixer, where he used an LCD screen and rotary encoder rather than the original slider style. Mine is similar, with the main difference being the use of an OLED screen, which was an easy modification to make. </td>
    <td width=35%><img src="https://i.imgur.com/rA4qBB2.jpg" width="300" height="400" alt="volume mixer"> </td>
    <td width=35%><img src="https://i.imgur.com/h1SAT6z.jpg" width="300" height="400" alt="volume mixer 2"> </td>
  </tr>
</table>

### Link to the main deej Github repo:
https://github.com/omriharel/deej

### Link to YaMoef's take on the deej:
https://github.com/YaMoef/deej/tree/master

### Components Required
![Components](https://i.imgur.com/Il0kmBM.jpg)

I used the following components in this build:
- Rotary encoder with push button
- Arduino nano (mine was a 40p clone from AliExpress which worked fine)
- Arduino compatible OLED screen (I used 0.91 inch)
- Cabling
- (Extra) I²C EEPROM Module

I used an encoder with its own pcb module to save from having to use a breadboard or create a pcb for my components, but if you wanted to take this approach, or lacked an encoder with a module, YaMoef's guide explains how to do this using resistors and capicitors. I actually ran into some trouble with signal noise when turning my encoder, which I think may have been alliviated with the inclusion of capacitors (my module appears to only include resistors). 

You can use an I²C EEPROM Module to have a way of saving your mixer settings when your device has been restarted. This can also be achieved through the internal ROM of the Arduino board, but due to memory limiations, you are likely to run into problems with the board relatively quickly. I haven't currently bothered including a module because I'm fine with not having saved settings for this project, but YaMoef's project details how to use one of these modules if you are interested. 

### 3D Printing
![Printed Parts](https://i.imgur.com/pD0fAVj.jpg)

I designed parts for printing using AutoDesk Fusion; the STL files are provided in this repo here:
https://github.com/richmulvany/deej/tree/main/stl_files

This was my first time printing something with a functional purpose, and I admittedly didn't approach the design with any intentions of usability by anyone else, so keep in mind they would be annoying to replicate. I also used a resin printer, where I would expect most people would be using a filament one. I did run into a problem using resin, where the case is slightly warped (I'm guessing this is due to my shed containing the printer decreasing in temperature over night during the print). 

I superglued my parts together, where most people have used screws for their mixers. I just happened to have superglue rather than screws, and it seems like resin prints work well with superglue. This does mean I will have to destroy the case to retrieve the components or make modifications, however. 

### Arduino Code

I attempted to modify YaMoef's Arduino sketch, specifically the build excluding an EEPROM module, which did initially need only little change to accomodate the use of an OLED screen vs LCD. I discovered, however, that my encoder was only registering changes intermittently, or every time with the caveat of having to slightly push it in while turning. There seems to be a great deal of noise interfering with the readings, which is possibly caused by a poor connection with one of the contacts inside my encoder. I also wonder if the inclusion of capacitors in the filter circuit would have dealt with this issue, but since mine did not seem to include any, I opted to modify the code until the readings were more consistent. This has led to a much more modified version of the Arduino sketch than I had originally intented. 

https://github.com/richmulvany/deej/tree/main/Arduino/Volume_Mixer_Sketch

### Schematic

![Schematic](https://steemitimages.com/p/7ohP4GDMGPrUMp8dW6yuJTR9MKNu8P8DCXDU9qmmoBC9dmeUb3KxLK2bBfQ8UmDUP7465U1jz7wEtByULJYh6UMWPKijmRY22amS?format=match&mode=fit&width=1280)

The above schematic from a full-sized Arduino project gives the gist of the assembly of my project. I used the equivalent pins on my nano board for the connections, although I used pins 6 and 8 for my A and B encoder pins, just due to preference. Here is what everything connected up looked like: 

![Connections](https://i.imgur.com/KBjFsCO.jpg)
