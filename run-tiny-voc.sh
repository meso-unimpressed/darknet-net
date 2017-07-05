#! /bin/sh
cd /home/nvidia/darknet-osc/
./darknet detector demo cfg/voc.data cfg/tiny-yolo-voc.cfg tiny-yolo-voc.weights -c 1

