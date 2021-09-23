---
tags: 平行化程式
---
Hw0 References
==
## 題目
#### Problem Statement
Suppose we toss darts randomly at a square dartboard, whose bullseye is at the origin, and whose sides are two feet in length. Suppose also that there is a circle inscribed in the square dartboard. The radius of the circle is one foot, and its area is π  square feet. If the points that are hit by the darts are uniformly distributed (and we always hit the square), then the number of darts that hit inside the circle should approximately satisfy the equation:

`Number_in_Circle/Total_Number_of_Tosses = PI/4,`

since the ratio of the area of the circle to the area of the square is PI/4 (π  / 4).

We can use this pseudo code to estimate the value of π  with a random number generator:

`number_in_circle = 0;`
```
for ( toss = 0; toss < number_of_tosses; toss ++) {
    x = random double between -1 and 1;
    y = random double between -1 and 1;
    distance_squared = x * x + y * y;
    if ( distance_squared <= 1)
        number_in_circle++;
}
```
`pi_estimate = 4 * number_in_circle /(( double ) number_of_tosses);`

This is called a “Monte Carlo method”, since it uses randomness (the dart tosses). Write a serial C/C++ program that uses the Monte Carlo method to estimate π , with a reasonable number of tosses. You may want to use the type of long long int for the number of hits in the circle and the number of tosses, since both may have to be very large to get a reasonable estimate of π.

Hint: You may want to check if RAND_MAX is large enough for use with rand() to get a higher precision, and if the number of tosses is great enough to reach a higher accuracy.

#### Requirement
Your solution includes two files: a Makefile and a pi.c (in C) or a pi.cpp (in C++).
Your executable program should be named pi.out and built with the make command.
Your executable program should print out the estimated π  value, which is accurate to two decimal places (i.e., 3.14xx), without any input.
You are supposed to build and run your program by simply typing make and ./pi.out. An example shows as follows.

```
$ make
$ ./pi.out
3.1415926....
```


#### References
[Official document of GNU](MAKEhttps://www.gnu.org/software/make/manual/make.html)
[Monte Carlo method](https://en.wikipedia.org/wiki/Monte_Carlo_method)

## References
* [Estimating the value of Pi using Monte Carlo_ geeksforgeeks_C++](https://www.geeksforgeeks.org/estimating-value-pi-using-monte-carlo/)
* [Example C Program to Compute PI Using A Monte Carlo Method 
&& simple gcc commands](https://www.dartmouth.edu/~rc/classes/soft_dev/C_simple_ex.html)
* [GCC 編譯器基本使用教學與範例](https://blog.gtwang.org/programming/gcc-comipler-basic-tutorial-examples/)
* [What do the makefile symbols $@ and $< mean?](https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean)
* [簡單學 makefile：makefile 介紹與範例程式](https://mropengate.blogspot.com/2018/01/makefile.html)
* [gcc params](https://gist.github.com/idhowardgj94/9a3a523e66f04ca87c3c41fa691128c5)
* [使用 gcc 自製 C/C++ 靜態、共享與動態載入函式庫教學](https://blog.gtwang.org/programming/howto-create-library-using-gcc/)
* [.o vs .out in C](https://stackoverflow.com/questions/58245469/o-vs-out-in-c)
* [Makefile範例教學](https://jasonblog.github.io/note/gunmake/makefilefan_li_jiao_xue.html)
* [gcc -o how to name object file](https://stackoverflow.com/questions/36364743/gcc-o-how-to-name-object-file)
* [Running all targets at once in a Makefile??](https://stackoverflow.com/questions/29173136/running-all-targets-at-once-in-a-makefile)
* [Should I name "makefile" or "Makefile"?](https://stackoverflow.com/questions/12669367/should-i-name-makefile-or-makefile)
* [How to Install CodeBlocks ( IDE 20.03 ) with MinGW for C and C++ Programming on Windows 10](https://www.youtube.com/watch?v=GWJqsmitR2I)
* [Cygwin 和MinGW 的区别与联系是怎样的？](https://www.zhihu.com/question/22137175)
* [Installing C and C++ compiler (GNU GCC Compiler) On Ubuntu/Debian Linux](https://www.osetc.com/en/installing-c-and-c-compiler-gnu-gcc-compiler-on-ubuntu-debian-linux.html)
* [How to Install GDB?](http://www.gdbtutorial.com/tutorial/how-install-gdb)
* [Using the system(“pause”) command in C++](https://www.journaldev.com/41740/system-pause-command-c-plus-plus)
* [is it necessary to have same names for .c and .o files?](https://stackoverflow.com/questions/25376496/is-it-necessary-to-have-same-names-for-c-and-o-files)
#### Others
* [How to show line numbering in nano when opening a file](https://askubuntu.com/questions/73444/how-to-show-line-numbering-in-nano-when-opening-a-file)
* [warning: return type defaults to ‘int’ [-Wreturn-type]](https://stackoverflow.com/questions/12373538/warning-return-type-defaults-to-int-wreturn-type)
* [How to remove all files starting with a certain string in Linux](https://superuser.com/questions/482435/how-to-remove-all-files-starting-with-a-certain-string-in-linux)
* [Jason's note](https://jasonblog.github.io/note/index.html)
* [GNU Make 使用手冊中譯](https://www.cc.ntut.edu.tw/~yccheng/oop2005f/GNUMakeManual.pdf)