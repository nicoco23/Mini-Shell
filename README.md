*This project has been created as part of the 42 curriculum by ltournie, ntassin.*

# **MINISHELL** or "and another bug"

## **DESCRIPTION**

Minishell is a procject where we have to make a simili version of a shell programm in c. It should replicate most of the comportement of shell and behave like him. It's the first group project of 42 from where we start.
There's a lot of rules, of new functions to discover, and obviously, a lot of bug comming with them to handle. Most of the code itself is not that complicated, but it's long to test from all the possibilites of input. It's one of the major 42 project, and this repo is our version !

## **INSTRUCTION**

We have to and some of the main shell programm function. First, the line that wait for the input and then the actions that must be applied by the input. Most of the works is obliously the second part. It come from take in the input and parsing it properly, separating words, pipe, files names, or random characters with no sens, to look for a match in the execution files or to send error message correponding to the error find. All of this making it look like a shell programm.

Aditionaly, we have to handle some signal imput :

```Ctrl + C ; Ctrl + D ; Ctrl + /```

All of them including different reacton from the programm.

And at last, we must redo some of the most classic commands of shell :

- "cd"
- "pwd"
- "echo"
- "export"
- "unset"
- "env"
- "exit"

Has usual, all of that must compile with a makefile and not remake, no leaks will be tolerated EXCEPETED for the leak cause by readline, the function we use for taking the input (it will be use a lot). If anything seem strange, look at a the correction sheet or compare to bash directly. 

Since a lot of things in this project are already known, it's most about learning to make a large program with a lot of option and starting working in groupe. A lot of time is also spend on test and debuging, with all the specificities shell as. 


## **COMPILATION** 

The project includes a makefile. A 'make' call in terminal in the corrresponding directory will generate a 'minishell' executable. It take only itself as argument. If else, it will show an error message.

Ererything else is working once the program is launch.

## **RESOURCES**

[Video "make a shell in c](https://www.youtube.com/watch?v=_pc7pVvAoCg&pp=ygUTbWFrZSB5b3VyIG93biBzaGVsbA%3D%3D)\
[how to use readline](https://www.youtube.com/watch?v=naDE5VdauwU&t=15s&pp=ygUKcmVhZGxpbmUgYw%3D%3D)\
[Claude (see bellow)](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://claude.ai/&ved=2ahUKEwjX2bzGjqeUAxW_TaQEHZorKskQFnoECA8QAQ&usg=AOvVaw2e9nJiB56fxuZtuB3NvSvX)\
Peers, mostly for testing and help us spot execption in the use of commandes or limits while running \

## **IA USE**

We did use ai in this project, for help us spot mistakes in call in focntion we doesn't know (for example readline need a compilation flag), for some of the debugging we doesn't know where it come from. We have listent to advice and make our version of what we thought was effectively usefull .All the code is still written by me.
