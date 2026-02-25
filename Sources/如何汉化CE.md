我们可以去[Cheat Engine](https://www.cheatengine.org/downloads.php)的官网下载CE的最新安装包，在下方有一个`Translations`，我们下载[Chinese translation files (zh_CN)](https://www.cheatengine.org/download/zh_CN.rar)得到一个本地压缩包后解压缩，将整个`zh_CN`文件夹复制到安装目录中的`languages`文件夹中，并修改language.ini文件，将最后一行修改为`PreferedLanguage=zh_CN`。打开软件，在`编辑`、`设置`、`语言`中修改即可。
## 我用Resource Hacker找不到exe程序中的语言部分
这是因为CE 的界面文字不是硬编码在 EXE 的资源表里，而是通过==.po 语言文件==动态加载的。我们可以打开语言文件夹中的`.po`文件，可以发现其实是在此处汉化。
## 小问题
这个翻译是基于7.2的，但是现在的版本已经是7.6了。但是这并不妨碍正常使用，只是版本号出了一点小问题。推荐使用[3DM维护的一个汉化仓库](https://github.com/3DMXM/Cheat-Engine-CN)。