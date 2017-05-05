https://github.com/nnminh171298/APPDEV
# This is my readme file

Rasberry Pi acoustic sensor project
.
This project will turn a rasberry Pi 3 into an acoustic sensor

.

Table of Content
1. Configuration instructions
2. Installation instructions
3. Operating instructions
4. List of project files
5. Coppyright and licensing information
6. Contact information of the contributor
7. Credit and acknowledgement

1. Configuration instructions
This section contains 2 parts: hardware configuration and software configuration.

1.1. Hardware configuration
This project is built on a Raspberry Pi3, with a USB sound card and a microphone.
Ethernet connection is recommended.
If an older version of Raspberry Pi is used, certain changes might be necessary.

1.2. Software configuration
First you have to set the USB sound card as the default audio device.
To do so, you have to put following content to two files:
	a) Use “lsusb” command to check if your USB sound card is mounted
	b) Use "sudo nano /etc/asound.conf" command and put the following content:
		pcm.!default {
			type plug
			slave {
				pcm "hw:1,0"
			}
		}
 		ctl.!default {
 		    type hw
 		    card 1
 		}
	c) Go to your home directory. Use “nano .asoundrc” command and put the same content to the file.
	d) Run “alsamixer” you should be able to see that USB sound card is the default audio device
Second, you have to downgrade alsa-util from version 1.0.28 to version 1.0.25 due a bug while recording of a newer version.
	a) Use “sudo nano /etc/apt/sources.list” command and add the last line:
		deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi
		# Uncomment line below then 'apt-get update' to enable 'apt-get source'
		#deb-src http://archive.raspbian.org/raspbian/ jessie main contrib non-free rpi
		deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
	b) Run “sudo apt-get update”
	c) Run “sudo aptitude versions alsa-utils” to check if version 1.0.25 of alsa-util is available:
	d) Run “sudo apt-get install alsa-utils=1.0.25-4” to downgrade
	e) Reboot

2. Installation Instructions
Clone the project named APPDEV from my Github profile.
Open the terminal and change the directory to the source code folder. Also change your character set to UTF-8.
Use command "make" to compile and link all the source code.

3. Operation instructions
After the installation, simply execute "./wave.a" in the project folder.

4. List of project files
The project contains following files:
--README.md:	this file.
--makefile:	the makefile of this project.
--wave.c:	the module containing functions about wave processing.
--wave.h:	the header of wave.c.
--screen.c:	the module containing functions about screen manipulation.
--screen.h:	the header of screen.c.
--comm.c:	the communication module using libcurl.
--comm.h:	the header file of comm.c.
--main.c:	contains main() function.
--sound.php:	the server page to receive data.
--display.php:	the server page visualizes data.

5. Coppyright and licensing information
This is a open source project. No coppyright or licensing.

6. Contact information of the contributor
Name: Nguyen Ngoc Minh.
Phone: +358 417 493 701.
Email: ngocminh1712989@gmail.com.

7. Credit and acknowledgement
This project is made by following the instruction of Doctor Gao Chao, VAMK.