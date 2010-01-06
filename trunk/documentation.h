/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Apollo Linux Kernel Module Documentation
 *
 * - Compiler:           GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with a PIO module can be used.
 *                       The example is written for ICnova AP7000 Base.
 * - References:
 *      AVR32408: Using GPIO with Linux on the AVR32\n
 *      Carlos Becker: <a href="http://carlosbecker.com.ar">
 *                      Interfacing a character LCD display</a>
 *
 * \date 2009-12-18
 *
 * \author
 *      Américo Dias <americo.dias@fe.up.pt>, 
 *      Daniel Oliveira <oliveira.daniel@fe.up.pt>, 
 *      Miguel Pina <miguel.pina@fe.up.pt>
 *
 *****************************************************************************/

/*! \page License License
 *  Apollo Linux Kernel Module
 *  Copyright (C) 2009  Américo Dias, Daniel Oliveira, Miguel Pina
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \page Changelog Changelog
 * \verbatim
05/01/10 - Final release (1.0.0)
12/22/09 - Added the interrupt bit.
         - Some bugs fixed.
12/19/09 - Initial release
\endverbatim
 */
 
/*! \mainpage
* \section intro Introduction
* This is the documentation for the data structures, functions, variables,
* defines, enums, and typedefs in the software for Apollo Linux Kernel Module.
* It also gives an examples of the usage of the driver.
*
* \section compinfo Compilation Info
* This software was written for the GNU GCC for AVR32.
* Other compilers may or may not work.
*
* \section deviceinfo Device Info
* All AVR32 devices with a PIO module can be used. This example has been tested
* with the following setup:
*
* - <a href="http://www.ic-board.de/product_info.php?info=p75_ICnova-AP7000-
* Base.html">ICnova AP7000 Base</a>
*
* \section setupinfo Setup Information
* CPU speed: <i>140 MHz</i>
*
* - Output pin: PD15
* - Input pin: PC31
* - Debug pin: PD14 *
*
* * Only with debug configuration. This pin changes its state on each bit
* read.
*
* \section application Application Usage
*
* The following code demonstrates the module usage:
*
* \code
* #include <stdio.h>
* #include <stdlib.h>
* #include <unistd.h>
* #include <fcntl.h>
* #include <string.h>
* #include <sys/ioctl.h>
* #include "apollo_common.h"
*
* int main( int argc, char *argv[] )
* {
*    int fd;
*    int res;
*    
*    ApolloFrame *frame;
*    
*    printf("Apollo Linux Kernel Module demo.\n");
*    
*    frame = calloc(sizeof(unsigned char), sizeof(ApolloFrame));
*     
*    fd = open("/dev/apollo", O_RDWR );
*    if ( fd < 0 )
*    {
*        printf("Couldn't open apollo! Make sure you've loaded the module.\n");
*        return -1;
*    }
*    
*    frame->cmd_command = 0x01;      // Command to send
*    frame->cmd_address = 0x10;      // Address of slave device
*    
*    // Now we call the kernel module, using ioctl:
*    res = ioctl(fd, 0, (void *)frame);
*    
*    // Let's print the entire frame structure
*    printf("Command:             0x%02x\n", frame->cmd_command);
*    printf("Command address:     0x%02x\n", frame->cmd_address);
*    // If everything went ok, here is our answer:
*    printf("Slave interrupt bit: 0x%02x\n", frame->ans_interrupt_bit);
*    printf("Slave analog value:  0x%02x\n", frame->ans_analog_value);
*    printf("Slave input command: 0x%02x\n", frame->ans_input_command);
*    printf("Slave device type:   0x%02x\n", frame->ans_device_type);
*    printf("Slave address:       0x%02x\n", frame->ans_address);
*   
*    close(fd);
*    
*    return 1;
* }
* \endcode
*
* Don't forget to load the module first using:
* \verbatim insmod mod_apollo.ko \endverbatim
*
* To remove the module use:
* \verbatim rmmod mod_apollo \endverbatim
*
* Finally, if the module was compiled in debug mode, you can see module
* messages with the command \b dmesg \b.
*
* When recompiling a project, make sure to run \b make \b clean before recompiling
*/
