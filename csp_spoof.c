
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "csp_spoof.h"

struct csp_packet_t;

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
    // PING DOES NOT INCLUDE DATA
    return packet;
}

void print_csp_id(const csp_id_t *id)
{
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
    // printf("CSP ID: %u\n", packet->id);
    print_csp_id(&packet->id);

    // Print the data
    printf("Packet Data: ");
    for (i = 0; i < packet->length; i++)
    {
        printf("%02X ", packet->data[i]);
    }
    printf("\n");
}