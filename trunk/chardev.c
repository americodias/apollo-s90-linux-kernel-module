/*   This file is prepared for Doxygen automatic documentation generation   */
/*! \file ********************************************************************
 *
 * \brief
 *      Apollo device implementation
 *
 * \par References:
 *      Carlos Becker: <a href="http://carlosbecker.com.ar">
 *                      Interfacing a character LCD display</a>
 *
 * \par Documentation
 *      For comprehensive code documentation, see readme.html
 *
 * \date 2009-12-18
 *
 * \author
 *      Américo Dias <americo.dias@fe.up.pt>, 
 *      Daniel Oliveira <oliveira.daniel@fe.up.pt>, 
 *      Miguel Pina <miguel.pina@fe.up.pt>
 *
 ****************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "chardev.h"
#include "apollo.h"

#define SUCCESS     0

/*! \brief Holds whether the device was already opened */
static int Device_Open = 0;

/*! \brief Device open
 *  Called when user calls open
 */
static int device_open( struct inode *inode, struct file *file )
{
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device_open(%p,%p)\n", inode, file);
#endif
    
    if ( Device_Open )
        return -EBUSY;      // Error: device already openned
    Device_Open++;          // Mark device as openned

    try_module_get( THIS_MODULE );
    return SUCCESS;         // OK!
}

/*! \brief Device close
 *  Called when user calls close
 */
static int device_release( struct inode *inode, struct file *file )
{
#ifdef __user
    printk(KERN_DEBUG "Apollo module: device_release(%p,%p)\n", inode, file);
#endif

     Device_Open--;         // Flag that

     module_put( THIS_MODULE );
     return SUCCESS;        // OK!
}

#ifndef DOXYGEN_IGNORE
/*! \brief Device read
 *  Called when user calls read() [Not implemented]
 */
/*static ssize_t device_read( struct file *file,
                            char __user *buffer,
                            size_t length,
                            loff_t *offset )
{
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device_read(%p,%p,%d)\n", file, buffer, (int)length);
#endif

    return 0;
}*/


/*! \brief Device Write
 *  Called when user calls write() [Not implemented]
 */
/*static ssize_t device_write( struct file *file,
                             const char __user *buffer,
                             size_t length,
                             loff_t *offset )
{
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device_Write(%p,%p,%d)\n", file, buffer, (int)length);
#endif
    return 0;  //return length
}*/
#endif

//called when user calls ioctl()
/*! \brief Device IOCTL
 *  Called when user calls ioctl(). This function implements all
 *  the Apollo protocol.
 */
int device_ioctl( struct inode *inode,
                  struct file *file,
                  unsigned int ioctl_num,
                  unsigned long arg)
{
    
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device_ioctl(%p,%d,%p)\n", file, ioctl_num, (void *)arg);
#endif
    frame_process((void *)arg);
    return SUCCESS;
}

//neccesary to register as character device
struct file_operations Fops = {
     .read   = NULL,
     .write = NULL,
     .ioctl = device_ioctl,
     .open   = device_open,
     .release= device_release,
};

//exported function, used by module.c
int register_apollo_chrdev(void)
{
    int ret;
     
    ret =  register_apollo_pins();
    if ( ret < 0 )
        goto err;
      
     ret = register_chrdev( MAJOR_NUM, DEVICE_FILE_NAME , &Fops );
     if ( ret < 0 )
        goto err;
        
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device registered\n");
#endif  
     return ret;

err:
    printk(KERN_WARNING "Apollo module: error registering device\n");
    return ret;
}
//exported function, used by module.c

int unregister_apollo_chrdev(void)
{
    unregister_chrdev( MAJOR_NUM, DEVICE_FILE_NAME );
#ifdef _DEBUG
    printk(KERN_DEBUG "Apollo module: device unregistered.\n");
#endif
    return 0;
}

