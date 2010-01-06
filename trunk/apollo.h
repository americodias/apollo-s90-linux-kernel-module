/*   This file is prepared for Doxygen automatic documentation generation   */
/*! \file ********************************************************************
 *
 * \brief
 *      Apollo definitions
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
#ifndef _APOLLO_H_
#define _APOLLO_H_

#include "apollo_common.h"

// Timming constraints in microseconds
// see Apollo Datasheet
// Do not modify this values. Different values may cause malfunction of the
// system.

#define T0          500
#define T1          1150
#define TP          300
#define TI          1650
#define TE          TI
#define TA          800
#define TC          250
#define TD          350

// IO pin levels
#define IN_HIGH     1
#define IN_LOW      0
#define OUT_HIGH    1
#define OUT_LOW     0

int register_apollo_pins(void);
void frame_process(void *frm);

#endif //_APOLLO_H_

