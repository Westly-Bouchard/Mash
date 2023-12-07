# Title
Name: Westly Bouchard \
CSCI 200 Section: Section F\
Project Title: Mash (Mini-Bash)

# Problem Description

I have often found myself wanting to automate small tasks around my computer, however I have never really found an easy 
enough way to do this (to me at least) that I actually go about implementing the automations. For this project I wanted 
to try my hand at writing an interpreter for a small language of my own design. Specifically, a language that feels kind 
of like c++ or java, but that has built in functionality for executing commands in the terminal and interacting with the 
filesystem. While these things are possible in c++ and java, I also wanted my language to be a scripting language in 
order for it to be easier to use.

# Program Documentation

## Build and Run
To build mash, simply run `make` in the project root directory. All compiled object files will be placed in the `build`
subdirectory, and the `mash` executable will be placed in the root directory.

Provided with this project are some example scripts, they can be found in the `examples` subdirectory
- `fib.mash` will print the first 20 numbers of the fibonacci sequence
- `pwdUnix.mash` and `pwdWin.mash` showcase the `exec()` function in mash, which allows the user to execute commands in 
the terminal and store their results in mash variables. There is a Windows version and a unix version, as different commands
are used for each operating system.
- `syntaxError.mash` is just a short, one line script that will cause the interpreter to report a syntax error. This is
to demonstrate the error reporting functionality built into the interpreter.

To run one of these examples, you can run `./mash [options] <filename>` on Unix systems or `.\mash [options] <filename>`
on Windows. Mash has two optional arguments:
- `-s` Will enable debug output from the lexical analysis stage of interpretation. Before execution, the interpreter
will print all the tokens it has parsed to the standard out stream. 
- `-p` Will enable debug output from the Parser. This functionality uses the `ASTWriter` class provided in `tool` to
display the parsed syntax tree from the provided source file. The formatting isn't great so beware.

So, if I wanted to run the fibonacci printing script with debug output from the parser I could run\
`./mash -p examples/fib.mash`

In terms of modifying or extending mash, this will probably be quite difficult. The project is not structured very well,
and usually making changes or adding functionality includes modifying many different parts of the project. It is not impossible,
however, and some things are easier than others. For example, adding more interpretation stages should not be too hard.

For example, if you wanted to add a more exhaustive type checking system in the form of an intermediate pass between parsing
and execution, this could be done fairly easily. These passes utilize the visitor pattern to work with the AST, so you could
simply extend the visitors provided for expressions and statements and implement their `visit()` methods for each subtype.

This might look something like:
```c++
class TypeChecker : public StmtVisitor<int>, public ExprVisitor<Value> {
    public:
        void visit(Stmt& visitable) override;
        // Overrides for other visitable types...
        
        void CheckTypes();  
};
```

Another couple of features that I would have loved to add are string concatenation with types other than string (so you 
could add integers or doubles to strings to make more complex commands and achieve more complex behavior), and a function
like `echo()` or `exec()` for getting input from the user.

Longer term goals include:
- A more exhaustive type system
- Functions or subroutines
- Classes and inheritance
- A possible compiler / vm configuration rather than an interpreter

But, given how long this minimum viable product took, I'm not sure how likely it is that I will actually write those parts.

# Class Description

I created many custom classes for this project, from fairly simple data classes for storing program structure in abstract 
syntax trees, to complex functional classes for lexing, parsing, and interpreting programs.

One example of this is the `Scanner` class, which handles translating the raw character stream from the source file to a 
stream of token objects that can be later used to build abstract syntax trees. This helped the structure of my program, 
because performing all the lexical analysis in the `main()` function would have made the code very unreadable.

# List Data Structure

Again, I used many list structures throughout the mash interpreter. However, the most prominent one is most definitely 
`vector`. Vectors are used throughout the interpreter to pass data between different parts of the interpreter.

For example, the `Scanner` takes in a stream of characters and returns a `vector<Token>` of Mash tokens to its caller. 
This vector is then passed to the `Parser`, which parses the tokens into an abstract syntax tree. This tree's root node 
is a vector of `Stmt` dataclasses which recursively include other AST nodes. Finally, the interpreter takes in this 
vector of statements and walks through them, executing as it goes.

So vectors are integral to the structure of the mash interpreter, they make up the foundation of the various intermediate
representations of the program that are used throughout the interpreter.

# File I/O

File IO is a very important part of any compiler / interpreter. The entire point of the mash interpreter is to execute 
a given program from a source file. FileIO was incorporated by taking a source file in as a command line argument, and 
opens that file and passes the `ifstream` reference 

# Reflections

I learned so much from this project, I'm just going to jot down a little list of some of the things
- Language Design
- Managing large C++ projects
- Debugging
- Many design patterns (the most prominent one being the visitor pattern)

However, the final project is not quite where I wanted it to be. There are some things that I just did not have time to 
implement, like string concatenation or a function to get input from the user. Additionally, `for` loops don't work exactly
how I wanted them to. In my next project, I will definitely spend some more time planning and writing pseudocode before 
I actually start working on the project itself. Specifically, just being aware of the overarching project structure before
I started writing a bunch of code would have been a good idea, just to help keep things a little bit more organized.
