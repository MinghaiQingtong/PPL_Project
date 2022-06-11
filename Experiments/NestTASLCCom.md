| Number  |                            Loops                             |  Nest Ranking  |        TASLC         | irankfinder |
| :-----: | :----------------------------------------------------------: | :------------: | :------------------: | :---------: |
|    0    |            while(-x+y<=0, -x-y+1<=0) y=y-2x+1 x=x            |       U        |          F           |      U      |
|    1    |            while(-x+y<=0, -x-y<=-1) y=y-2x+1 x=x             |       U        |          F           |      U      |
|    6    |             while(q>=1) q=q+a-1 a=3a-4b, b=4a+3b             |       U        |          U           |      U      |
|    9    |                    while(x>=0) x=x-y y=y                     |       U        |          F           |      F      |
|   10    |                while(x>=0, y=0) x=x-c y=y c=c                |       U        |          F           |      F      |
|   11    |                   while(x>=23) x=x-c, c=c                    |       U        |          F           |      F      |
|   12    |                    while(x>=0) x=x-y y=y                     |       U        |          F           |      F      |
|   15    |               while(x>=0) x=x-a, a=b+1, b=a+1                |       T        |          T           |      T      |
|   21    |                while(4x+y>=1) x=-2x+4y, y=4x                 |       U        |          U           |      U      |
|   25    |             while(q<=55) q=q+a-1, 2a=a+2b, 2b=b              |       U        |          U           |      F      |
|   26    |             while(q<=54) q=q+a-1, 2a=a+2b, 2b=b              |       U        |          U           |      F      |
|   27    |         while(q>=0, a>=1, b>=1) q=q+a-b, a=2a, b=3b          |       U        |          U           |      U      |
|   29    |              while(x>=0, y>=0) t=y-1, y=x, x=t               |       T        |          T           |      T      |
|   30    |                while(x>=0, y=0) x=y-1, y=x+1                 |       T        |          T           |      T      |
|   31    |  while(q>=1) q=q+a-1, a=3a-5b+c, b=12a+3b, c=3c-4d, d=4c+3d  |       T        |          T           |      U      |
|   34    |                    while(y<=-1) x=x+1 y=y                    |       U        |          U           |      F      |
|   35    |                  while(y>=0, y<=10) 2y=2y+1                  |       T        |          T           |      T      |
|   36    |                       while(x>=1) 2x=x                       |       T        |          T           |      T      |
|   38    |        while(a>=1, b+1<=0, a+b>=0, a+b<=5) a=2a, b=2b        |       U        |          U           |      F      |
|   39    |                 while(y>=0) y=y-a+b a=a b=b                  |       U        |          F           |      F      |
|   40    |            while(x>=0) x=x+y, y=y+z, z=z+w, w=w-c            |       U        |          F           |      F      |
|   49    |                   while(x>=0) x=x-y, y=2y                    |       U        |          F           |      F      |
|   50    |                    while(0<=x<=1) x=3x-1                     |       U        |          F           |      U      |
|   51    |                    while(x>=1) x=x-y y=1                     |       T        |          T           |      T      |
|   52    |                    while(x>=1) y=1, x=x-y                    |       T        |          T           |      T      |
|   53    |                  while(x>=0) x=x-y, 2y=y+1                   |       T        |          T           |      T      |
|   55    |         while(x>=0, y>=0, z+x>=0) y=y-x, z=z+x-2 x=x         |       U        |          T           |      U      |
|   60    |                while(x>=0) x=x-y, y=y-z, z=-z                |       U        |          F           |      F      |
|   61    |                while(y<=6,x>=0) y=-y+7, x=x-y                |       T        |          T           |      T      |
|   63    |               while(2x+y>=0) x=x-c, y=y+c,c=c                |       U        |          F           |      F      |
|   65    |      while(z>=0) x=y-c, y=x, z=z+x+y-a+b, c=c, a=a, b=b      |       U        |          F           |      F      |
|   66    |                  while(q>=1) q=q+z-1, z=-z                   |       T        |          T           |      T      |
|   67    |              while(q>=0) q=q+z-y-1, y=-y, z=-z               |       T        |          T           |      T      |
|   68    |          while(q>=1) q=q+a-1, 10a=6a-8b, 10b=8a+6b           |       T        |          T           |      T      |
|   70    |             while(x>=1, y>=1) x=x-i, y=y+i, i=i              |       U        |          F           |      F      |
|   72    |                  while(x+c>=0) x=x-c, c=c+1                  |       T        |          T           |      T      |
|   73    |                   while(x>=b) x=x-d, d=d+2                   |       U        |          U           |      U      |
|   75    |                       while(x>=2) x=2x                       |       U        |          U           |      F      |
|   78    |        while(b>=-2, 3a+2>=b, a+b>=1) a=3a-1, b=2b+a+1        |       U        |          U           |      F      |
|   79    |                     while(x>=1) x=-2x+9                      |       U        |          F           |      F      |
|   80    |                while(a-b>=2, b>=1) a=3a, b=2b                |       U        |          U           |      F      |
|   81    |                  while(x>=0) x=x-2c+1, c=c                   |       U        |          F           |      F      |
|   83    |         while(a-b>=-5, -a+4b<=4) 4a=3a+b, 4b=a+3b+8          |       T        |          T           |      T      |
|   84    |                       while(x>=1) x=2x                       |       U        |          U           |      F      |
|   85    |          while(q<=-1) q=q+a-1, 10a=6a-8b, 10b=8a+6b          |       U        |          U           |      F      |
|   86    |                  while(b<=-1) a=2a+b, b=2b                   |       U        |          U           |      F      |
|   88    |                    while(x>=0) y=y-1, x=x                    |       U        |          U           |      F      |
|   89    |                    while(x>=0) x=x+c, c=c                    |       U        |          F           |      F      |
|   93    |                  while(a+b>=3) a=3a-2, b=2b                  |       U        |          U           |      U      |
|   94    |                  while(a+b>=4) a=3a+b, b=2b                  |       U        |          U           |      F      |
|   95    |                    while(x>=0) x=2x, y=3y                    |       U        |          F           |      F      |
|   96    |               while(x+y>=1, x<=-1) x=2x, y=3y                |       U        |          U           |      F      |
|   97    |                 while(x>=0) x=2x+3y, y=7y+11                 |       U        |          F           |      U      |
|   98    |             while(z>=1, y<=-1) x=3x, y=2y, z=x+y             |       U        |          U           |      F      |
|   99    |             while(z>=0) x=x+y, y=y-x+1, z=z+x+1              |       U        |          U           |      U      |
|   100   |         while(y+z>=1, x>=1, x+y<=-1) x=2x, y=3y z=7z         |       U        |          U           |      F      |
|   101   |               while(x>=1) x=x+y, y=y+z, z=z+x                |       U        |          U           |      F      |
|   102   |              while(x+y>=1, x+1<=0) 2x=5x, y=3y               |       U        |          U           |      F      |
|   103   |               while(x+y>=1, x+1<=0) x=2x, y=3y               |       U        |          U           |      F      |
|   104   | while(x<=-1, y<=-1, z<=-1, z<=7y-1, y<=11x-1) x=2x, y=3y, z=5z |       U        |          U           |      F      |
|   105   |                    while(x>=1) x=x+y, y=x                    |       U        |          U           |      U      |
|   106   |              while(a=b, a>=2, b>=2) a=3a, b=3b               |       U        |          U           |      F      |
|   107   |      while(x>=1, y>=1, z>=1) x=10x-8y+9z, y=5y+7z, z=2z      |       U        |          U           |      U      |
|   108   |      while(x>=y, y>=1) x=3x, y=2y+100000z, z=z+12345678      |       U        |          U           |      F      |
|   109   |               while(a-b>=0, b>=0) a=3a, b=b+1                |       U        |          U           |      F      |
|   112   |                     while(x>=0) x=-2x+10                     |       U        |          F           |      U      |
|   113   |                    while(c<=0) x=x+c, c=c                    |       U        |          F           |      F      |
|   115   |                       while(x>=1) x=-x                       |       T        |          T           |      T      |
|   116   | while(2x-y-4z>=1) x=-20x-0y+75z, 20y=-7x+97y+105z, 97z=37x+3y-40z |       U        |          U           |      U      |
|   119   |                      while(a>=-1) a=-a                       |       U        |          F           |      F      |
|   120   |                   while(a>=-1, a<=1) a=-a                    |       U        |          F           |      F      |
|   121   |                      while(x>=0) x=x+1                       |       U        |          U           |      F      |
|   122   |               while(x>=0) x=x+a-b-1, a=a, b=b                |       U        |          F           |      F      |
|   123   |                    while(x>=0) x=x-c, c=c                    |       U        |          F           |      F      |
|   126   |                  while(x>=0) x=x+y, y=-2y-1                  |       T        |          T           |      U      |
|   129   |                    while(x>=-1048) x=x-1                     |       T        |          T           |      T      |
|   132   |               while(x>=0) x=x-1, a=a-3, c=c+2b               |       T        |          T           |      T      |
|   136   |              while(2x+y>=1) z=x, x=-z-7y, y=-3z              |       U        |          U           |      U      |
|   140   |                 while(x>=0) z=y, y=2y-x, x=z                 |       U        |          F           |      U      |
|   144   |         while(x>=0, z>=0) x=x-y, y=y+1, z=z-w, w=w+1         |       T        |          T           |      T      |
|   150   |           while(a-b>=1, a+b>=1, a<=10) a=b, b=b-1            |       T        |          T           |      T      |
|   156   |                   while(a>=0) a=a+b, b=b-1                   |       T        |          T           |      T      |
|   165   |                 while(a>=1, b>=1) a=a-b, b=b                 |       T        |          T           |      T      |
|   170   |                 while(a>=1, b>=a) a=3a, b=2b                 |       U        |          U           |      U      |
| SUMTIME |                                                              | 8.58s(Depth=8) | 3.92s(Depth=2，k=10) |   13.265s   |


