# 단축키 패드

> 아두이노, 3D 프린팅



---



## 210122 개요

> 약 한 달 전, 석사 졸업 논문 원고 쓸 당시, 
>
> 졸업 논문은 영어로 적어야 하는데 영작을 바로 못하니 한국어로 작성 → 한 문장씩 번역기 돌림 → 직접 다듬기,의 반복.
>
> 그러다 보니 ctrl + c, ctrl + v 또는 ctrl + x, ctrl + v를 몇 번이나 눌렀는지 모르겠다.
>
> 보통 ctrl 과 shift 키를 왼쪽 새끼손가락으로 누르는데, 하루 8시간 가까이를 꼬박 원고를 쓰다 보니 점점 새끼손가락이 아파오고 힘이 안 들어가더라.
>
> 그리고 요즘, 파이썬 수업에서 VS code를 사용하니까, 코드를 돌릴 때마다 ctrl + s, ctrl + \`를 해줘야 한다.
>
> 아픈 것도 아픈 거지만, ctrl + \`는 세로로 일직선상에 놓여있어서 누르기도 불편하다.
>
> 그래서 들었던 생각.
>
> 예전에 긱블에서 아케이드 버튼으로 ctrl + s 버튼을 만들었던 게 생각나서, 자주 쓰는 단축키 몇 가지로 구성된 전용 패드를 만들면 어떨까, 하고 생각했다. 



### 재료

##### 아두이노 나노 (핀 납땜 안 된 거)

일단 아두이노 중에 제일 작은 거로 찾아다녔다.

버튼이랑 전선으로 바로 납땜하려고, 핀을 납땜 안 한 쪽으로 구매했다.



##### 아케이드 버튼 

더 작은 푸쉬 버튼도 추천받았지만, 아케이드 버튼의 감촉이 좋아서 작은 크기를 찾아다녔다.

30 mm까지는 많이 팔던데 아무리 생각해도 너무 크다 느껴, 20 mm 내외로 찾아다녔다.

우리 집 3D 프린터도 원을 잘 못 그리니, 마침 사각 버튼이어서 다행이다.



### 간략한 디자인

<img src="records.assets/개요1.jpg" alt="개요1" style="zoom:80%;" />

일단 자주 쓰는 6가지 키로 구성.

유닉스 기반에서의 복사, 붙여넣기, 잘라내기 단축키도 넣을까 했지만, 버튼 크기에 따른 전체 키 패드의 크기를 고려하면 너무 커져서 뺐다.

전체 키 패드의 높이는 지금 쓰는 키보드에 맞춰서 43 mm를 넘지 않도록.

가로 세로 길이는 버튼에 크기와 간격을 맞춰서 100 × 70 mm.

조립은 뚜껑을 덮는 식으로.버튼의 색상 배치는 좀 더 생각해 봐야겠다.



---



## 210125 윗판 제작1

> 1차로 윗판 제작.
>
> 일단은 만들어보자 싶어서 뽑아 보았다.



### 도면

<img src="records.assets/윗판1-1.png" alt="윗판1-1" style="zoom:50%;" />

**<평면도>**

<img src="records.assets/윗판1-2.png" alt="윗판1-2" style="zoom:50%;" />

**<좌측면도>**



### 출력물

<img src="records.assets/윗판1(4).jpg" alt="윗판1 (4)" style="zoom: 50%;" />

아케이드 버튼 끼운 모습.



<img src="records.assets/윗판1(1).jpg" alt="윗판1 (1)" style="zoom: 50%;" />

살짝 뜬다.

두께를 1.4 mm 정도로 늘여봐야겠다.



<img src="records.assets/윗판1(2).jpg" alt="윗판1 (2)" style="zoom:50%;" />

옆면도 좀 약한 듯하다.

두께를 원래 하려던 대로, 2 mm로 올려야겠다.



<img src="records.assets/윗판1(3).jpg" alt="윗판1 (3)" style="zoom:50%;" />

윗판 높이도 30 mm로 낮춰도 될 거 같다.



<img src="records.assets/윗판1(5).jpg" alt="윗판1 (5)" style="zoom:50%;" />

전체적인 폭은 적당한 듯.



다시 그려서 출력해보자.



---



## 210126 윗판 제작2

> 어제의 수정 사항을 반영한 두 번째 윗판.



### 도면

<img src="records.assets/윗판2-1.png" alt="윗판2-1" style="zoom:50%;" />

**<평면도>**

<img src="records.assets/윗판2-2.png" alt="윗판2-2" style="zoom:50%;" />

**<정면도>**

윗면 두께를 1.4 mm로, 옆면 두께를 2 mm로 수정.



###  출력물

<img src="records.assets/윗판2(2).jpg" alt="윗판2(2)" style="zoom:50%;" />

버튼 고정이 잘 되는 걸 보니 윗면 두께는 적당한 듯하다.



<img src="records.assets/윗판2(1).jpg" alt="윗판2(1)" style="zoom:50%;" />

이번 출력물의 크기는 잘 맞았지만, 키보드 옆에 직접 놓아보니 전체 패드의 높이가 이 정도면 딱 좋겠다는 생각이 들었다.



<img src="records.assets/윗판2(3).jpg" alt="윗판2(3)" style="zoom:50%;" />

고민하다가 버튼의 다리 부분을 접어서 전체 패드의 높이를 줄이기로 하였다.

윗판의 높이를 20 mm로 수정하고, 전체 패드의 높이를 30 mm 초반이 되도록 제작할 예정이다.



---



## 210127 윗판3 + 밑판 제작

## 윗판3

### 도면

<img src="records.assets/윗판3-1.png" alt="윗판3-1" style="zoom:50%;" />

**<평면도>**

<img src="records.assets/윗판3-2.png" alt="윗판3-2" style="zoom:50%;" />

**<정면도>**

높이를 20 mm로 조절.



### 출력물

<img src="records.assets/윗판3(1).jpg" alt="윗판3(1)" style="zoom:50%;" />



<img src="records.assets/윗판3(2).jpg" alt="윗판3(2)" style="zoom:50%;" />





## 밑판

> 아두이노 나노가 들어갈 홈과 USB 연결 부위가 외부로 노출되도록 설계.



### 도면

<img src="records.assets/밑판1.png" alt="밑판1" style="zoom:50%;" />

**<평면도>**



<img src="records.assets/밑판2.png" alt="밑판2" style="zoom:50%;" />

**<정면도>**

<img src="records.assets/밑판3.png" alt="밑판3" style="zoom:50%;" />



### 출력물

<img src="records.assets/밑판(2).jpg" alt="밑판(2)" style="zoom:50%;" />

밑판은 나름 한 번만에 잘 나온 것 같다.



<img src="records.assets/조립(1).jpg" alt="조립(1)" style="zoom:50%;" />

출력물들을 조립한 모습.



<img src="records.assets/조립(2).jpg" alt="조립(2)" style="zoom:50%;" />



<img src="records.assets/조립(3).jpg" alt="조립(3)" style="zoom:50%;" />

전체 높이는 31 mm 정도.



---



## 210206 PCB판

> 코드 조사하다가, 인터럽트를 사용해야하는데 아두이노에서 인터럽트 핀은 하나 밖에 없다는 것을 알고 고민.
>
> 다이오드를 잘 사용하면, 각 버튼이 연결된 디지털 핀과 인터럽트 핀에 동시에 전압이 걸리도록 할 수 있을 거 같다 생각하였다.
>
> 연결할 것이 많아지므로 PCB판을 사용하는 게 좋을 거 같다 생각하여 집에 있던 5*7 cm PCB를 안에 넣기 위한 틀을 제작.



### 도면

<img src="records.assets/PCB판1.png" alt="PCB판1" style="zoom:50%;" />

**<평면도>**



<img src="records.assets/PCB판2.png" alt="PCB판2" style="zoom:50%;" />

**<정면도>**



<img src="records.assets/PCB판3.png" alt="PCB판3" style="zoom:50%;" />



### 출력물

<img src="records.assets/PCB판 (1).jpg" alt="PCB판 (1)" style="zoom:50%;" />



---

