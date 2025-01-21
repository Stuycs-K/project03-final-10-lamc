# Dev Log:

This document must be updated daily by EACH group member.

## Chris Lam

### 2024-01-08 - Made makefile, trying to learn sockets, played with sockets
Makefile - 10 minutes  
Learned socket syntax and comprehending networking-ish (created basic server/client connection with sockets) - 1 hr  

### 2024-01-09 - Sockets & Select (made new branch)
Trying to fix bug where client has some garbage at the end of each handshake - 10 mins  
Even more socket syntax and fixing some previous file descriptor/socket descriptor bug - 20 mins  
Literally read select demo code and did not understand most of it - 30 mins  

### 2024-01-10 - Debugging
Identified & fixed problems with forking server and when multiple clients try to connect to main server - 30 mins  
Still cannot fix bug where client's are reading each others' garbage (probably reading/writing too many bytes but I cannot find the source) - 30 mins  

### 2024-01-11 + 12 - Total redesign of previous networking, Client + Socket selecting, server forking + selection being able to read from multiple socket descriptors
Fixed reading garbage (forgot to reset buffer after each iteration) - 20 mins  
Created 2 x 100 socket descriptor array to fill with new clients, added client sockets to read_fps for select preperations - 1 hour  
Cleaned up socket code on the server side, implemenetd forking server when both indicies are filled and reading clients stdin - 1 hour  
Basically just copied all of selects syntax and played around with it until it worked on server side - 2 hours  
Above but for client - 30 mins  
Implemented setsockopt() to fix "bind failed: Address already in use" - 5 mins  
Fixed bug where server stalls on resetting read_fps - 30 mins  
Fixed bug where clients would incorrectly display what they wrote to each other (I didn't fflush) - 15 mins  

### 2024-01-13 - Logistics
Added DEVLOG to main branch - 1 min  
Made client to client communication easier by prompting each user and displaying information correctly - 1 hour  
Made while loop timer and cleaned up gamble.c - 30 mins  

### 2024-01-14 - Logistics part 2 + Made Timer
Found bug where timer doesn't work and tried to fix - 25 mins  
Found bug where if clients connceted to server and left, and then tried connecting again the sockets would break - 15 mins  
Fixed timer by replacing fgets() with read - 20 mins  
Fixed networking by resetting the array of socket descriptors after every iteration - 15 mins  
Implemented timer into clients - 30 mins  

### 2024-01-15 - Debugging + Combined chris and socket branches
Found bug where clients read the prize amount as user input and fixed it - 30 mins 
Imported gamble.c from chris branch into socket branch and shrinked prize size - 30 mins  
Turned inital handshake into prize extrpolation from servers - 15 mins  

### 2024-01-16 - Wrote up Final Decision Component  
Turned socket.c to server.c to setup a timer in server, updated makefile to account for difference - 30 mins  
Set up timer and get specific input from user for final decision - 30 mins  
Made a stopping system after 10 seconds and each client only reads one input afterwards (for now it is limited to steal or split) - 30 mins  
Allowed clients to display in unison what the other client typed - 10 mins  
Fixed bug where displayed messages would be read on the other clients - 15 mins  

### 2024-01-17 - Tried to fix bug but realized bug was intended feature
My original design was a 2D array holding all socket descriptors but my code kept clearing the array so I tried to debug  
(This was silly because then if a client connected onto the server when a game has already started, they would be waiting for longer  
if the previous game had ended because then a new client would take the place of the previous game's spot in the array)  
TLDR: unintentionally made it better and it only took 1.5 hours to realize  
Got user input for steal/split and almost completely working (Bug where split/steal doesn't work (will fix tmr)) - 40 mins  

### 2024-01-18 - Finished final decision, put finishing touches
Finish final decision handling - 1.5 hours  
Made server assign each client anumber to output in the final decision - 1 hour  
Fixed a bunch of bugs (Null terminated strings, clients did not stop reading after time was finished, etc) - 2 hours  

### 2024-01-19 - Accounts
Attempted to make username + password system - 2 hours  
Gave up on the passwords and just made it work with using usernames to login - 30 minutes  
Unsuccessfully tried to synchronize usernames with money - 4 hours  

### 2024-01-20 - Accounts + Money works + Made video
Made accounts link up to money (survives through multiple clients) + cleaned up files - 2 hours  
Updated README - 15 mins  
Created video presentation - 30 mins  