[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# Prison

### Group Name: Clam

Member: Chris Lam

### Project Description:

This project is a two-player prisoner's dilemma chat game using sockets. Pairs of clients will be allotted time to convince the other player to split with them. When time is up, each player must decide to split or steal the prize money.
The prize will then be distributed accordingly:

  * If both players steal both will lose half of the prize
  * If both players split both will win half of the prize 
  * If one steals and the other splits, the one that steals will win all of the prize while the one that splits will get nothing


### Video Presentation
[Prison Demo](https://drive.google.com/file/d/108NsUK0HNoBHjEMCxXdxPAb9pTdmIEDw/view?usp=sharing)

### Instructions:
1. Clone repo
2. Run `make clean`
3. Run `make compile`
4. Run `make server`
5. Open two new terminals and run two instances of `make client`
