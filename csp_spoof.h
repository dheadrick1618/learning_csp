/*
Written by Devin Headrick

This module contains things needed to 'spoof' a CSP packet.

Instead of using CSP when there is only one device being used that requires it,
rather than using the entire libcsp library and setting up everything it requires, we
are going to create an outgoing packet in the same structure as CSP and read responses
that are in CSP packet format and parse them accordingly.

*/

#ifndef CSP_SPOOF_H
#define CSP_SPOOF_H
#endif

#include <stdint.h>

#define CSP_PADDING_BYTES 8
#define BASE_PACKET_LEN 10

// THE FOLLOWING STRUCTS WERE COPIED FROM THE LIBCSP SOURCE CODE
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

/// @brief Print the contents of the header struct portion of a mock CSP packet
/// @param id 
void print_csp_id(const csp_id_t *id);

/// @brief Print the contents of a mock CSP packet
/// @param packet 
void print_csp_packet(csp_packet_t *packet);

/// @brief  Mock function to simulate getting a packet from a buffer. This is called when creating a packet
/// @return
csp_packet_t *csp_buffer_get();

/// @brief  Write values to required csp header fields for a ESP PING command
/// @return
csp_packet_t *build_ping_packet();
