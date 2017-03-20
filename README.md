# This is my readme file
Rasberry Pi acoustic sensor project

This project will turn a rasberry Pi 3 into an acoustic sensor

1. Configuration

1.1 Hardware configuration

A rasberry Pi 3 is recommended, if a older version of Pi is used, 
corresponding configuration might be changed.

The Pi is mounted with a USB sound card, and plugged in a microphone.

It is recommended to have Ethernet connection for your Pi

1.2 Software configuration

The USB sound card has to be set as default device. To do so, you need to
modify two files with the following contents.
...

If you are using Rasbian Jessie, you have to roll back alsa-utils to an
earlier version.
...

