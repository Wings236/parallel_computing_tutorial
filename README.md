# 并行计算导论

## 课程简介
随着当前计算（特别是大模型计算）的增长对硬件的需求也自然增长，当然，硬件的性能本身也在不断增长。
提升计算速度的一种方式是并行计算，即利用并行的思路拆解目标计算，使其能用并行的方式进行计算
从而能够在一定程度上加快计算。

而在具体的实践中，除了考虑并行算法之外，还需要考虑不同硬件的计算性能，通信时间等。在这里只是做一个导论性质的介绍。

## 内容规划
由于该课程主要是个人的学习笔记，其目的主要是快速熟悉并行计算的相关思路和技巧，所以在这里并不会阐述得非常详细。
总的来说，主要集中在算法思路上，包括并行计算的基本原理，相关的并行计算技术介绍与实践。

- [可能] 对当前并行计算的项目代码进行讲解。

目录大纲：
| 章节    | 章节名      |
| ------- | --------   | 
| 第一章  | 基本原理    |
| 第二章  | 矩阵并行计算 |
| 第三章  | 多线程      |
| 第四章  | 单指令多数据处理 |
| 第五章  | CUDA编程    |

## 环境安装
### 安装Node.js
官网：https://nodejs.org/en/download/package-manager

### 安装docsify
```shell
npm i docsify-cli -g
```

### 启动docsify
```shell
docsify serve ./docs
```

## 参考资料
- [parallel-computing-tutorial](https://github.com/mit-han-lab/parallel-computing-tutorial)
- 《GPU编程与优化——大众高性能计算》
- 

## TODO List
- [x] 搭建docsify展示。
- [ ] 构建项目例子展示。
- [ ] 设计导论内容，并准备相关材料。

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=Wings236/parallel_computing_tutorial&type=Date)](https://star-history.com/#Wings236/parallel_computing_tutorial&Date)
