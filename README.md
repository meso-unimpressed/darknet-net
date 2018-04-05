darknet-net
===========

A fork of [darknet](https://github.com/pjreddie/darknet) that is able to send detection data out via either osc or websockets.

**Extra CLI flags:**

Use websocket or OSC protocol
sends json array when using ws, for osc it sends a message bundle to channel /darknet

`-protocol osc|ws` (default: ws)


Which format to use to describe the position of detection outline boxes.
xywh: Specifies the xy coordinates as well as widht and height. x position, y position of top left corner, w = width, h = height. All variables are floats of 0-1.
lrtb: Specifies the position of each edge. l = left, r = right, t = top, b = bottom. All variables are absolute pixel values as integers. This format is dependent on the resolution of the image/video input.

`-coord xywh|lrtb` (default: xywh)


IP or URL for your OSC/WS server

`-address <string>` (default: ws)


Optional server port

`-port <int>`


Whether to enable video file(streaming) output

`-videoOut 1|0` (default: 0)


Filepath for video output

`-videoOutPath <string>` (default: ./output.avi)


Whether the videoOutPath will be created as a [named pipe](http://www.linuxjournal.com/article/2156)

in order to work, the name pipe should have a .avi extension, eg: "/tmp/custompipe.avi"

`-pipe 1|0` (default: 0)


Whether to enable drawing video and detections in a window. Be aware that his eats up some fps.
**untested!**

`-showWindow 1|0` (default: 0)


To run the detection on a video file and not on the webcam.

`-filename <path to video file>` 


**Note:**
When using a named pipe, the process will get blocked until another application is connecting to the named pipe in read mode.
After the file got created you can connect to the pipe with f.e. ffmpeg by `ffmpeg -i <path to pipe filename> output.mp4`
Or open it in a video player like VLC.

**Example for the different coordinate formats:**
xywh:

```[ { "class": "person", "prob": 0.96257078647613525, "x": 0.4973103404045105, "y": 0.53185933828353882, "w": 0.75370079278945923, "h": 0.89959228038787842 } ]```

lrtb:

```[ { "class": "tvmonitor", "prob": 0.61706143617630005, "l": 311, "r": 400, "t": 151, "b": 261 }]```


**How to compile:**

Install libwsclient
```
git clone https://github.com/PTS93/libwsclient
cd libwsclient
./autogen.sh
./configure && make && sudo make install
```

Install liblo
```
wget https://github.com/radarsat1/liblo/releases/download/0.29/liblo-0.29.tar.gz
tar xvfz liblo-0.29.tar.gz
cd liblo-0.29
./configure && make && sudo make install
```

Install json-c
```
git clone https://github.com/json-c/json-c.git
sh autogen.sh
cd json-c
./configure && make && make check && sudo make install
```

You will need to download the weight files you want to use and install all dependencies needed by darknet.

Follow this guide for the dependencies: https://pjreddie.com/darknet/install/

For weight files: https://pjreddie.com/darknet/yolo/

For some more speed improvements its also adivsed to compile with CUDNN.
You can download the latest version including the install guide from here https://developer.nvidia.com/rdp/cudnn-download
If you don't want to use CUDNN you can set `CUDNN=1` in the `Makefile` to `CUDNN=0`

Compile darknet
```
make
```

see `start-darknet` for an example command line
