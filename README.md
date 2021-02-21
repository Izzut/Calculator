# Calculator
The instructions for this assignment can be found in the pdf-file 'Assignment Calculator'.

## Assumtions made about the assignment
Based on the examples in the instructions, I have made the assumtion that when doing add/subtract/multiply commands the input value can only be a positive integer. Therefore the whole program only deals with integers, the result is however allowed to be negative.

## How to build and run the code on Windows
If you have everything installed to build and run c++ code using the g++ compiler and a makefile, it should just be a matter of downloading the files and typing `make` in a terminal and then runing the program called Calculator. The program can be run either with or without an argument, if you run the program without an argument it will give you the option to input commands from the command line. If you include a file or filepath as an argument when you run the program, it will take the commands written in that file as input.

Example:
```
Calculator
Calculator "C:\Documents\Calculator\examplefile.txt"
```
or
```
./Calculator
./Calculator "C:\Documents\Calculator\examplefile.txt"
```

If you do not have a g++ compiler, one can be downloaded here https://sourceforge.net/projects/mingw-w64/, and support for makefile can for exemple be installed from the package maneger choclatey by typing `choco install make` (https://chocolatey.org/install). For more detailed information one could consult step three and four found at this link https://code.visualstudio.com/docs/cpp/config-mingw.

### Additional options in the Makefile
The makefile also contains options for `make test` (using catch2 from https://github.com/catchorg/Catch2/tree/v2.x), here some simple tests can be found that I used to ensure that the logic worked from the start. These test are in no way meant to cover all possible scenarios and was only used as a tool in development. The makefile also contains an option `make valgrind` that I used to ensure no memory leaks where present in my program. Non of these has been throughourly tested on Windows but at least the test option should run, one might have to add a flag for large objects if using the compiler linked above, a comment about this is made in the makefile.

Lastly, the options to type `make cleanL` or `make cleanW` are also available, these will remove the executable file named Calculator and all .o files, cleanL uses Linux commands like rm and cleanW uses del.

## Adding another operation
If you would want to add another operation, this could be done by adding another subclass in the file Operation.h, in a same manner as the other operation classes, the new operation will also need its own get_value() function that performs the operation on a value. Once this is done the new operation should be possible to test in the test.cc file. 

Once this test yeilds satisfying results you will need to make some modifications to the Calculator.cc file. The functions create_operation_from_value() and create_operation_from_register() will need some modification and the new command that should be used to trigger this new operation need to be added along with the other commands in the function execute_command(). This should be everything that needs to change in order for a new operation to be added.

However, if you would want to add a division operation, you migth want to consider using double or float insted of integers, since divisions (even with the assumtion that all input values are positive integers) could create decimal numbers. This is not a requirement but it could be a nice addition.

## Time
I would say that this program took me a little more than a full working day to make, maybe about 10 hours.
