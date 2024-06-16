Description:

Weaver is a Wordle-inspired game, in which the goal is to try to find a way to get from the
starting word to the ending word. You can change only one letter at a time, and each word along
the way must be a valid word. 
Play online at https://weavergame.net/ 

The following C program allows users to play this game with words of various lengths, not just 
4-letter words.

Running the Program:

The program begins by displaying a message to introduce the game. It then asks the user to
enter the number of letters that they would like the words in the game to have. All the possible
words can be found in the words.txt file. Then, there should be output to indicate the number of 
words of that length which were found in the file.

At this point, the user may choose to enter the starting or ending words, or type ‘r’ to select a
random word from the words available.
If the user tries to select a word, the program validates that the word is the correct length and 
that it is in the dictionary, i.e. the words available from the file. Until these conditions are 
met, the user must try again.
The user may also choose to have a random word for either the starting or ending word, or both. 

Once the user has been presented with the starting and ending words, they can play the game!
They will be prompted to enter their next word, and continue until they have successfully 
transitioned to the ending word or until they type ‘q’ to quit. 

In either case, once the user is done guessing, the program presents the following three menu
options:
If the user selects 1, they are asked again to enter starting and ending words or have them
selected at random, and they can play again.
If the user selects 2, they are asked again how many letters they would like to have in the words
used in the game, and then to enter the starting and ending words.
If the user selects 3, the program stops executing.