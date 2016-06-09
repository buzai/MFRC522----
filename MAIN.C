/**********************RC522实验开发板例程************************
*  CPU:STC89C52RC
*  晶振:11.0592MHZ
------------------------------------------------*/
#include <reg52.h>
#include  <STDIO.H>
#include <string.h>
#include "main.h"
#include "mfrc522.h"

int re_data;
unsigned char Receive[];
unsigned char UART_buff;
bit New_rec = 0, Send_ed = 1, Money = 0;

unsigned char g_ucTempbuf[20];
//unsigned int dcopyArrayInt[10];                       
void delay1(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);	
}  


int array_cmp(unsigned char *s1, unsigned int *s2)
{

    int i;
    unsigned int a,b;
    for(i = 0; i < 4; i ++){

		a = s1[i];
		b = s2[i];
		//printf("i is %d  ----  a is : %x --- b is :%x \n",i,a,b);
        if(a > b) return 1;
        else if(a < b) return -1;
	}
    
    //运行到这里，表示所有4ge判断元素均相等。
    return 0;


}







void main( )
{    
     unsigned char status,i;
	 unsigned int str[4]={0xD5,0x5E,0x2A,0xD9};
	 unsigned int temp,j;
	  
     InitializeSystem( );
     PcdReset();
     PcdAntennaOff(); 
     PcdAntennaOn(); 

     while ( 1 )
     {   


//		if(RI == 1) {  //如果收到.
//	
//	      RI = 0;      //清除标志.
//	
//	      UART_buff = SBUF;  //接收.
//	
//		  printf("rec id %x",UART_buff);
//	
//	    }
			

	 		


         status = PcdRequest(PICC_REQALL, g_ucTempbuf);//寻卡
         if (status != MI_OK)
         {    
             InitializeSystem( );
		     PcdReset();
		     PcdAntennaOff(); 
		     PcdAntennaOn(); 
		     continue;
         }
			     
			
         status = PcdAnticoll(g_ucTempbuf);//防冲撞
         if (status != MI_OK)
         {    continue;    }


        //D55E2AD9
		
//		printf("开始: %d \n",array_cmp(g_ucTempbuf,str));


		////////以下为超级终端打印出的内容////////////////////////
		if(array_cmp(g_ucTempbuf,str)==0){

	   		LED_GREEN = 0;
			delay1(100);
			LED_GREEN = 1;
			delay1(100);
			LED_GREEN = 0;
			delay1(200);
			LED_GREEN = 1;

			printf("卡号是 ：");
				for(i=0;i<4;i++)
				{
					temp=g_ucTempbuf[i];
					printf("%X",temp);
					
	        	}
			printf("\n");
		}
		else{
			printf("卡号错误 错误的卡号是 ：");
				for(i=0;i<4;i++)
				{
					temp=g_ucTempbuf[i];
					printf("%X",temp);
					
	        	}
			printf("\n");
		}

		////////////////////////////////////////////////////////


	    for(i=0;i<250;i++)//先输出一种频率的声音
        {
         for(j=0;j<80;j++);
         Speaker=~Speaker;
        }

		
						 		         
		PcdHalt();

    }
}


/////////////////////////////////////////////////////////////////////
//系统初始化
/////////////////////////////////////////////////////////////////////
void InitializeSystem()
{
/*	P0M1 = 0x0; P0M2 = 0x0;
	P1M1 = 0x0;	P1M2 = 0x0;                      
	P3M1 = 0x0; P3M2 = 0xFF; 
*/	P0 = 0xFF; P1 = 0xFF; P3 = 0xFF;P2 = 0xFF;

 	TMOD=0x21;		   //设T0为方式1，GATE=1；
	SCON=0x50;
	TH1=0xF4;          //波特率为2400bps
	TL1=0xF4;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //允许T0中断
	TR1=1;			   //开启定时器
	TI=1;
	EA=1;			   	//开启总中断
	
	ES = 1;
	RI = 1;

 
}




   
  

