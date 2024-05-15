# Learning CSP

For now I will implement a dummy CSP program using C - which takes non-CSP arguments (in the future from the OBC), and formats them into CSP, and vice versa. 


## Notes

- To build projects with 'zmq' library, you must pass the compiler the '-lzmq' flag. i.e. 
  
```@bash
gcc zmq_hello_world_client.c -Wall -lzmq -o zmq_client
```


### References:

- Article for beginning guide to CSP 
https://codeabove.dev/index.php/2023/01/14/cubesat-space-protocol-first-steps/
