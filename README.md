![Darknet Logo](http://pjreddie.com/media/files/darknet-black-small.png)

#Darknet#
Darknet is an open source neural network framework written in C and CUDA. It is fast, easy to install, and supports CPU and GPU computation.

For more information see the [Darknet project website](http://pjreddie.com/darknet).

For questions or issues please use the [Google Group](https://groups.google.com/forum/#!forum/darknet).


OSC Addition by Meso
----------
This version of darknet was extended by [liblo](http://liblo.sourceforge.net/) an OSC C library to send detections out via OSC.
In addition to all the flags existing in Darknet already you have the flags -ip and -port to set the target IP address and port.
See start-darknet for an example command to launch the application. Default port is 7770. Default IP is 127.0.0.1
For more information on darknet itself see the [Darknet project website](http://pjreddie.com/darknet).

In addition to all the default darknet dependencies you need liblo installed on your system. An armv8 version of liblo is added to the repo, its intended for use with the Nvidia Jetson TX2.
It's advised to delete it if you are compiling the project on a different CPU platform.

Darknet only support OSX and Linux officially, this version won't compile on windows. You can integrate the OSC additions into a windows port of darknet.