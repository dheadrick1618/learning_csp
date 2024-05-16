
## Notes

- To build projects with 'zmq' library, you must pass the compiler the '-lzmq' flag. i.e. 
  
```@bash
gcc zmq_hello_world_client.c -Wall -lzmq -o zmq_client
```