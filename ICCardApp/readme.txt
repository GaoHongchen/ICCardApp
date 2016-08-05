开发环境：
Win7 32bit，qt-opensource-windows-x86-mingw492-5.5.0


VC的引用库文件为xxx.lib， GCC的为xxx.a，通过比较两种库文件的格式，发现很相似。于是把xxx.dll，xxx.lib和xxx.h复制到Qt的project下，直接把xxx.lib改为xxx.a, 根据Qt的库名字的格式， 在xxx.a的前面加上lib， 即为libxxx.a。
再在Qt的.pro文件中最后面加上
LIBS += -L. –lxxx  //增加当前目录下的libxxx.a

先在pro文件中加入一行：
LIBS += -L ./ -lPlotDll
然后将PlotDll.dll和PlotDll.lib拷贝到工程build目录下（就是含有Makefile的目录），再重新编译一次，应该就可以了