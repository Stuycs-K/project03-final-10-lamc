# Final Project Proposal

## Group Members:

Chris Lam

# Intentions:

My goal is to create a prisoner's dilemma game where two players can communicate with one another. Each player is shown a sum of money and will be asked to split or steal. If both players steal they both get nothing, if one player steals they will get the entire sum of money, and if both players split they will each receive half of the money.    

# Intended usage:

When a player joins a server, they will be waiting to be paired with another player. Once paired, they will be shown the randomly generated sum of money and each given ten seconds to freely chat with each other. Once time is up, each player will be prompted to steal or split the money.

# Technical Details:

Memory allocation will be used.

File manipulation may or may not be used depending if I have time to create a login system which saves the total amount of money earned.

Processes will be used to fork off servers for each game between two players.

Shared memory & Pipes will be used to display the same information to two players, as well as maintaining servers.

Semaphores will be used to ensure connection between two players and block more than two people from joining.

# Intended pacing:

Jan 6: Create makefile, copy over everything from previous lab  
Jan 7-9: Make game work  
Jan 9-13: Make connection work with game  
Jan 13: Project should be working at this point  
Jan 14-19: Make improvements if I possible, implement login system, keep record of wins and currency, etc.  
Jan 20: Make video presentation  
