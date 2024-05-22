# Learning CSP

The goal of this repo is to setup a simple program to 'spoof' csp packets. This will simply create a data structure the same format as a CSP packet so we can talk to our EPS, and it won't know the difference between the spoof and the use of actual libcsp.

## Sending a ping command

Firstly to communicate with our EPS using CSP ontop of CAN, we need to build a hardcoded ping command in CSP in accordance with the EPS data sheet, and then write that packet onto a CAN interface.

## Notes

- For CAN:  a DLC is a data length code, which defines the number of bytes in the data payload

## References

- Article for beginning guide to CSP
https://codeabove.dev/index.php/2023/01/14/cubesat-space-protocol-first-steps/

- v1.4 libcsp repo (source code referenced for structuring packet)
https://github.com/AlbertaSat/libcsp/blob/bd29773501dee33df3906a9eda130bb48eb24efc/src/drivers/can/can_socketcan.c
