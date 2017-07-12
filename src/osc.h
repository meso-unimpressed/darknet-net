#ifndef OSC_H
#define OSC_H

#include "lo/lo.h"
#include "image.h"
#include "utils.h"
#include "blas.h"
#include "cuda.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

lo_address osc_address;
void osc_setup(char* ip, char* port);
void osc_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes);

#endif