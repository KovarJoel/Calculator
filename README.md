# Console Calculator in C++

### Video Demo:  <URL HERE>

## Description:

This is my final project for Harvard University's computer sience course [CS50](https://cs50.harvard.edu/x/2023/).
My goal was to make a little wrapper for [sqlite](https://www.sqlite.org/index.html) and build a fairly simple calculator in the console window on top of it.

#### My calculator supports multiple features:
* Basic arithmetic operations (+, -, *, /, ^)
* Parentheses
* Saving and retrieving variables from a database
* Saving a history of the last few calculations

### My program generally consists of these three bigger parts:
 * **SQLITE WRAPPER:** My sqlite wrapper consists of three classes: a wrapper for a `Database`, one for `Table`s (to interact with them, e.g. create, drop, select) and a third class for storing and printing the retrieved `TableData` from a executed method on the database. In addition to that there is an additional header file that lets me insert variadic arguments into a string and escape text. The goal of this wrapper was to make it easy to use and similar to the one we had in python from the cs50 module.

 * **CALCULATION:** I have a class `Number` which can be constructed with a string called `expression`. At first all variables in that `expression` get substituted with their corresponding values which are all stored in a `Table` in my `Database`. After that the `expression` gets split so that there are no parentheses left in one of those sub-expressions. If that is the case, I loop through all operators in order of their precedence and if they are in the sub-expression the corresponding function to each of those operators gets called on the value before and after that operator in the sub-expression. The part of both values and the operator in the sub-expression gets replaced with its result. This process loops until there is no operator left. At the end the string `expression` gets converted to `double` and if that fails, there is a syntax error somewhere. Those edge cases, like a syntax error or division by 0 are handled in my program.

* **APPLICATION:** At the start of the application all needed data gets initialized and if there is no `Database` holding all of my variables and the history then it will be created. Same goes for all needed `Table`s in that `Database`. After that a little welcome and help message is printed. The application runs in an inifinite loop once initialized. In each iteration the user is asked to input a string. If it is a command (starting with a `'!'`) the according action will be done. There is support for those actions: print the help page, clear the screen, exit the program, show or delete variables, show operators and show the history of the last calculations. If the users string is not a command my program will try to calculate it. You can save a variable with `variableName=expression` where `variableName` has to be all letters and the expression can be any supported mathematical expression. If there are whitespaces between the expression or even the variables name, they will just be ignored.
