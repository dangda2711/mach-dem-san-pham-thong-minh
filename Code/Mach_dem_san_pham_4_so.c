 #include "AT89X51.h"
//const unsigned char code ma7doan[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1E,0x01,0x09,0xFF};
const char ma7doan[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
#define p_led P0
sbit l1 = P2^7;
sbit l2 = P2^6;
sbit l3 = P2^5;
sbit l4 = P2^4;
unsigned char lan_quet=0;
unsigned char dem_ton_tof=0;
unsigned int so_sp;
unsigned int so_du;
sbit cb_h = P1^0; // Cam bien hang
bit ncb_h=0;
sbit luong= P1^1;// Thong bao khi so san pham là boi so cua 10
sbit day= P1^2; // Thong bao chan 9999
sbit kd = P2^2; // nut khoi tang
sbit du = P2^1; // nut giam
sbit re = P2^0; // nut reset

bit PN = 0;
void quet_nut();

//======================================== 
void delay_ms(unsigned time) // ham trao tre ms
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<125;j++)
	{
	}
}
#define t_on 10
#define t_of 10
void quet_led(unsigned int so)
{
	dem_ton_tof++;
	if(dem_ton_tof==t_of)
	{
		lan_quet++;
		if(lan_quet==1)
		{
			p_led=(ma7doan[so/1000%10]);
			l1=0;
		}
		if(lan_quet==2)
		{
			p_led=(ma7doan[so/100%10]);
			l2=0;
		}
		if(lan_quet==3)
		{
			p_led=(ma7doan[so/10%10]);
			l3=0;
		}
		if(lan_quet==4)
		{
			p_led=(ma7doan[so/1%10]);								 
			l4=0;
			lan_quet=0;
		}
	}
	else
	{
		if(dem_ton_tof==t_on+t_of)
		{
			l1=l2=l3=l4=1;
			p_led=0xff;		    
			dem_ton_tof=0;
		}	
	}
}
//======================================== 
void chay()
{
	quet_led(so_sp);
	//---------------------------------------- 
	{
		if(cb_h==1)
		{
			ncb_h=1; // bao co vat can chan ngan
		}
		if(cb_h==0&&ncb_h==1)
		{
			ncb_h=0; // bao vat da di ngan qua
			so_sp++;
			if(so_sp>9999)
			{
				so_sp=0;
			}
			if(so_sp==9999)
			{
				day=1;
			}
			else
			{
				day=0;
			}
			so_du= so_sp%10;
			if(so_du==0){
				luong=1;
			}
			else
			{
				luong=0;
      }
		}
	}
	
}

//======================================== 
void main()			//chuong trinh chinh
{
	luong=0;
	so_sp=0;
	day=0;
	while(1) // vong lap vo han
	{
		
		chay();
		quet_nut();
	}
}
//======================================== 
void quet_nut()
{
	if(PN==1) // KIEM TRA KHONG NHAN NUT KHI PN = 0
	{
		if(kd==0)
		{
			PN =0; // BAO DA NHAN NUT
			so_sp++;
			if(so_sp>9999)
			{
				so_sp=0;
			}
		}
		if(du==0) // KHI NUT NHAN CHE DO 2 DUOC NHAN
		{
			PN = 0; // BAO DA NHAN NUT
			so_sp--;
			if(so_sp>9999)
			{
				so_sp=9999;
			}
		}
		if(re==0)
		{
			PN = 0; // BAO DA NHAN NUT
			so_sp=0;
		}
		}
	else // KIEM TRA NUT KHONG NHAN
	{
		if(kd==1&&du==1&&re==1)
			PN=1; // CHO PHEP NHAN PHIM TIEP THEO
	}
	
}
//======================================== 