/*************************************************/
/* ���C���g���[�X�v���O����(C����)   */
/* ������     2004.8.24     by AND     */
/*************************************************/
#include <pic.h>
__CONFIG(0xFFFA); /* �����ݒ� CP:OFF,PT:OFF,WT:OFF,HS */

wait00(short k)
{
/* ��(k�~0.01)�~���b �̃E�F�C�g(k�~0.01msec wait)*/
	short i;
	short j; /* 16 Bit �ϐ��̐錾 */
   	for(j=0;j<k;j++){ /* (k�~3)��̌J��Ԃ� */
		for(i=0;i<3;i++){
		}
	
	}
	return 0;
}

int left_down(void){
	PORTA=0x03; /* both motor on */
	wait00(3);   /* 0.03msec wait */
	PORTA=0x01; /* right motor on */
	wait00(18);   /* 0.18msec wait */
	PORTA=0x00; /* both motor off */
	wait00(79);   /* 0.79msec wait */
}

int small_left_down(void){
	PORTA=0x03; /* both motor on */
	wait00(5);   /* 0.05msec wait */
	PORTA=0x01; /* right motor on */
	wait00(12);   /* 0.12msec wait */
	PORTA=0x00; /* both motor off */
	wait00(83);   /* 0.83msec wait */
}

int right_down(void){
	PORTA=0x03; /* both motor on */
	wait00(3);   /* 0.03msec wait */
	PORTA=0x02; /* left motor on */
	wait00(18);   /* 0.18msec wait */
	PORTA=0x00; /* both motor off */
	wait00(79);   /* 0.79msec wait */
}

int small_right_down(void){
	PORTA=0x03; /* both motor on */
	wait00(5);   /* 0.05msec wait */
	PORTA=0x02; /* left motor on */
	wait00(12);   /* 0.12msec wait */
	PORTA=0x00; /* both motor off */
	wait00(83);   /* 0.83msec wait */
}

int straight(void){
	PORTA=0x03; /* both motor on */
	wait00(20);   /* 0.20msec wait */
	PORTA=0x00; /* both motor off */
	wait00(80);   /* 0.80msec wait */
}

int led_sens(void)
{
	RB3=RB0; /* �Z���T���́�LED�\�� */
	RB4=RB1; /* �Z���T���́�LED�\�� */
	RB5=RB2; /* �Z���T���́�LED�\�� */
}

int main(void)
{
	TRISA = 0xFC; /* A 0,1:output, 2,3,4:input */
	TRISB = 0xC7; /* B0,1,2:input, B3,4,5:LEDoutput, other bits input */
	PORTB = 0;    /* PORTB clear */
	PORTA = 0;    /* PORTA clear */
	while(RA4==1){
		led_sens();
	}
	while(1){/* �������[�v */
		led_sens();
		if(RB0==0 && RB1==0 && RB2==1){ /* Black Black White */
			small_left_down();           /* turn left a little */
			}
		else if(RB0==0 && RB1==1 && RB2==1){ /* Black White White */
			left_down();                 /* turn left */
			}
		else if(RB0==1 && RB1==0 && RB2==0){ /* White Black Black */
			small_right_down();          /* turn right a little */
		}
		else if(RB0==1 && RB1==1 && RB2==0){ /* White White Black */
			right_down();                /* turn right */
		}
		else{                                /* The other case */
			straight();                  /* go to straight */
		}
	}	
}