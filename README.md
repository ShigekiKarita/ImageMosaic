
## 準備

* C++コンパイラのインストール(C++11に対応したもの)
* OpenCVのインストール http://opencv.org/downloads.html
* ソースコードのDL (右側にZIPのリンク) または
```
git clone https://github.com/ShigekiKarita/ImageMosaic.git
```


## 利用方法

* ```Makefile``` のOpenCVパスを動かす環境に合わせる

```
INCPATH = -I/usr/local/Cellar/opencv/2.4.9/include
LIBPATH = -L/usr/local/Cellar/opencv/2.4.9/lib
```

* 次のコマンドを打つ(Makefileの内容が実行されます)

```
make
```

* 実行

```
./main

# オプション
./main threshold
./main weight
./main adjust
./main adjust-threshold
./main adjust-weight
```
* adjust : DynamicAdjusterを利用
* threshold : RGBを利用した閾値処理
* weight : RGBを利用した重み付け処理

画像が表示されたら成功
次の画像に移るには何かキーを押してください

## 注意

Visual Studioなど特殊な環境では mykeypoints.hpp 22行目

```c++:mykeypoints.hpp
//cv::initModule_nonfree();
```

上のコメントアウトを消せば動くかもしれません


## その他

shigekikarita@gmail.com まで
