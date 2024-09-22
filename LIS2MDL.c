#include "MAIN.H"
#include "LIS2MDL_Reg.H"
#include "MYI2C.H"

#define LIS2MDL_ADDRESS 0x3C

void LIS2MDL_WriteReg(uint8_t RegAddress , uint8_t Data) //地址 数据
{
	MyI2C_Start();
	MyI2C_SendByte(LIS2MDL_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

 uint8_t LIS2MDL_ReadReg(uint8_t RegAddress)
{	
	uint8_t Data;
	
	MyI2C_Start(); //发送起始信号 
	
	MyI2C_SendByte(LIS2MDL_ADDRESS); //指定设备
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress); //指定地址
	MyI2C_ReceiveAck();
	
	//想要重新指定起始位就得重新发送起始信号
	MyI2C_Start(); //重复起始
	MyI2C_SendByte(LIS2MDL_ADDRESS | 0x01); //读写位为1 变成
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	
	return Data;
}

void LIS2MDL_Init(void)
{
	MyI2C_Init();
	LIS2MDL_WriteReg(LIS2MDL_CFG_REG_A,0x88);	
}

/*获取角度数值*/
void LIS2MDL_GetData(int16_t *ANGLE_X,int16_t *ANGLE_Y,int16_t *ANGLE_Z)
{	
	uint8_t DataH,DataL;
	//获取X角度
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTX_H); //读取加速度计的高八位
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTX_L); //读取加速度计的低八位
	*ANGLE_X = (DataH << 8)|DataL;
	
	//获取Y轴角度
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTY_H); //读取加速度计的高八位
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTY_L); //读取加速度计的低八位
	*ANGLE_Y = (DataH << 8)|DataL;
	
	//获取Z轴角度
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTZ_H); //读取加速度计的高八位
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTZ_L); //读取加速度计的低八位
	*ANGLE_Z = (DataH << 8)|DataL;
}
