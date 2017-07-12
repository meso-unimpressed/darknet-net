#include "osc.h"


void osc_setup(char* ip, char* port){
    // an address to send messages to. sometimes it is better to let the server
    // pick a port number for you by passing NULL as the last argument
    // t = lo_address_new_from_url( "osc.unix://localhost/tmp/mysocket" );
    // t = lo_address_new("127.0.0.1", "7770");
    osc_address = lo_address_new(ip, port);
}

void osc_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes)
{
    

    // you may want to construct a bundle instead of one big message
    // lo_message m = lo_bundle_new(LO_TT_IMMEDIATE);
    lo_message m = lo_message_new();

    printf("%d x %d\n", im.w, im.h);

    int i;
    for(i = 0; i < num; ++i){
        int class = max_index(probs[i], classes);
        float prob = probs[i][class];
        if(prob > thresh){

            // printf("%d %s: %.0f%%\n", i, names[class], prob*100);
            printf("%s: %.0f%%\n", names[class], prob*100);
            
            // not using color, add it to the message contructor below if you want to use it
            // int offset = class*123457 % classes;
            // float red = get_color(2,offset,classes);
            // float green = get_color(1,offset,classes);
            // float blue = get_color(0,offset,classes);
            // float rgb[3];

            // rgb[0] = red;
            // rgb[1] = green;
            // rgb[2] = blue;
            box b = boxes[i];

            int left  = (b.x-b.w/2.)*im.w;
            int right = (b.x+b.w/2.)*im.w;
            int top   = (b.y-b.h/2.)*im.h;
            int bot   = (b.y+b.h/2.)*im.h;
            // if(left < 0) left = 0;
            // if(right > im.w-1) right = im.w-1;
            // if(top < 0) top = 0;
            // if(bot > im.h-1) bot = im.h-1;

            lo_message_add 	(m, "sfiiii", names[class], prob*100, left, right, top, bot);
        }
    }
    lo_send_message(osc_address,"/darknet",m);
    lo_message_free (m);
}