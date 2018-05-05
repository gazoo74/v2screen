# How to use

Hi dear user,

  Currently the SDK is not complete yet, but I can show you some demo.
  By using demo, you can display bitmap, or play doom.


## Chnage Log

#### 2018.04.17

- add driver for windows.
- add src/mirror, used to mirror part of your screen to vocore2 screen, depends on Qt to compile.
  

# Quick use for VoCore2

1. first check

If you have VoCore2, you can directly upgrade your firmware with the one in
root at demo/vocore2/demo.bin, then connect to VoCore2 by wifi, directly call "vodisp" to
check if screen works. call "vodisp bitmap /root/t1.bmp" to display bitmap on
screen. call "vodisp test" to test screen colors.

2. run doom

After first step, please copy DOOM.wad to VoCore2 /tmp/iwad. DOOM.wad can buy
from id software. Then call cp /root/xdoom /tmp/xdoom, put xdoom to memory.
OK, now we are ready to "play"! call /tmp/xdoom. I did not finish keyboard
control part, if you like, do your homework, modify src/doom/Source/vo_video.c
to make it work.


# Quick use for Linux

1. Install libusb-1.0 for your linux computer.

For Ubuntu, you can simply call "sudo apt-get install libusb-1.0"

2. Compile vodisp with libvodisp.so

PS: you might need to modify the Makefile to fit your system.

3. Call "sudo vodisp" to enable display.

Once display works, vodisp will return "Display connected".


# Quick use for Windows

1. Install both libusbK driver for windows in demo/win/driver_sleep and driver_normal

2. You can directly run demo/win/vodisp to boot up the display.

Use "vodisp bitmap demo/img/t1.bmp" to show bitmap.

Note: vodisp.exe keep only bitmap function.


# Quick use for Raspberry Pi

coming soon...

# API

Library libvodisp.so contains all api to use VoCore2 Screen. It depends on
libusb-1.0.so.

- int vodisp_connect()

Connect to the screen. It will do setting up the screen and display logo.


- int vodisp_disconnect()

Disconnect from the screen.


- int vodisp_write_frame(const char *buf)

Write data to screen. The buffer size must be FRAMESIZE(1152000), and pixel is
24bits, order is RGBRGBRGB... Screen is 480 x 800.


Note1: API is not complete, next version we plan to add api control backlight,
control screen rotate.

Note2: For more API usage, please check vodisp source code.
