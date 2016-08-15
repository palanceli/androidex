#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#include "hello-android.h"

// 主设备号和从设备号变量
static int ha_major = 0;
static int ha_minor = 0;

// 设备类别和设备变量
static struct class* ha_class = NULL;
static struct hello_android_dev* ha_dev = NULL;

// 传统的设备文件操作方法
static int ha_open(struct inode* inode, struct file* filp);
static int ha_release(struct inode* inode, struct file* filp);
static ssize_t ha_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos);
static ssize_t ha_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos);

// 传统的设备文件操作方法表
static struct file_operations ha_fops = {
  .owner  = THIS_MODULE,
  .open   = ha_open,
  .release  = ha_release,
  .read   = ha_read,
  .write  = ha_write,
};

// devfs 文件系统的设备属性操作方法
static ssize_t ha_value_show(struct device* dev, struct device_attribute* attr, char* buf);
static ssize_t ha_value_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

// devfs文件系统的设备属性
static DEVICE_ATTR(value, S_IRUGO | S_IWUSR, ha_value_show, ha_value_store);

// 打开设备方法
static int ha_open(struct inode* inode, struct file* filp){
  struct hello_android_dev* dev;

  // 将自定义设备结构体保存在文件指针的私有数据成员中，以便访问设备是可以直接拿来用
  dev = container_of(inode->i_cdev, struct hello_android_dev, dev);
  filp->private_data = dev;

  return 0;
}

// 设备文件释放时调用
static int ha_release(struct inode* inode, struct file* filp){
  return 0;
}

static ssize_t ha_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos){
  ssize_t err = 0;
  struct hello_android_dev* dev = filp->private_data;

  // 同步访问
  if(down_interruptible(&(dev->sem))){
    return -ERESTARTSYS;
  }

  if(count < sizeof(dev->value)){
    goto out;
  }

  // 将寄存器value的值拷贝到用户提供的缓冲区
  if(copy_to_user(buf, &(dev->value), sizeof(dev->value))){
    err = -EFAULT;
    goto out;
  }
  err = sizeof(dev->value);

out:
  up(&(dev->sem));
  return err;
}

// 写设备的寄存器value的值
static ssize_t ha_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos){
  struct hello_android_dev* dev = filp->private_data;
  ssize_t err = 0;

  // 同步访问
  if(down_interruptible(&(dev->sem))){
    return -ERESTARTSYS;
  }

  if(count != sizeof(dev->value)){
    goto out;
  }

  // 将用户提供的缓冲区的值写到设备寄存器
  if(copy_from_user(&(dev->value), buf, count)){
    err = -EFAULT;
    goto out;
  }

  err = sizeof(dev->value);
out:
  up(&dev->sem);
  return err;
}

// 将寄存器value的值读取到缓冲区buf中，内部使用
static ssize_t __ha_get_value(struct hello_android_dev* dev, char* buf){
  int value = 0;
  // 同步访问
  if(down_interruptible(&(dev->sem))){
    return -ERESTARTSYS;
  }
  value = dev->value;
  up(&(dev->sem));

  return snprintf(buf, PAGE_SIZE, "%d\n", value);
}

// 把缓冲区的buf的值写到设备寄存器value中，内部使用
static ssize_t __ha_set_value(struct hello_android_dev* dev, const char* buf, size_t count){
  int value = 0;

  // 将字符串转换成数字
  value = simple_strtol(buf, NULL, 10);

  // 同步访问
  if(down_interruptible(&(dev->sem))){
    return -ERESTARTSYS;
  }

  dev->value = value;
  up(&dev->sem);

  return count;
}

// 读设备属性value的值
static ssize_t ha_value_show(struct device* dev, struct device_attribute* attr, char* buf){
  struct hello_android_dev* hadev = (struct hello_android_dev*)dev_get_drvdata(dev);

  return __ha_get_value(hadev, buf);
}

// 写设备属性value的值
static ssize_t ha_value_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count){
  struct hello_android_dev* hadev = (struct hello_android_dev*)dev_get_drvdata(dev);

  return __ha_set_value(hadev, buf, count);
}

// 读取设备寄存器value的值，保存到page缓冲区
static ssize_t ha_proc_read(char* page, char** start, off_t off, int count, int* eof, void* data){
  if(off > 0){
    *eof = 1;
    return 0;
  }
  return __ha_get_value(ha_dev, page);
}

// 把缓冲区的值buff保存到设备寄存器value
static ssize_t ha_proc_write(struct file* filp, const char __user* buff, unsigned long len, void* data){
  int err = 0;
  char* page = NULL;
  if(len > PAGE_SIZE){
    printk(KERN_ALERT"The buff is too large: %lu.\n", len);
    return -EFAULT;
  }
  page = (char*)__get_free_page(GFP_KERNEL);
  if(!page){
    printk(KERN_ALERT"Failed to alloc page.\n");
    return -ENOMEM;
  }

  // 先把用户提供的缓冲区的值拷贝到内核缓冲区
  if(copy_from_user(page, buff, len)){
    printk(KERN_ALERT"Failed to copy buff from user.\n");
    err = -EFAULT;
    goto out;
  }

  err = __ha_set_value(ha_dev, page, len);

out:
  free_page((unsigned long)page);
  return err;
}

// 创建/proc/ha文件
static void ha_create_proc(void){
  struct proc_dir_entry* entry;

  entry = create_proc_entry(HA_DEVICE_PROC_NAME, 0, NULL);
  if(entry){
    //entry->owner = THIS_MODULE;
    entry->read_proc = ha_proc_read;
    entry->write_proc = ha_proc_write;
  }
}

// 删除/proc/ha文件
static void ha_remove_proc(void){
  remove_proc_entry(HA_DEVICE_PROC_NAME, NULL);
}

// 初始化设备
static int __ha_setup_dev(struct hello_android_dev* dev){
  int err;
  dev_t devno = MKDEV(ha_major, ha_minor);

  memset(dev, 0, sizeof(struct hello_android_dev));

  // 初始化字符设备
  cdev_init(&(dev->dev), &ha_fops);
  dev->dev.owner = THIS_MODULE;

  // 注册字符设备
  err = cdev_add(&(dev->dev), devno, 1);
  if(err){
    return err;
  }

  // 初始化信号量和寄存器value的值
  sema_init(&(dev->sem), 1);
  dev->value = 0;

  return 0;
}

// 模块加载方法
static int __init ha_init(void){
  int err = -1;
  dev_t dev = 0;
  struct device* temp = NULL;

  printk(KERN_ALERT"Initializing ha device.\n");

  // 动态分配主设备号和从设备号
  err = alloc_chrdev_region(&dev, 0, 1, HA_DEVICE_NODE_NAME);
  if(err < 0){
    printk(KERN_ALERT"Failed to alloc char dev region.\n");
    goto fail;
  }

  ha_major = MAJOR(dev);
  ha_minor = MINOR(dev);

  // 分配ha设备结构体
  ha_dev = kmalloc(sizeof(struct hello_android_dev), GFP_KERNEL);
  if(!ha_dev){
    err = -ENOMEM;
    printk(KERN_ALERT"Failed to alloc freg device.\n");
    goto unregister;
  }

  // 初始化设备
  err = __ha_setup_dev(ha_dev);
  if(err){
    printk(KERN_ALERT"Failed to setup ha device: %d.\n", err);
    goto cleanup;
  }

  // 在/sys/class/目录下创建设备类别目录ha
  ha_class = class_create(THIS_MODULE, HA_DEVICE_CLASS_NAME);
  if(IS_ERR(ha_class)){
    err = PTR_ERR(ha_class);
    printk(KERN_ALERT"Failed to create ha device class.\n");
    goto destroy_cdev;
  }

  // 在/dev/目录和/sys/class/ha目录下分别创建设备文件ha
  temp = device_create(ha_class, NULL, dev, NULL, "%s", HA_DEVICE_FILE_NAME);
  if(IS_ERR(temp)){
    err = PTR_ERR(temp);
    printk(KERN_ALERT"Failed to create ha device.\n");
    goto destroy_class;
  }

  // 在/sys/class/ha/ha目录下创建属性文件value
  err = device_create_file(temp, &dev_attr_value);
  if(err < 0){
    printk(KERN_ALERT"Failed to create attribute val of ha device.\n");
    goto destroy_device;
  }

  dev_set_drvdata(temp, ha_dev);

  // 创建/proc/ha文件
  ha_create_proc();

  printk(KERN_ALERT"Succeeded to initialize ha device.\n");

  return 0;
destroy_device:
  device_destroy(ha_class, dev);
destroy_class:
  class_destroy(ha_class);
destroy_cdev:
  cdev_del(&(ha_dev->dev));
cleanup:
  kfree(ha_dev);
unregister:
unregister_chrdev_region(MKDEV(ha_major, ha_minor), 1);
fail:
  return err;
}

// 模块卸载方法
static void __exit ha_exit(void){
  dev_t devno = MKDEV(ha_major, ha_minor);

  printk(KERN_ALERT"Destroy ha device.\n");

  // 删除/proc/ha文件
  ha_remove_proc();

  // 销毁设备类别和设备
  if(ha_class){
    device_destroy(ha_class, MKDEV(ha_major, ha_minor));
    class_destroy(ha_class);
  }

  // 删除字符设备和释放设备内存
  if(ha_dev){
    cdev_del(&(ha_dev->dev));
    kfree(ha_dev);
  }

  // 释放设备号资源
  unregister_chrdev_region(devno, 1);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Android Driver");

module_init(ha_init);
module_exit(ha_exit);
