#include "communication.h"
#include <json.h>

int onclose(wsclient *c) {
    fprintf(stderr, "ws onclose called: %d\n", c->sockfd);
    return 0;
}

int onerror(wsclient *c, wsclient_error *err) {
    fprintf(stderr, "ws onerror: (%d): %s\n", err->code, err->str);
    if(err->extra_code) {
        //errno = err->extra_code;
        perror("recv");
    }
    return 0;
}

int onmessage(wsclient *c, wsclient_message *msg) {
    fprintf(stderr, "ws onmessage: (%llu): %s\n", msg->payload_len, msg->payload);
    return 0;
}

int onopen(wsclient *c) {
    fprintf(stderr, "ws onopen called: %d\n", c->sockfd);
    // libwsclient_send(c, "Hello on-open");
    return 0;
}

void comm_setup(char* address, char* port, char* protocol){
    comm_protocol = protocol;
    printf("using comm protocol %s\n", protocol);
    printf("address:%s, port:%s \n",address,port);
    if(strcmp(protocol,"osc") == 0){
        printf("setting up osc\n");
        if(strcmp(port,"") == 0){
            port = "7770";
            printf("defaulting to port 7770\n");
        }
        osc_address = lo_address_new(address, port);
    }else if(strcmp(protocol,"ws") == 0){
        printf("setting up ws\n");
        if(strcmp(port,"") == 0){
            ws_client = libwsclient_new(address);
        }else{
            char buf[256];
            snprintf(buf, sizeof buf, "%s%s%s", address, ":", port);
            ws_client = libwsclient_new(buf);
        }

        if(!ws_client) {
            fprintf(stderr, "Unable to initialize new WS client.\n");
            exit(1);
        }
        //set callback functions for this client
        libwsclient_onopen(ws_client, &onopen);
        libwsclient_onmessage(ws_client, &onmessage);
        libwsclient_onerror(ws_client, &onerror);
        libwsclient_onclose(ws_client, &onclose);
        //bind helper UNIX socket to "test.sock"
        //One can then use netcat (nc) to send data to the websocket server end on behalf of the client, like so:
        // $> echo -n "some data that will be echoed by echo.websocket.org" | nc -U test.sock
        libwsclient_helper_socket(ws_client, "test.sock");
        //starts run thread.
        libwsclient_run(ws_client);

        //blocks until run thread for client is done.
        // libwsclient_finish(client);
    }
    // an address to send messages to. sometimes it is better to let the server
    // pick a port number for you by passing NULL as the last argument
    // t = lo_address_new_from_url( "osc.unix://localhost/tmp/mysocket" );
    // t = lo_address_new("127.0.0.1", "7770");
    printf("comm setup done\n");

}

void osc_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes)
{


    // you may want to construct a bundle instead of one big message
    // lo_message m = lo_bundle_new(LO_TT_IMMEDIATE);
        lo_message m = lo_message_new();

        printf("%d x %d\n", im.w, im.h);
        // libwsclient_send(ws_client, "Hello darknet");
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
                if(left < 0) left = 0;
                if(right > im.w-1) right = im.w-1;
                if(top < 0) top = 0;
                if(bot > im.h-1) bot = im.h-1;

                lo_message_add 	(m, "sfiiii", names[class], prob, left, right, top, bot);
            }
        }
        lo_send_message(osc_address,"/darknet",m);
        lo_message_free (m);
}


void ws_send_detections(image im, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes)
{

        printf("%d x %d\n", im.w, im.h);
        json_object *jarray = json_object_new_array();
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
                if(left < 0) left = 0;
                if(right > im.w-1) right = im.w-1;
                if(top < 0) top = 0;
                if(bot > im.h-1) bot = im.h-1;

                json_object * jobj = json_object_new_object();

                json_object *jclass = json_object_new_string(names[class]);
                json_object_object_add(jobj,"class", jclass);

                json_object *jprob = json_object_new_double(prob);
                json_object_object_add(jobj,"prob", jprob);
                if(strcmp(coordFormat,"xywh") == 0){
                    json_object_object_add(jobj,"x", json_object_new_double(b.x));
                    json_object_object_add(jobj,"y", json_object_new_double(b.y));
                    json_object_object_add(jobj,"w", json_object_new_double(b.w));
                    json_object_object_add(jobj,"h", json_object_new_double(b.h));
                }else if(strcmp(coordFormat,"lrtb") == 0){
                    json_object_object_add(jobj,"l", json_object_new_int(left));
                    json_object_object_add(jobj,"r", json_object_new_int(right));
                    json_object_object_add(jobj,"t", json_object_new_int(top));
                    json_object_object_add(jobj,"b", json_object_new_int(bot));
                }

                json_object_array_add(jarray,jobj);


            }
        }
    libwsclient_send(ws_client, json_object_to_json_string(jarray));
}
