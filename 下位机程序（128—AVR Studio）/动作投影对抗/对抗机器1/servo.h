#ifndef SERVO_H_
#define SERVO_H_

void SendUart0Byte(unsigned char data);
void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit);
void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity);
void SetServoVelocity(unsigned char id, signed short int velocity);



#endif /* SERVO_H_ */