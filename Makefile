CFLAGS = -Wall 

# Default target
all: csp_spoof_emitter csp_spoof_listener

csp_spoof_listener: csp_spoof_listener.o csp_spoof.o
	gcc $(CFLAGS) -o csp_spoof_listener csp_spoof_listener.o csp_spoof.o

# build object files from source files
csp_spoof_listener.o: csp_spoof_listener.c csp_spoof.h
	gcc $(CFLAGS) -c csp_spoof_listener.c

# build the target executable
csp_spoof_emitter: csp_spoof_emitter.o csp_spoof.o
	gcc $(CFLAGS) -o csp_spoof_emitter csp_spoof_emitter.o csp_spoof.o

# build object files from source files
csp_spoof_emitter.o: csp_spoof_emitter.c csp_spoof.h
	gcc $(CFLAGS) -c csp_spoof_emitter.c

csp_spoof.o: csp_spoof.c csp_spoof.h
	gcc $(CFLAGS) -c csp_spoof.c

clean:
	rm -f csp_spoof_emitter.o csp_spoof.o csp_spoof_emitter
	rm -f csp_spoof_listener.o csp_spoof.o csp_spoof_listener

# Phony targets
.PHONY: all clean