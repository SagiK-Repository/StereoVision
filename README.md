# SteroVision
StreoVision, Streo Vision

### 목적
- StreoVision을 하는데 그 목적이 있다.

### 예상 과정

```mermaid
flowchart LR

subgraph G_1 ["PC"]
A_1["Image<br>StreoVision"]
B_1["Image<br>StreoVision<br> in C++"]
C_1["Image<br>StreoVision<br> in Python"]
end

subgraph G_2 ["Raspberry-Pi"]
B_2["Video<br>StreoVision<br> in C++"]
C_2["Video<br>StreoVision<br> in Python"]
end

subgraph G_2 ["Jetson Nano"]
B_3["Video<br>StreoVision<br> in C++"]
C_3["Video<br>StreoVision<br> in Python"]
end


A_0["StreoVision"]-->A_1-->B_1 & C_1
B_1 --> B_2 --> B_3
C_1 --> C_2 --> C_3


```

### 목표
- [ ] : [목적을 이루기 위한 목표1]
- [ ] : [목적을 이루기 위한 목표2]
- [ ] : [목적을 이루기 위한 목표3]

### 제작자
[@SAgiKPJH](https://github.com/SAgiKPJH)

### 참조
- non