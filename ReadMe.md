记录学习android过程中的代码。该项目是针对android-6.0.1_r11而做，镜像文件中安卓远吗和androidex并列放，如下：
``` bash
/
|- android-6.0.1_r11    # android源码
|- androidex
```
androidex内的项目有的需要拷贝到源码external下，有的需要拷贝到drivers下，在每个项目文件夹下都有一个setup.sh文件，用来完成把自己放到正确的位置。实际操作是在目标位置创建软链，指向androidex下的项目。这样做可以只在androidex下修改和管理文件，不需要再往源码同步。源码就能编译到最新androidex的内容。
在androidex根目录下还有一个setup.sh文件，只需要执行一次
``` bash
sh setup.sh
```
它会完成每个项目下的setup.sh的执行。
