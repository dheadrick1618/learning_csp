/*
written by devin headrick

this program periodically writes a csp packet to a can interface. 

initially developed to emit a ping packet in accordance with our eps csp struct requirement

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "csp_spoof.h"

int main(int argc, char **argv){

    //Create a CSP ping packet
    csp_packet_t *packet;

    packet = build_ping_packet();
    
    print_csp_packet(packet);
    
    //write the packet to the vcan interface
    int s; 
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "vcan0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	frame.can_id = 0x555;
	frame.can_dlc = 5;
	sprintf(frame.data, "AAAAA");

	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}


    free(packet);

    return 0;
}