#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydrv"
#define MYDRV_MAX_LENGTH 4096
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
static int MYDRV_MAJOR;
static char *mydrv_data;
static int mydrv_read_offset, mydrv_write_offset;

static int mydrv_open(struct inode *inode, struct file *file)
{
        if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
                return -1;
        return 0;
}

static int mydrv_release(struct inode *inode, struct file *file)
{
        if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
                return -1;
        return 0;
}
static long mydrv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        printk(KERN_INFO "mydrv_ioctl is invoked \n");
        return 0;
}

static ssize_t mydrv_read(struct file *file, char *buf, size_t count, loff_t *ppos) 
{
        if ((buf == NULL) || (count < 0)){
			gpio_is_valid(GPIO1);
			gpio_direction_output(GPIO1,1);
			gpio_is_valid(GPIO2);
			gpio_direction_output(GPIO2,0);
		}
        if ((mydrv_write_offset - mydrv_read_offset) <= 0){
			gpio_is_valid(GPIO1);
			gpio_direction_output(GPIO1,1);
			gpio_is_valid(GPIO2);
			gpio_direction_output(GPIO2,0);
		}
        count = MIN((mydrv_write_offset - mydrv_read_offset), count);
        if (copy_to_user(buf, mydrv_data + mydrv_read_offset, count)) // copy_to_user(to, from, n); 커널데이터를 유저 주소로 . mydrv_data + mydrv_read_offset에서, count 만큼.
                return -EFAULT;
        mydrv_read_offset += count;
        return count;
}

static ssize_t mydrv_write(struct file *file, const char *buf, size_t count, loff_t *ppos)//mydrv_write_offset에서 count 만큼을 읽겠다.
{
        if ((buf==NULL) || (count < 0))
                return -EINVAL;
        if (mydrv_write_offset + count >= MYDRV_MAX_LENGTH){//이게 그러니까 인자인 셈임. mydrv_write_offset 더하기 쓸 양인 count 더한게 만약에 설정한 MAX보다 크면,
                /* driver space is too small */
                return 0;
        }
        if (copy_from_user(mydrv_data + mydrv_write_offset, buf, count)) //buf에서 mydrv_data + mydrv_write_offset 로 count만큼 복사하는 것.
                return -EFAULT;
		gpio_is_valid(GPIO1);
        gpio_direction_output(GPIO1,0);
        gpio_is_valid(GPIO2);
        gpio_direction_output(GPIO2,1);

        mydrv_write_offset += count;
        return count;
}


struct file_operations mydrv_fops = {
.owner = THIS_MODULE,
.read = mydrv_read,
.write = mydrv_write,
.compat_ioctl = mydrv_ioctl,
.open = mydrv_open,
.release = mydrv_release,
};

int mydrv_init(void)
{
	
        gpio_is_valid(GPIO1);
        gpio_direction_output(GPIO1,1);

        if ((MYDRV_MAJOR = register_chrdev(0, DEVICE_NAME,&mydrv_fops)) < 0){
                printk(KERN_INFO "can't be registered \n");
                return MYDRV_MAJOR;
        }
        printk(KERN_INFO "major NO = %d \n", MYDRV_MAJOR);
        if ((mydrv_data = (char *)kmalloc(MYDRV_MAX_LENGTH * sizeof(char), GFP_KERNEL))==NULL){ //공간확보
                unregister_chrdev(MYDRV_MAJOR, DEVICE_NAME);
                return -ENOMEM;
        }
        mydrv_read_offset = mydrv_write_offset = 0;
        return 0;
}


void mydrv_cleanup(void)
{
		gpio_is_valid(GPIO1);
        gpio_direction_output(GPIO1,0);
        gpio_is_valid(GPIO2);
        gpio_direction_output(GPIO2,0);
        kfree(mydrv_data);
        unregister_chrdev(MYDRV_MAJOR, DEVICE_NAME);
}
module_init(mydrv_init);
module_exit(mydrv_cleanup);

