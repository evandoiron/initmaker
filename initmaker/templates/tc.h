#defmacro systick
#ifdefined period
/** @brief Systic Period %period%ms */
#define SYSTICK_PERIOD %period%
#fi
#endmacro

#defmacro tc
#ifdefined name
#define %toupper(name)% TC%unit%
#fi
#endmacro

#defmacro tcc
#ifdefined name
#define %toupper(name)% TCC%unit%
#fi
#endmacro
