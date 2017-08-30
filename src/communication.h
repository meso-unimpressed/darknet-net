#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include "image.h"
#include "utils.h"
#include "blas.h"
#include "cuda.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "lo/lo.h"
#include <wsclient/wsclient.h>

lo_address osc_address;
char* comm_protocol;
wsclient *ws_client;

void comm_setup(char* ip, char* port, char* protocol);
void osc_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes);
void ws_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes);

#endif