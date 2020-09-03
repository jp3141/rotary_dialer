# rotary_dialer
Use old telephone rotary dial as a USB numeric keypad; includes 3-D printer files. [video at YouTube](https://www.youtube.com/watch?v=j2RmRgkIrfg)

Use an old AT&T Trimline rotary dialer as a numeric keypad for your computer. Disassemble the phone handset and extract the dialer. The 3-D files include a replacement for the center plug -- so you can change the colour.

Uses a Teensy 3.x or Teensy LC to read the pulses. One pin of the teensy is set as a weak pullup (INPUT_PULLUP) and the program counts the number of (debounced) positive pulses, representing the number dialled. It then sends that as a keystroke to the computer as a USB HID keyboard. The on-board LED flashes in synch with the dialer pulses.

The program also acts as a USB serial port -- for debugging. When initialized, the LED flashes quickly for up to 10 s while the serial port initializes, or the first number is dialed. You do not need to use the serial port for the keypad to work. 

The 3-D printed enclosure prints as a single piece; the center plug is also included. There is a slot for the Teensy, and mounting holes for a Trimline dialer. Use three #4 x 1/4" sheet metal screws to attach the dialer to the enclosure. If you cannot get 1/4" screws, use longer ones and cut to size. Ther are holes in the baseplate to allow a screwdriver to reach the bottom screws. 

The baseplate also includes an inverted truncated cone (frustrum) to hold small 12 mm rubber feet securely. 
