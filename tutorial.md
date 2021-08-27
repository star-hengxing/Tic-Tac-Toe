# 总览

本次教程，你需要实现基础的AI算法来指导井字棋AI进行选择。

先简单说一下这个指导AI选择的思路。我们把整个游戏流程当成一个树状图，把每一步都列出来。

<center>    <img style="border-radius: 0.3125em;    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);"     src="https://pic1.zhimg.com/80/v2-71463a9b4164037bfa560428a380f414_720w.jpg?source=1940ef5c">    <br>    <div style="color:orange; border-bottom: 1px solid #d9d9d9;    display: inline-block;    color: #999;    padding: 2px;">https://www.zhihu.com/question/27221568/answer/140874499</div> </center>

列完后，我们可以发现这次游戏不同选择啊的不同结果，这时候我们有一个评估函数，赢就加1分，平局0分，输局-1分。那么我们把此分数传上去根节点，这样当你选择的时候，就知道哪个位置分数最高，选择这个位置就能走向胜利。

核心思路就是用一个利用穷举深度搜索所有可能性，然后找到赢的可能性。

五子棋和围棋也是这种**类型**的游戏，但井字棋3x3大小的地图，这个程度的穷举对计算机还算友好。其余两种，大家都知道棋盘有多大了，穷举出来能跑很久，所以就有了各种加速搜索的算法。

算法讲解轮子已经有了，我就不献丑了(

# 编译

* C++20，仅windows平台，Linux暂未测试
* Rust latest 编译器即可

# 作业框架

我们使用三个常量来表示估值函数，分别是**WIN**/**DRAW**/**LOSE**。

枚举**status_type**表示井字棋的三种状态。

game_map结构体提供了几个方法。

**update**：指定填充井字棋地图的一个位置

**is_win**：检测当前玩家是否胜利。

**is_full**：检测井字棋地图是否全部非空。

# coding

**find_step**函数是对外的接口，返回AI选择的位置。

## 极大极小值算法

[wiki](https://en.wikipedia.org/wiki/Minimax)

你需要修改**find_max_step**和**find_max_step**函数。

完成递归的终止判断，也就是使用评估函数(可以使用框架提供的三个常量)，然后对非空的地方位置进行递归穷举。

## Alpha–beta剪枝算法

[wiki](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

你需要修改**find_xxx_step**系列函数，给函数传进可供修改的alpha和beta参数，当可剪枝的时候，该函数直接返回当前记录的估值。

验证

1. 取消在main函数里调用**find_step**函数上的注释，通过计时验证是否提高了效率。
2. 手动添加全局变量，放在**find_xxx_step**系列函数里，观察调用次数。