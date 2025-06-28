# 并行计算导论

## 内容简介
随着当前深度学习模型(特别是Transformer架构)不断地增大，计算需求也不断增大。

提升计算速度的一种方式是并行计算，即利用并行的思路拆解目标计算，使其能用并行的方式进行计算从而能够在一定程度上加快计算。

而在具体的实践中，除了考虑并行计算的方法之外，还需要考虑不同硬件的计算性能，通信时间等。

在这里从基础的内容到并行计算再到具体的模型案例进行梳理和介绍

## 内容规划
从基础的C语言到并发编程基础，再到并行计算基础，内容逻辑如下：

1. C/C++基础：熟悉完整的C/C++内容。
2. 基于C/C++的并发编程基础。
3. 并行计算基础。
4. 具体案例。

注：该项目主要是个人的学习笔记，其目的主要是快速熟悉并行计算的相关思路和技巧。

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

## TODO List
- [x] 搭建docsify展示。
- [ ] 构建项目例子展示。
- [ ] 设计导论内容，并准备相关材料。

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=Wings236/parallel_computing_tutorial&type=Date)](https://star-history.com/#Wings236/parallel_computing_tutorial&Date)
