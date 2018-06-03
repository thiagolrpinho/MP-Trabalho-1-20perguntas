# Game of 20 Questions


The game consists of a series of Yes or No questions until it get on an answer. If the answer and what the user thought at the start of the game are equal, the program wins. If they differ, the game will ask the player for the right answer and which question answering yes would lead to this right answer. 
The game will get more questions and right answer after more plays.
It's possible to save a game, load an anterior game, to start a new game or to edit an already loaded one.


## How to play

First clone this repository. 

### Prerequisites

You need g++ installed which is native from ubuntu. 


### Installing

After extracting it, enter on the folder using your terminal and write 
```
make
```

### Play it
After that, write on your console:
```
./play_game
```

## Running the tests

On the folder you installed your Game of 20 Questions, write in the terminal:
To make a program to run all the tests:
```
make all_tester
```
If you want to see the tests before running it, write:
```
./all_tester --list-tests
```
Or just run it using
```
./all_tester 
```
*Warning
    The all_tester is not fully automatized because I'm new to catch library of tests and don't know how to automatize input and output on terminal tests.
    This happens only with tests_game_interface.cpp*

###Running other tests
To run other tests just go to the main folder of the project:
To test only the Binary Tree used on the game.
```
make btree_tester
```

Beside the previous tests, if you want to test too the game statements of the game:
```
make game_statement_tester
```

If you want to test too the game engine:
```
make game_engine_tester
```

### Gcov Test
If you have gcov and gcovr installed, you can generate the 
test coverture of the binary tree by typing:
```
make gcov_btree
```
And then:
```
./gcov_btree
```

You can additionally check game statements and game engine by changing *gcov_btree*
for *gcov_statement* or *gcov_engine* respectively on the previous list of instruction.
You can also just genereate for all tests by doing:
```
make gcov_tester
```
And then:
```
./gcov_tester
```

To generate a graphical representation of how much the code is covered by the tests you can type:
```
make gcovr_html
```
The output files are located insides the './test/gcov' folder.

*Warning
    The gcov_tester is not fully automatized because I'm new to catch library of tests and don't know how to automatize input and output on terminal tests.
    This happens only with tests_game_interface.cpp*

## More information
There's a folder created with doxygen that contains an interactive way to see the classes and methods used in the game.
Also there's an pdf on the main folder named:
```
metodos.pdf
```
With each method used, what it does(in portuguese) and a list of the tests used to validate each one of them.
## Built With

* [Catch](http://catch-lib.net/) - The test library used

## Author

* **Thiago Luis Rodrigues Pinho** - *Game of 20 Questions* - [Thiago Luis](https://github.com/thiagolrpinho/MP-Trabalho-1-20perguntas)



## Acknowledgments

* It was my first time developing using TTD method. I learned a lot and I am grateful for 
the experience. 
* It think this was a bit too complex for a two weeks project. 
* I wish I could have organized my code more. 
* Thanks for reading until here.
* Sorry for english and programing mistakes. Please correct me so I can improve.

