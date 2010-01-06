/*   This file is prepared for Doxygen automatic documentation generation   */
/*! \file ********************************************************************
 *
 * \brief
 *      Linux kernel module for apollo protocol.
 *
 * \par References:
 *      AVR32408: Using GPIO with Linux on the AVR32\n
 *      Carlos Becker: <a href="http://carlosbecker.com.ar">
 *                      Interfacing a character LCD display</a>
 *
 * \par Documentation:
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

#include <linux/module.h>
#include "chardev.h"
#include "version.h"

/*! \brief Module init function.
 *  This function is called when the module is loaded into the kernel.
 */
int init_module(void)
{
    int ret_val;

    //register char device
    ret_val = register_apollo_chrdev();
    if ( ret_val < 0 )
    {
        printk( KERN_ALERT "Apollo module: couldn't register device\n" );
        return ret_val;
    }
  
    printk(KERN_DEBUG "Apollo module: module loaded (version %s)\n", DISP(VERSION));
  
    return 0;
}

/*! \brief Module exit function.
 *  This function is called when the module is unloaded from the kernel
 */
void cleanup_module(void)
{
    printk(KERN_DEBUG "Apollo module: closing device\n");
    // Unregister character device from kernel
    unregister_apollo_chrdev();
}

MODULE_DESCRIPTION("Apollo protocol driver");
MODULE_AUTHOR("Americo Dias, Daniel Oliveira, Miguel Pina (<americo.dias,oliveira.daniel,miguel.pina>@fe.up.pt)");
MODULE_LICENSE("GPL");

