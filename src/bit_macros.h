#ifndef SET_BIT
#define SET_BIT(REG,BIT)        ((REG) |= (1U << (BIT)))
#endif

#ifndef CLEAR_BIT
#define CLEAR_BIT(REG,BIT)      ((REG) &= ~(1U << (BIT)))
#endif

#ifndef TOGGLE_BIT
#define TOGGLE_BIT(REG,BIT)     ((REG) ^= (1U << (BIT)))
#endif

#ifndef GET_BIT
#define GET_BIT(REG,BIT)        (((REG) & (1U << (BIT))) >> (BIT))
#endif
