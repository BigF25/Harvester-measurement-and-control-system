#ifndef __CANdevice_H
#define __CANdevice_H	
#include "sys.h" 
#include "CANdevice3402.h"
#include "CANdevice4055.h"
#include "CANdevice5801.h"
#include "CANdevice7017.h"

#define ADDRESS_3402		1
#define ADDRESS_4055		2
#define ADDRESS_5801_1	3
#define ADDRESS_5801_2	4
#define ADDRESS_7017		5

typedef u8 TPDOCommand;
typedef u8 TPDOChannel;
#define SendMsg_Force_OK 0
#define SendMsg_Force_NO 1

#define TPDO_CH1 	0x00
#define TPDO_CH2 	0x01
#define TPDO_CH3 	0x02
#define TPDO_CH4 	0x03
#define TPDOCOMMAND_YES 0xFF
#define TPDOCOMMAND_NO 	0x01
u8 enable_TPDO(uint32_t id, TPDOChannel channel, TPDOCommand command);

#define microsecond(x) x
u8 set_lapsetime_TPDO(uint32_t id, TPDOChannel channel, u16 time);
u8 read_lapsetime_TPDO(uint32_t id, TPDOChannel channel);
u8 event_TPDO(uint32_t id, TPDOChannel channel, u16 time);

u8 CANdevice_sendmsg_force(CAN_TypeDef* CANx, CanTxMsg* TxMessage);

#endif 

