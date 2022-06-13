### 1. Introduction

This repository contains two folders --- code and experiments.

Code is in **/program/workspace**. And experiments with 84 SVCOMP cases are in **/Experiments/NestTASLCCom.md**.

This procedure is to solve the program termination problem. 

For example.

```C++
while(x >= y && x + y >= 1)
y = y - 2 * x + 1;
```

 This program may be terminating, may be an endless loop. But this procedure can calculate this program's termination.

### 2. Environment

This procedure need two tools --- PPL and maple.

You can download PPL with https://www.bugseng.com/ppl.

After you install PPL and maple, you can run this procedure.

### 3. Run Code

You need write the loop in file data and name1.1.cpp will open the file and read the loop.

For example.

```
while(x >= y && x + y >= 1)
y = y - 2 * x + 1;
```

You need write the loop in file data as following : 

``` C++
1 // The total loop you have. If you only write 1 loop, you just write 1. And if you write 10 loops, you need write 10. 
0 // Current loop's number. A tag to identify different loop.
2 // It means there are 2 statements coming.
-x+y<=0 -x-y+1<=0 // loop
2 // It means there are 2 statements coming.
y>=y-2*x+1 y<=y-2*x+1 // contraints. Attention: the origin contraint is y=y-2x+1, but you need to write it with inequlities represatations.
2 // The variables number.
x y // the variables. Attention: you'd better not use 'd' as your variables. It may cause some unknown error.
```

And you can just run start.sh, it will contain all compile command.

```
./start.sh
```

After you run, you will get a file --- output. The result of loops' termination are all in it.

