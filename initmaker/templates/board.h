#defmacro board
/**
#ifdefined project
 * @defgroup %project%
#fi
 * @file %filename%
 * %processor%
#ifdefined description
 * @brief Source file for SystemInit Function
 * %description%
#fi
 * 
#ifdefined copyright
 * @copyright %copyright%
 * All Rights Reserved
#fi
#ifdefined company
 * %company%
#fi
#ifdefined author
 * @author %author%
#fi

 * @date %date%
 *
#ifdefined legal
%legal%
#fi
 **/
#ifndef __%tag%__
#define __%tag%__

#include "sam.h"

/** SystemInit is called from startup_samd51.c just prior to calling main.
  * it is by default a weak alias to Dummy_Init
  */
void SystemInit(void);
 
typedef struct {
	IRQn_Type irq;
	int32_t priority;
} NVICList_t;

/** @addtogroup GPIO
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup clocking
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup SERCOM
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup DMA
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup TC
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup EVSYS
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup MISC
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/
/** @addtogroup ExtendedInit
 *  @ingroup SystemInit
 *  @{ **/
/** @} **/

#endif /* __%tag%__ */
#endmacro