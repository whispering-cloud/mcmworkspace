## 获取数据
1. 运动员参数
2. 赛道数据 2021东京奥运会或者UCI 里程数据以及每个位置的高度

| 运动员参数 |           解释           | 数值                    |
| ---------: | :----------------------: | :---------------------- |
|        $M$ |     运动员的最大功率     | $n*m+k$                 |
|        $E$ | 运动员的体转能量转换效率 | $\frac{n*m+k}{R*(1-n)}$ |
|        $LT$ |     运动员的耐乳酸能力     | $LT=l$                |
|       $CP$ |      运动员的恢复力      | $k*(1-n)$               |

**注：以上参数的获取方法：**
1. 把power curve拟合$y=m*n^x+l*x+k$得到$m,n,l,k$
2. 把$m,n,l,k$代入上表

## 函数定义

### func: $\delta_p(s,p,v)=>(\delta s_p,\delta r_p,\delta v_p)$
定义：在距离为$s$，功率为$p$，速度为$v$，计算在单位时间内，距离、体力和速度的变化量。

|          常量 | 值    |
| ------------: | :---- |
|         $c_r$ | 0.003 |
|           $m$ | 80    |
|           $g$ | 9.8   |
|        $\eta$ | 0.95  |
|        $\rho$ | 1.2   |
| $c_w \cdot A$ | 0.31  |

|     变量 | 值                                                           |
| -------: | :----------------------------------------------------------- |
| $\theta$ | $arctan(\frac{dh}{ds})$【注：$\frac{dh}{ds}$为坡度】         |
|    $F_r$ | $c_rmg$                                                      |
|    $F_w$ | $\rho c_w\cdot A(v-v_w)^2$                                   |
|    $F_s$ | $mg\cdot sin\theta$                                          |
|      $f$ | $F_r+F_w+F_s$                                                |
|      $a$ | $\frac{P-f\cdot v_0}{m\cdot v_0}$【注：$v_0$表示上一个速度】 |
|    $v_p$ | $v_0+a$                                                      |
|    $s_p$ | $\frac{v_0+v}{2}+s_0$                                        |
|    $r_p$ | $CP-\frac{P}{E}$                                             |

## 搞dp
- 路程单位 0.01km 
- 体力单位 1J 
- 速度单位 0.1m/s
- 时间单位 1s
$$dp_{i+1,j+r_p,v+v_p}= max_{p = 0}^{M*\frac{j}{R}}\{dp_{i,j,v}+s_p\}$$



## 第一问
两个TT 一男一女
男TT Eddie Anderson https://www.strava.com/activities/6705570242/power-curve
女TT Jessica Allen https://www.strava.com/activities/6681616427/power-curve
两个climber 一男一女
男climber Johannes Weber https://www.strava.com/activities/5860321729/power-curve
女climber eackerlund  https://www.strava.com/activities/6699067197/power-curve
## 第二问
代入 我就不写了

## 第三问
加上 $v_w$ 作为参数输入
## 第四问
对power curve 平滑窗口
再重新计算时间
## 第五问
对每个人进行一次模型的跑（？）
按时间排序
排第四名的按照模型来跑
前三名就跟在第四名前面帮他挡风


