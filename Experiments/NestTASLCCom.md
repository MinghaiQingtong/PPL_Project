| Number  |                            Loops                             | Nested RFs |          TASLC          | irankfinder |
| :-----: | :----------------------------------------------------------: | :--------: | :---------------------: | :---------: |
|    1    |          while(-x+y<=0, -x-y+1<=0) y1=y-2x+1, x1=x           |     U      |            F            |      U      |
|    2    |           while(-x+y<=0, -x-y<=-1) y1=y-2x+1, x1=x           |     U      |            F            |      U      |
|    3    |           while(q>=1) q1=q+a-1, a1=3a-4b, b1=4a+3b           |     U      |            U            |      U      |
|    4    |                   while(x>=0) x1=x-y, y1=y                   |     U      |            F            |      F      |
|    5    |             while(x>=0, y=0) x1=x-c, y1=y, c1=c              |     U      |            F            |      F      |
|    6    |                  while(x>=23) x1=x-c, c1=c                   |     U      |            F            |      F      |
|    7    |                   while(x>=0) x1=x-y, y1=y                   |     U      |            F            |      F      |
|    8    |              while(x>=0) x1=x-a, a1=b+1, b1=a+1              |     T      |            T            |      T      |
|    9    |               while(4x+y>=1) x1=-2x+4y, y1=4x                |     U      |            U            |      U      |
|   10    |            while(q<=55) q1=q+a-1, 2a1=a+2b, 2b1=b            |     U      |            U            |      F      |
|   11    |            while(q<=54) q1=q+a-1, 2a1=a+2b, 2b1=b            |     U      |            U            |      F      |
|   12    |        while(q>=0, a>=1, b>=1) q1=q+a-b, a1=2a, b1=3b        |     U      |            U            |      U      |
|   13    |             while(x>=0, y>=0) t1=y-1, y1=x, x1=t             |     T      |            T            |      T      |
|   14    |               while(x>=0, y=0) x1=y-1, y1=x+1                |     T      |            T            |      T      |
|   15    | while(q>=1) q1=q+a-1, a1=3a-5b+c, b1=12a+3b, c1=3c-4d, d1=4c+3d |     T      |            T            |      U      |
|   16    |                  while(y<=-1) x1=x+1, y1=y                   |     U      |            U            |      F      |
|   17    |                 while(y>=0, y<=10) 2y1=2y+1                  |     T      |            T            |      T      |
|   18    |                      while(x>=1) 2x1=x                       |     T      |            T            |      T      |
|   19    |       while(a>=1, b+1<=0, a+b>=0, a+b<=5) a1=2a, b1=2b       |     U      |            U            |      F      |
|   20    |               while(y>=0) y1=y-a+b, a1=a, b1=b               |     U      |            F            |      F      |
|   21    |          while(x>=0) x1=x+y, y1=y+z, z1=z+w, w1=w-c          |     U      |            F            |      F      |
|   22    |                  while(x>=0) x1=x-y, y1=2y                   |     U      |            F            |      F      |
|   23    |                    while(0<=x<=1) x1=3x-1                    |     U      |            F            |      U      |
|   24    |                   while(x>=1) x1=x-y, y1=1                   |     T      |            T            |      T      |
|   25    |                   while(x>=1) y1=1, x1=x-y                   |     T      |            T            |      T      |
|   26    |                 while(x>=0) x1=x-y, 2y1=y+1                  |     T      |            T            |      T      |
|   27    |       while(x>=0, y>=0, z+x>=0) y1=y-x, z1=z+x-2, x1=x       |     U      |            T            |      U      |
|   28    |              while(x>=0) x1=x-y, y1=y-z, z1=-z               |     U      |            F            |      F      |
|   29    |               while(y<=6,x>=0) y1=-y+7, x1=x-y               |     T      |            T            |      T      |
|   30    |             while(2x+y>=0) x1=x-c, y1=y+c, c1=c              |     U      |            F            |      F      |
|   31    |   while(z>=0) x1=y-c, y1=x, z1=z+x+y-a+b, c1=c, a1=a, b1=b   |     U      |            F            |      F      |
|   32    |                 while(q>=1) q1=q+z-1, z1=-z                  |     T      |            T            |      T      |
|   33    |             while(q>=0) q1=q+z-y-1, y1=-y, z1=-z             |     T      |            T            |      T      |
|   34    |         while(q>=1) q1=q+a-1, 10a1=6a-8b, 10b1=8a+6b         |     T      |            T            |      T      |
|   35    |            while(x>=1, y>=1) x1=x-i, y1=y+i, i1=i            |     U      |            F            |      F      |
|   36    |                 while(x+c>=0) x1=x-c, c1=c+1                 |     T      |            T            |      T      |
|   37    |                  while(x>=b) x1=x-d, d1=d+2                  |     U      |            U            |      U      |
|   38    |                      while(x>=2) x1=2x                       |     U      |            U            |      F      |
|   39    |       while(b>=-2, 3a+2>=b, a+b>=1) a1=3a-1, b1=2b+a+1       |     U      |            U            |      F      |
|   40    |                     while(x>=1) x1=-2x+9                     |     U      |            F            |      F      |
|   41    |               while(a-b>=2, b>=1) a1=3a, b1=2b               |     U      |            U            |      F      |
|   42    |                 while(x>=0) x1=x-2c+1, c1=c                  |     U      |            F            |      F      |
|   43    |        while(a-b>=-5, -a+4b<=4) 4a1=3a+b, 4b1=a+3b+8         |     T      |            T            |      T      |
|   44    |                      while(x>=1) x1=2x                       |     U      |            U            |      F      |
|   45    |        while(q<=-1) q1=q+a-1, 10a1=6a-8b, 10b1=8a+6b         |     U      |            U            |      F      |
|   46    |                 while(b<=-1) a1=2a+b, b1=2b                  |     U      |            U            |      F      |
|   47    |                   while(x>=0) y1=y-1, x1=x                   |     U      |            U            |      F      |
|   48    |                   while(x>=0) x1=x+c, c1=c                   |     U      |            F            |      F      |
|   49    |                 while(a+b>=3) a1=3a-2, b1=2b                 |     U      |            U            |      U      |
|   50    |                 while(a+b>=4) a1=3a+b, b1=2b                 |     U      |            U            |      F      |
|   51    |                   while(x>=0) x1=2x, y1=3y                   |     U      |            F            |      F      |
|   52    |              while(x+y>=1, x<=-1) x1=2x, y1=3y               |     U      |            U            |      F      |
|   53    |                while(x>=0) x1=2x+3y, y1=7y+11                |     U      |            F            |      U      |
|   54    |           while(z>=1, y<=-1) x1=3x, y1=2y, z1=x+y            |     U      |            U            |      F      |
|   55    |            while(z>=0) x1=x+y, y1=y-x+1, z1=z+x+1            |     U      |            U            |      U      |
|   56    |       while(y+z>=1, x>=1, x+y<=-1) x1=2x, y1=3y, z1=7z       |     U      |            U            |      F      |
|   57    |              while(x>=1) x1=x+y, y1=y+z, z1=z+x              |     U      |            U            |      F      |
|   58    |             while(x+y>=1, x+1<=0) 2x1=5x, y1=3y              |     U      |            U            |      F      |
|   59    |              while(x+y>=1, x+1<=0) x1=2x, y1=3y              |     U      |            U            |      F      |
|   60    | while(x<=-1, y<=-1, z<=-1, z<=7y-1, y<=11x-1) x1=2x, y1=3y, z1=5z |     U      |            U            |      F      |
|   61    |                   while(x>=1) x1=x+y, y1=x                   |     U      |            U            |      U      |
|   62    |             while(a=b, a>=2, b>=2) a1=3a, b1=3b              |     U      |            U            |      F      |
|   63    |    while(x>=1, y>=1, z>=1) x1=10x-8y+9z, y1=5y+7z, z1=2z     |     U      |            U            |      U      |
|   64    |    while(x>=y, y>=1) x1=3x, y1=2y+100000z, z1=z+12345678     |     U      |            U            |      F      |
|   65    |              while(a-b>=0, b>=0) a1=3a, b1=b+1               |     U      |            U            |      F      |
|   66    |                    while(x>=0) x1=-2x+10                     |     U      |            F            |      U      |
|   67    |                   while(c<=0) x1=x+c, c1=c                   |     U      |            F            |      F      |
|   68    |                      while(x>=1) x1=-x                       |     T      |            T            |      T      |
|   69    | while(2x-y-4z>=1) x1=-20x-0y+75z, 20y1=-7x+97y+105z, 97z1=37x+3y-40z |     U      |            U            |      U      |
|   70    |                      while(a>=-1) a1=-a                      |     U      |            F            |      F      |
|   71    |                   while(a>=-1, a<=1) a1=-a                   |     U      |            F            |      F      |
|   72    |                      while(x>=0) x1=x+1                      |     U      |            U            |      F      |
|   73    |              while(x>=0) x1=x+a-b-1, a1=a, b1=b              |     U      |            F            |      F      |
|   74    |                   while(x>=0) x1=x-c, c1=c                   |     U      |            F            |      F      |
|   75    |                 while(x>=0) x1=x+y, y1=-2y-1                 |     T      |            T            |      U      |
|   76    |                    while(x>=-1048) x1=x-1                    |     T      |            T            |      T      |
|   77    |             while(x>=0) x1=x-1, a1=a-3, c1=c+2b              |     T      |            T            |      T      |
|   78    |            while(2x+y>=1) z1=x, x1=-z-7y, y1=-3z             |     U      |            U            |      U      |
|   79    |               while(x>=0) z1=y, y1=2y-x, x1=z                |     U      |            F            |      U      |
|   80    |       while(x>=0, z>=0) x1=x-y, y1=y+1, z1=z-w, w1=w+1       |     T      |            T            |      T      |
|   81    |          while(a-b>=1, a+b>=1, a<=10) a1=b, b1=b-1           |     T      |            T            |      T      |
|   82    |                  while(a>=0) a1=a+b, b1=b-1                  |     T      |            T            |      T      |
|   83    |                while(a>=1, b>=1) a1=a-b, b1=b                |     T      |            T            |      T      |
|   84    |                while(a>=1, b>=a) a1=3a, b1=2b                |     U      |            U            |      U      |
| SUMTIME |                                                              | 8.58s(d=8) | 3.92s(MaxDepth=2，k=10) |   13.265s   |

> T --- 循环程序是终止的。
>
> F --- 循环程序是非终止的。
>
> U --- 当前方法无法判断该循环程序是否终止。
>
> d --- Nested RFs的最大阶段数。
>
> MaxDepth --- TASLC的最大划分深度。
>

