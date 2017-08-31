#darknet-net#

**Extra CLI flags:**

use websocket or OSC protocol
`-protocol osc|ws` (default: ws)

IP or URL for your OSC/WS server
`-address <string>` (default: ws)

optional server port
`-port <int>`

whether to enable video file(streaming) output
`-videoOut 1|0` (default: 0)

filepath for video output
`-videoOutPath <string>` (default: ./output.avi)

whether the videoOutPath will be created as a [named pipe](http://www.linuxjournal.com/article/2156)
`-pipe 1|0` (default: 0)

whether to enable drawing video and detections in a window. Be aware that his eats up some fps.
`-showWindow 1|0` (default: 0)

**Note:**
When using a named pipe, the process will get blocked until another application is connecting to the named pipe in read mode.
After the file got created you can connect to the pipe with f.e. ffmpeg by `ffmpeg -i <path to pipe filename> output.mp4`
Or open it in a video player like VLC.


**How to compile:**

Install libwsclient
```
git clone https://github.com/payden/libwsclient
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
wget https://github.com/radarsat1/liblo/releases/download/0.29/liblo-0.29.tar.gz
tar xvfz liblo-0.29.tar.gz
cd liblo-0.29
./configure && make && sudo make install
```

You will need to download the weight files you want to use and install all dependencies needed by darknet.
Follow this guide: https://pjreddie.com/darknet/install/
For weight files: https://pjreddie.com/darknet/yolo/

Compile darknet
```
make
```

see `start-darknet` for an example command line