#include "msp430f5529.h"

unsigned char i = 0;
unsigned char disp = 0;
unsigned char pov[2][84]= {
  {0x35,0x01,0x31,0x05,0x05,0x05,0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x11,0x11,0x21,0x11,0x11,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x31,0x05,0x05,0x05,0x31,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x11,0x01,0x21,0x11,0x11,0x21},//for p2
  {0x3c,0x00,0x20,0x30,0x28,0x24,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x10,0x00,0x04,0x00,0x10,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x24,0x24,0x24,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x10,0x10,0x1c,0x10,0x10,0x0c} //for p1
	};  

void delay_ms(unsigned int ms )			// MS delay function
{
	unsigned int i;
	for (i = 0; i<= ms; i++)
   	__delay_cycles(300);
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; /* Good dog, no barking */
  
   /* Digital out to a LED */
  P2DIR |= BIT0;
  P2DIR |= BIT2;
  P2DIR |= BIT4;
  P2DIR |= BIT5;
  P1DIR |= BIT2;
  P1DIR |= BIT3;
  P1DIR |= BIT4;
  P1DIR |= BIT5;
  //P6DIR |= BIT0;
  //P6DIR |= BIT1;
  //P6DIR |= BIT2;
  //P6DIR |= BIT3;
  //P6DIR |= BIT4;
  //P7DIR |= BIT0;
  //P7DIR |= BIT0;
  //P3DIR |= BIT6;
  //P3DIR |= BIT5;
  //P2OUT &= 0x00;
  //P1OUT &= 0x00;

  TA1CCTL0 = CCIE;  
  TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
  TA1CCR0 = 20;       //smaller, faster initial=32768
 
  __bis_SR_register(GIE); /* Enable maskable interrupts */

  while(1) { /* CPU does nothing and thus no harm */ 
  }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    /*P2OUT ^= BIT0;
    P2OUT ^= BIT2;
    P2OUT ^= BIT4;
    P2OUT ^= BIT5;
    P1OUT ^= BIT2;
    P1OUT ^= BIT3;
    P1OUT ^= BIT4;
    P1OUT ^= BIT5;*/
    
  disp^=1;
  if(disp!=0)
  {  
	  if(i==84)
             {
		i=0;
              //__delay_cycles(1000);          //delay for backloop 1 sec
             }   
	  P2OUT|=pov[0][i];
          P1OUT|=pov[1][i];
          delay_ms(1);
	  i++;
  }
  else
  {
	P2OUT&=0x00;
        P1OUT&=0x00;
  }
}

/*https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/297841*/