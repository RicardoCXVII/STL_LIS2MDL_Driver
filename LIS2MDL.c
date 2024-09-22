#include "MAIN.H"
#include "LIS2MDL_Reg.H"
#include "MYI2C.H"

#define LIS2MDL_ADDRESS 0x3C

void LIS2MDL_WriteReg(uint8_t RegAddress , uint8_t Data) //��ַ ����
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
	
	MyI2C_Start(); //������ʼ�ź� 
	
	MyI2C_SendByte(LIS2MDL_ADDRESS); //ָ���豸
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress); //ָ����ַ
	MyI2C_ReceiveAck();
	
	//��Ҫ����ָ����ʼλ�͵����·�����ʼ�ź�
	MyI2C_Start(); //�ظ���ʼ
	MyI2C_SendByte(LIS2MDL_ADDRESS | 0x01); //��дλΪ1 ���
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

/*��ȡ�Ƕ���ֵ*/
void LIS2MDL_GetData(int16_t *ANGLE_X,int16_t *ANGLE_Y,int16_t *ANGLE_Z)
{	
	uint8_t DataH,DataL;
	//��ȡX�Ƕ�
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTX_H); //��ȡ���ٶȼƵĸ߰�λ
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTX_L); //��ȡ���ٶȼƵĵͰ�λ
	*ANGLE_X = (DataH << 8)|DataL;
	
	//��ȡY��Ƕ�
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTY_H); //��ȡ���ٶȼƵĸ߰�λ
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTY_L); //��ȡ���ٶȼƵĵͰ�λ
	*ANGLE_Y = (DataH << 8)|DataL;
	
	//��ȡZ��Ƕ�
	DataH = LIS2MDL_ReadReg(LIS2MDL_OUTZ_H); //��ȡ���ٶȼƵĸ߰�λ
	DataL = LIS2MDL_ReadReg(LIS2MDL_OUTZ_L); //��ȡ���ٶȼƵĵͰ�λ
	*ANGLE_Z = (DataH << 8)|DataL;
}
