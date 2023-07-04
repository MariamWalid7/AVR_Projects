/*
 * *************************** BIT_MATH.h ******************************************************** *
 *
 * Created: 8/4/2022 1:45:51 AM
 *  Author: maria
 *  Layer:  LIB
 */


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Reg,BitNo)  (  (Reg) |=  (1<<BitNo) )

#define CLR_BIT(Reg,BitNo)  (  (Reg) &= ~(1<<BitNo) )

#define TOG_BIT(Reg,BitNo)  (  (Reg) ^=  (1<<BitNo) )

#define GET_BIT(Reg,BitNo)  ( ((Reg)>> BitNo) & 0x01)



#endif /* BIT_MATH_H_ */
