/*   This file is prepared for Doxygen automatic documentation generation   */
/*! \file ********************************************************************
 *
 * \brief
 *      Apollo protocol functions
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

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/device.h>
#include <asm/gpio.h>
#include <asm/arch/at32ap700x.h>
#include "apollo.h"

/*! \brief Output pin for apollo protocol */
static int output_pin = GPIO_PIN_PD(15);
#ifdef _DEBUG
/*! \brief Debug pin for apollo protocol (Strobe on each read)*/
static int debug_pin = GPIO_PIN_PD(14);
unsigned char debug_pin_status = 0;
#endif
/*! \brief Input pin for apollo protocol */
static int input_pin = GPIO_PIN_PC(31);

/*! \brief Send bits to the apollo bus
 *  \param  value Bits to send
 *  \param  count Number of bits to send
 */
void send_bits(unsigned char value, unsigned char count)
{
    unsigned char mask;
    unsigned char counter;

    if(count == 0)
        return;

    mask = 1 << (count-1);  // Bit mask
    // Send the bits
    for(counter = 0; counter < count; counter++) {
        gpio_set_value(output_pin, OUT_LOW);

        if((value & mask) > 0)  // If the bit is 0
            udelay(T1-TP);      // the delay is T1-TP
        else                    // else
            udelay(T0-TP);      // its T0-TP
        gpio_set_value(output_pin, OUT_HIGH);
        udelay(TP);
        mask >>= 1;
    }
}

/*! \brief Read bits from the apollo bus
 *  \param  count Number of bits to send
 *  \return Bits received
 */
unsigned char read_bits(unsigned char count) {
    unsigned char result;
    unsigned char counter;

    result = 0;

    for(counter = 0; counter < count; counter++) {
        result <<= 1;
        gpio_set_value(output_pin, OUT_LOW);
        udelay((unsigned int)(TD+TC/2));
#ifdef _DEBUG
        // Change the debug pin state on each bit read
        debug_pin_status ^= 1;
        gpio_set_value(debug_pin, debug_pin_status);
#endif
        if(gpio_get_value(input_pin) == IN_HIGH)
            result |= 0x01;
        else
            result &= ~0x01;
        udelay((unsigned int)(TC/2+TA));
        gpio_set_value(output_pin, OUT_HIGH);
        udelay(TP);
    }

    return result;
}

/*! \brief Register the apollo bus pins
 *  \return Error code
 */
int register_apollo_pins(void) {
    int ret;

    ret = gpio_direction_output(output_pin,0);
    if ( ret < 0 )
        goto err;
#ifdef _DEBUG
    ret = gpio_direction_output(debug_pin,0);
    if ( ret < 0 )
        goto err;
#endif
    ret = gpio_direction_input(input_pin);
    if ( ret < 0 )
        goto err;

    return 0;

err:
    printk(KERN_WARNING "Apollo module: error configuring pins\n");
    return ret;
}

/*! \brief Process a apollo frame
 *  \param frm Pointer to a ApolloFrame structure
 */
void frame_process(void *frm)
{ 
    ApolloFrame *frame = (ApolloFrame *)frm;
    
    // Initiating/terminating pulse
    gpio_set_value(output_pin, OUT_HIGH);
    udelay(TI);
    
    send_bits(frame->cmd_command, 3);
    send_bits(frame->cmd_address, 7);
        
    frame->ans_interrupt_bit = read_bits(1);
    frame->ans_analog_value = read_bits(7);
    frame->ans_input_command = read_bits(3);
    frame->ans_device_type = read_bits(3);
    frame->ans_address = read_bits(7);
    
    gpio_set_value(output_pin, OUT_LOW);
    return;
}

