```
本demo用的32位的vlc开发库，界面用的MFC测试界面，开发工具vs2008。

```

# vlcplay
调用vlc动态库，实现视频播放功能

# 开发包下载
vlc播放器[SDK](http://download.videolan.org/pub/videolan/vlc/3.0.0/win32/)，官方已单独打包，原始安装包中已没有SDK. 本次下载的SDK为32位版本。

# 开发平台
Windows

# 开发工具
vs2008

# FAQ
### 1.编译时，需要在stdafx.h中添加一个宏定义  #define ssize_t SSIZE_T
###  2.编译时，会提示stdint.h stdbool.h文件不存在,这个是C99的标准头文件，如果没有，需要网上下载，放到vs的include中。（例如:C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\include）