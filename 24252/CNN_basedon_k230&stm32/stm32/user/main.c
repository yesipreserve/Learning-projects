#include "AllHeader.h"

Serial_k230_Data data; // �������ݽṹ�����,���ڴ洢���յ�������	Define a data structure variable to store the received data
KEY key1={RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_11, GPIO_Mode_IPU};//���尴��1	Define button 1

int main(void)
{	
	uint16_t check_count=1;//��ֹ����...
	Key_Init(key1);
	delay_init();
	OLED_Init();
	OLED_ShowString(1,1,"M1:");
	OLED_ShowString(1,10,"D:");
	OLED_ShowString(2,1,"M2:");
	OLED_ShowString(3,1,"M3:");
	OLED_ShowString(4,1,"M4:");
	Serial_k230_Init(); // ��ʼ��K230���ڽ���
	Serial_Printf("pelase wait...\r\n");
	Servo_init(); // ��ʼ�����
	Jdy23_USART3_Init(9600); // ��ʼ����������

	Motor_Init(); // ��ʼ�����
	Control_Speed(0,0,0,0); // ��ʼ������ٶ�Ϊ0
	mode_flag=1;
	while(1)
	{
		
		Deal_data_real(); // �����ڽ��յ�����
		OLED_ShowSignedNum(1,4,Encoder_Offset[0],4);
		OLED_ShowSignedNum(2,4,-Encoder_Offset[1],4);
		OLED_ShowSignedNum(3,4,-Encoder_Offset[2],4);
		OLED_ShowSignedNum(4,4,Encoder_Offset[3],4);
		if(Key_GetNum(key1)==0)//��ȡ�˿�
				{
					check_count++;
				}
		OLED_ShowSignedNum(1,13,data.depth,3);
		OLED_ShowString(4,13,"8.23");
		Serial_k230_updateData(&data); // ��������
		Serial_k230_toPC(&data); // �����ݷ��͵�PC�ˣ�������
		Servo_process(&data); // ������֪data
		//Control_Speed(100,100,100,100);
		Motor_Bluetooth_Mode(); // ����ң��С��
	}
}
//����һ��time3,����times���ڵ��ԣ�����Ϊtest����
// void Car_Move(void)
// {
// 	static uint8_t state = 0;
// 	switch(state)
// 	{
// 		case 0:
// 			forward(400);
// 		break;
// 		case 1:
// 			backward(400);
// 		break;
// 		case 2:
// 			Left_Turn(400);
// 		break;
// 		case 3:
// 			Move(R_Move,400);
// 		break;
// 		case 4:
// 			Motion_State(OFF);
// 		break;
// 	}
// 	state++;
// 	if(state>4)state=0;
// }