# ICCardApp
A Project Related to IC Cards Management Developed with Qt5.

---

## Developement Requirements
* System: Windows 7 (32bit)
* Qt: Qt 5.5.0(with MinGW 4.9.2)
* Qt Binary file: qt-opensource-windows-x86-mingw492-5.5.0.exe
* MySql Database: libmysql, WampServer
* Access Database: Microsoft Access 2010
* CH375 Interface: CH375DLL.DLL
* Package Tool: Enigma Virtual Box

## Package
Files related was stored in the **ICCardApp_EVB** folder on BaiduYun.
![](http://i.imgur.com/Mh2lwuX.png)

## Documents
Documents related to Data Protocal was stored on BaiduYun.

## Issues
### 发布的QT程序无法显示图标和图片
将qt的安装目录下面的imageformats和platforms文件夹复制到可执行程序目录下

### 运行时错误
在exe同级目录下添加完依赖的dll之后，再新建一个platforms文件夹，将qminimal.dll、qwindows.dll放入其中

**Note:** 我的这两个文件夹在D:\Program_Files\Qt\Qt5.5.0\Tools\QtCreator\bin\plugins目录下

### 待测试
如果直接把相关的Qt的dll放在exe的目录下，在别的系统中是不能运行的。因为它还需要加载一些运行库。这里使用vs2010，故运行库为msvcp100.dll,msvcr100.dll等等。

## Picture
![](http://i.imgur.com/N9csVRY.png)