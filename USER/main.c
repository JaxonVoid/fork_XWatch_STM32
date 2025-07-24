#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "OLED.h"
#include "key.h"
#include "menu.h"
#include "rtc.h"
//#include "oled_pic.h"

// change test

#define LED_ON   0; //led����
#define LED_OFF  1; //led�ر�

void (*current_operation_index)();
unsigned char key;
unsigned char func_index = 0; //�������ʱ���ڳ��������ֵ
unsigned char last_index = 127;
unsigned char last_sec = 60;

//����ҳ�����
void Watch_Show(void)
{
	extern unsigned char func_index;
	extern unsigned char last_sec;
	
	if((func_index == 0)&&(calendar.sec != last_sec)){
		OLED_ShowNum(34+0 ,2,calendar.w_year ,4,12);
		OLED_ShowNum(34+30,2,calendar.w_month,2,12);
		OLED_ShowNum(34+48,2,calendar.w_date ,2,12);
		
		OLED_ShowNum(32+0 ,4,calendar.hour,2,16);
		OLED_ShowNum(32+24,4,calendar.min ,2,16);
		OLED_ShowNum(32+48,4,calendar.sec ,2,16);
	}
}

int main(void)
{	
    delay_init();
    LED_Init();
	OLED_Init();
	KEY_Init();
	RTC_Init();
	
//	RTC_Set(2023,2,3,15,22,40);
	
	OLED_Fill_Fast(0xff); //����ɫ
	delay_ms(200);
	OLED_Fill_Fast(0x00); //����

    while(1){
		key = KEY_Scan(0);
		Menu_Show(key);
		
		Watch_Show(); //���̸���
		
		LED1=~LED1;
		LED0 = LED_ON;
    }

}
