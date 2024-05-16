// Written by Devin Headrick

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdint.h>

#ifndef CSP_PACKET_PADDING_BYTES
#define CSP_PADDING_BYTES 8
#endif

#define BASE_PACKET_LEN 10

/**
   CSP identifier/header.
   The __packed attribute ensures that the compiler does not add any padding between the fields of the structure.
*/
typedef struct __packed
{
    uint8_t pri;
    uint8_t flags;
    uint16_t src;
    uint16_t dst;
    uint8_t dport;
    uint8_t sport;
} csp_id_t;

/**
   CSP Packet.

   This structure is constructed to fit with all interface and protocols to prevent the
   need to copy data (zero copy).

   @note In most cases a CSP packet cannot be reused in case of send failure, because the
   lower layers may add additional data causing increased length (e.g. CRC32), convert
   the CSP id to different endian (e.g. I2C), etc.
*/
typedef struct
{
    /**
           Padding. These bytes are intended for use by protocols, which want to prepend
           data before sending it, without having to copy/reorganize the entire message.
        */
    uint8_t padding[CSP_PADDING_BYTES];
    /** Data length. Must be just before CSP ID.*/
    uint16_t length;
    /** CSP id. Must be just before data, as it allows the interface to id and data
            in a single operation. */
    csp_id_t id;
    /**
           Data part of packet.
           When using the csp_buffer API, the size of the data part is set by
           csp_buffer_init(), and can later be accessed by csp_buffer_data_size()
        */
    union
    {
        /** Access data as uint8_t. */
        uint8_t data[0];
        /** Access data as uint16_t */
        uint16_t data16[0];
        /** Access data as uint32_t */
        uint32_t data32[0];
    };
} csp_packet_t;

// Mock function to simulate getting a packet from a buffer
csp_packet_t *csp_buffer_get()
{
    size_t packet_size = sizeof(csp_packet_t) + BASE_PACKET_LEN;
    csp_packet_t *packet = (csp_packet_t *)malloc(packet_size);
    if (packet != NULL)
    {
        memset(packet, 0, packet_size); // Initialize all fields to zero
    }
    return packet;
}

csp_packet_t *build_ping_packet()
{
    csp_packet_t *packet;
    packet = csp_buffer_get();
    size_t len = BASE_PACKET_LEN;
    packet->length = len;

    csp_id_t id = {
        .pri = 2, 
        .src = 16,
        .dst = 4,
        .dport = 1,
        .sport = 52,
    };

    packet->id = id;

    //int i;
    // for (i = 0; i < len; i++){
    //     packet->data[i] = i;
    // }

    //strcpy((char *)packet->data, "TEST");

    return packet;
}

void print_csp_id(const csp_id_t *id) {
    printf("CSP ID Attributes:\n");
    printf("Priority: %u\n", id->pri);
    printf("Flags: 0x%02X\n", id->flags);
    printf("Source Address: %u\n", id->src);
    printf("Destination Address: %u\n", id->dst);
    printf("Destination Port: %u\n", id->dport);
    printf("Source Port: %u\n", id->sport);
}

void print_packet(csp_packet_t *packet)
{
    int i;

    // Print the general attributes
    printf("Packet Length: %u\n", packet->length);
    //printf("CSP ID: %u\n", packet->id);
    print_csp_id(&packet->id);

    // Print the data
    printf("Packet Data: ");
    for (i = 0; i < packet->length; i++)
    {
        printf("%02X ", packet->data[i]);
    }
    printf("\n");
}

int main(int *argc, int *argv[])
{
    // REMEMBER: Cant use uninitialized pointers - or get segfault
    csp_packet_t *packet;

    packet = build_ping_packet();

    print_packet(packet);

    free(packet);

    return 0;
}