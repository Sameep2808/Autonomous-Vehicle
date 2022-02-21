#include "mbed.h"
#define PWM_FREQ 500
#define PWM_WIDTH_H 20
#define PWM_WIDTH_M 15
#define PWM_WIDTH_L 12
/* Activate on board LEDs */
Serial pc(USBTX, USBRX);
int a=0;float s=0,e=0,af=0.3,c=0;
char ch;
DigitalIn torch(D4);
DigitalOut pulse(D0); // Stepper
DigitalOut dir(D1); // Stepper Direction
DigitalOut bd(D2); // Brake Direction
DigitalOut bp(D3); // Brake Pulse
DigitalOut myled1(LED2); // LED to test
PwmOut pwm(D5); // PWM for chassis motor
DigitalOut myled2(LED1);
DigitalOut myled3(LED3);
/* Function prototype */

void gos(float s)
{
    pwm.write(s);
    wait(0.0001);
    pwm.write(0);
    wait(0.0001);
    }
    
void gom(float s)
{
    pwm.write(s);
    wait(0.00005);
    pwm.write(0);
    wait(0.00005);
    }

    
void con(float c)
{
    for(float i=0;i<0.2;i=i+0.0005)
         {
             go(c);
             wait(0.009);
             }
    
    }    
    
float acc(int e,int af)
{
    pc.printf("accccc");
    for(float i=e;i<af;i=i+0.0002)
         {
             go(i);
             wait(0.009);
             }
             return af;
    }
 
float dacc(int e,int af)
{
    pc.printf("dddddaccccc");
    for(float i=e;i>af;i=i-0.0002)
         {
             go(i);
             wait(0.009);
             }
            return af;
    }    
    
void br()
{
    pwm.pulsewidth_ms(0);
    bd=1;
    bp=1;
    wait(2);
    bd=0;
    wait(0.5);
    bp=0;
}
        
void right()
{
    dir=0;
    for(int i=0;i<1000;i++)
    {
        pulse=1;
        //myled = 1; // LED is ON
        wait(0.0003);
        pulse=0;
        // myled = 0; // LED is ON
        wait(0.0003);
    } 
        
    
}

void left()
{
    dir=1;
    for(int i=0;i<1000;i++)
    {
        pulse=1;
        //myled = 1; // LED is ON
        wait(0.0003);
        pulse=0;
        // myled = 0; // LED is ON
        wait(0.0003);
    } 
}

int main()
{
    e=0;
    while(1)
    {
       
       if(pc.readable()==1)
       {
        pc.printf("INSERT");
        pc.scanf("%c",&ch);
        pc.printf("%c",ch);
       
       switch(ch)
       {
           
           case 'A':
           if(e!=0){
            e=dacc(e,0);}
           con(0);
           myled1=0;
           myled2=0;
           myled3=0; 
           break;
           
           case 'B':
           if(e<0.1){
           e=acc(e,0.1);}
           else if(e>0.1){
           e=dacc(e,0.1);}
           con(0.1);
           myled1=0;
           myled2=1;
           myled3=1;       
           break;
           
           
           case 'C':
           if(e<0.3){
           e=acc(e,0.3);}
           else if(e>0.3){
           e=dacc(e,0.3);}
           con(0.3);
           myled1=1;
           myled2=0;
           myled3=1;
           break;
           
           case 'D':
           if(e!=0){
           e=dacc(e,0);}
           con(0);
           myled1=1;
           myled2=1;
           myled3=0;
           break;
           
           case 'E':
           if(e!=0){
           e=dacc(e,0);}
           con(0);
           myled1=1;
           myled2=0;
           myled3=0;
           pc.printf("Right");
           right();
           ch = 'A';
           break;
           
           case 'F':
           if(e!=0){
           e=dacc(e,0);}
           con(0);
           myled1=0;
           myled2=0;
           myled3=1;
           pc.printf("Left");
           left();
           ch = 'A';
           break;
           
           case 'G':
           if(e!=0){
           e=dacc(e,0);}
           con(0);
           br();
           pc.printf("Break");
           break;
       }
       }
       pc.printf("%f",s);
       wait(0.001);
       
    }
     
}

