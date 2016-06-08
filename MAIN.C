/**********************RC522ʵ�鿪��������************************
*  CPU:STC89C52RC
*  ����:11.0592MHZ
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
    
    //���е������ʾ����4ge�ж�Ԫ�ؾ���ȡ�
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


//		if(RI == 1) {  //����յ�.
//	
//	      RI = 0;      //�����־.
//	
//	      UART_buff = SBUF;  //����.
//	
//		  printf("rec id %x",UART_buff);
//	
//	    }
			

	 		


         status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
         if (status != MI_OK)
         {    
             InitializeSystem( );
		     PcdReset();
		     PcdAntennaOff(); 
		     PcdAntennaOn(); 
		     continue;
         }
			     
			
         status = PcdAnticoll(g_ucTempbuf);//����ײ
         if (status != MI_OK)
         {    continue;    }


        //D55E2AD9
		
//		printf("��ʼ: %d \n",array_cmp(g_ucTempbuf,str));


		////////����Ϊ�����ն˴�ӡ��������////////////////////////
//		if(array_cmp(g_ucTempbuf,str)==0){
//
//			printf("������ ��");
				for(i=0;i<4;i++)
				{
					temp=g_ucTempbuf[i];
					printf("%X-",temp);
					
	        	}
//			printf("\n");
//		}
//		else{
//			printf("���Ŵ��� ����Ŀ����� ��");
//				for(i=0;i<4;i++)
//				{
//					temp=g_ucTempbuf[i];
//					printf("%X-",temp);
//					
//	        	}
//			printf("\n");
//		}

		////////////////////////////////////////////////////////

		LED_GREEN = 0;
	    for(i=0;i<250;i++)//�����һ��Ƶ�ʵ�����
        {
         for(j=0;j<80;j++);
         Speaker=~Speaker;
        }
		delay1(100);
		LED_GREEN = 1;
		delay1(100);
		LED_GREEN = 0;
		delay1(200);
		LED_GREEN = 1;
		
						 		         
		PcdHalt();

    }
}


/////////////////////////////////////////////////////////////////////
//ϵͳ��ʼ��
/////////////////////////////////////////////////////////////////////
void InitializeSystem()
{
/*	P0M1 = 0x0; P0M2 = 0x0;
	P1M1 = 0x0;	P1M2 = 0x0;                      
	P3M1 = 0x0; P3M2 = 0xFF; 
*/	P0 = 0xFF; P1 = 0xFF; P3 = 0xFF;P2 = 0xFF;

 	TMOD=0x21;		   //��T0Ϊ��ʽ1��GATE=1��
	SCON=0x50;
	TH1=0xF4;          //������Ϊ2400bps
	TL1=0xF4;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //����T0�ж�
	TR1=1;			   //������ʱ��
	TI=1;
	EA=1;			   	//�������ж�
	
	ES = 1;
	RI = 1;

 
}




   
  
