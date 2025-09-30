#define PIN_LED 7

int PERIOD  = 10000;
//int PERIOD = 1000;
//int PERIOD = 100;
int DUTY = 0;

void set_duty(int duty){
  if(duty<0){duty=0;}
  if(duty>100){duty=100;}
  DUTY = duty;
}

void set_period(int period){
  if(period < 100){period = 100;}
  if(period > 10000){period = 10000;}
  PERIOD = period;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  set_period(PERIOD);
  set_duty(0);
}

void loop() {
  // put your main code here, to run repeatedly:

  // 1초 삼각파: 0→100(0.5s) → 100→0(0.5s), 총 101단계
  const unsigned long step_us = 5000UL; // 5ms = 0.5s/100

  //상승: 0 → 100
  for(int d=0; d<=100; ++d){
    set_duty(d);
    unsigned long remain = step_us;

      if ((unsigned long)PERIOD > step_us) {
      unsigned long on_win  = (unsigned long)step_us * (unsigned long)DUTY / 100UL;
      unsigned long off_win = step_us - on_win;

      if (on_win == 0) {
        digitalWrite(PIN_LED, HIGH);  delayMicroseconds(off_win);
      } else if (off_win == 0) {
        digitalWrite(PIN_LED, LOW);   delayMicroseconds(on_win);
      } else {
        digitalWrite(PIN_LED, LOW);   delayMicroseconds(on_win);   // ON (active-LOW)
        digitalWrite(PIN_LED, HIGH);  delayMicroseconds(off_win);  // OFF
      }
      continue;
    }
    
    while(remain >= (unsigned long)PERIOD){
      unsigned long on_us  = (unsigned long)PERIOD * (unsigned long)DUTY / 100UL;
      unsigned long off_us = (unsigned long)PERIOD - on_us;

      if(on_us==0){
        digitalWrite(PIN_LED, HIGH);
        delayMicroseconds(PERIOD);
      }else if(off_us==0){
        digitalWrite(PIN_LED, LOW);
        delayMicroseconds(PERIOD);
      }else{
        digitalWrite(PIN_LED, LOW);  delayMicroseconds(on_us);   // ON
        digitalWrite(PIN_LED, HIGH); delayMicroseconds(off_us);  // OFF
      }
      remain -= PERIOD;
    }
    if(remain>0) delayMicroseconds(remain);
  }

 
  for(int d=100; d>=0; --d){
    set_duty(d);
    unsigned long remain = step_us;
    while(remain >= (unsigned long)PERIOD){
      unsigned long on_us  = (unsigned long)PERIOD * (unsigned long)DUTY / 100UL;
      unsigned long off_us = (unsigned long)PERIOD - on_us;

      if(on_us==0){
        digitalWrite(PIN_LED, HIGH);
        delayMicroseconds(PERIOD);
      }else if(off_us==0){
        digitalWrite(PIN_LED, LOW);
        delayMicroseconds(PERIOD);
      }else{
        digitalWrite(PIN_LED, LOW);  delayMicroseconds(on_us);
        digitalWrite(PIN_LED, HIGH); delayMicroseconds(off_us);
      }
      remain -= PERIOD;
    }
    if(remain>0) delayMicroseconds(remain);
  }


}
