*This project has been created as part of the 42 curriculum by ltournie, ntassin.*

# **MINISHELL** or "and another bug"

## **DESCRIPTION**

Minishell is a project where we have to make a mini version of a shell in C. It should replicate most of shell's behavior. It's the first group project of 42 from where we start.
There's a lot of rules, of new functions to discover, and obviously, a lot of bug coming down with them to handle. Most of the code itself is not that complicated, but it's long to test from all the possibilities of input. It's one of the major 42 project, and this repo is our version !

## **INSTRUCTION**

We have to re-make some of the main shell program functions. First, the line that wait for the input and then the actions that must be applied by the input. Most of the works is obviously the second part. It starts by taking in the input and parsing it properly, separating words, pipes, file names, or random characters, to look for a match in the execution files or to send error message corresponding to the error found.

Additionally, we have to handle some signal input :

```Ctrl + C ; Ctrl + D ; Ctrl + \```

All of them including different reaction from the program.

And at last, we must rewrite some of the most classic commands of shell :

- "cd"
- "pwd"
- "echo"
- "export"
- "unset"
- "env"
- "exit"

As usual, all of that must compile with a Makefile and not remake, no leaks will be tolerated EXCEPTED for the leaks caused by `readline`, the function we use for taking the input (it will be used a lot). If anything seem strange, look at a the correction sheet or compare to bash directly. 

Since a lot of things in this project are already known, it's most about learning to make a large program with a lot of option and starting working in group. A lot of time is also spend on test and debugging, with all the specialties shell has. 


## **COMPILATION** 

The project includes a Makefile. A 'make' call in terminal in the corresponding directory will generate a 'minishell' executable. It takes only itself as argument. If else, it will show an error message.

Everything else is working once the program is launch.

## **RESOURCES**

[Video "make a shell in c](https://www.youtube.com/watch?v=_pc7pVvAoCg&pp=ygUTbWFrZSB5b3VyIG93biBzaGVsbA%3D%3D)\
[how to use readline](https://www.youtube.com/watch?v=naDE5VdauwU&t=15s&pp=ygUKcmVhZGxpbmUgYw%3D%3D)\
[Claude (see bellow)](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://claude.ai/&ved=2ahUKEwjX2bzGjqeUAxW_TaQEHZorKskQFnoECA8QAQ&usg=AOvVaw2e9nJiB56fxuZtuB3NvSvX)\
Peers, mostly for testing and help us spot exception in the use of commanded or limits while running \

## **IA USE**

We did use AI in this project, for help us spot mistakes in call in fonction we doesn't know (for example readline need a compilation flag), for some of the debugging we doesn't know where it come from. We have listen to advice and make our version of what we thought was effectively useful .All the code is still written by me.
