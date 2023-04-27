coding cp command using sockets:
/*the idea*/
    server:
        - will be a daemon listening in the background for the client
        - will recieve the file and the destination;
        - will read the file and write it to the destination
    client:
        - will inistiate a conection with the deamon;
        - will  send the file and the destination;