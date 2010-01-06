/*   This file is prepared for Doxygen automatic documentation generation   */
/*! \file ********************************************************************
 *
 * \brief
 *		Apollo common definitions
 *
 * \par Documentation
 *      For comprehensive code documentation, see readme.html
 *
 * \date 2009-12-18
 *
 * \author
 *      Américo Dias <americo.dias@fe.up.pt>, 
 *		Daniel Oliveira <oliveira.daniel@fe.up.pt>, 
 *		Miguel Pina <miguel.pina@fe.up.pt>
 *
 ****************************************************************************/
#ifndef _APOLLO_COMMON_H_
#define _APOLLO_COMMON_H_

/*! \brief Apollo communication frame structure*/
typedef struct
{
	// Command to slave device
	unsigned char cmd_command; 		  /*!< Command (3 bits)*/  
	unsigned char cmd_address;		  /*!< Address (7 bits)*/ 
	// Answer from slave device
	unsigned char ans_interrupt_bit;  /*!< Interrupt bit (1 bit)*/
	unsigned char ans_analog_value;   /*!< Analog value (7 bits)*/  
  	unsigned char ans_input_command;  /*!< Input command (3 bits)*/ 
  	unsigned char ans_device_type;    /*!< Device type (3 bits)*/ 
  	unsigned char ans_address;        /*!< Address (7 bits)*/ 
} ApolloFrame;

#endif //_APOLLO_COMMON_H_

