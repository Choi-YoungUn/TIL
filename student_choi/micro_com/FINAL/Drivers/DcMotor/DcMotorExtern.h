//****************** MotorExtern.h **********************

extern typeDcMotor DcMotor1;
extern typeController Controller1;
extern typeBackup   Backup1;

extern void DcMotor1SetDutyPulse(TIM_HandleTypeDef *htim, int16_t pulse);

extern void CalculateMotorRevolution(typeDcMotor *motor);
extern void CalculateWheelRevolution(typeDcMotor *motor);
extern void CalculateMotorRPS(typeDcMotor *motor);
extern void CalculateMotorRPM(typeDcMotor *motor);
extern void CalculateWheelRPS(typeDcMotor *motor);
extern void CalculateWheelRPM(typeDcMotor *motor);


extern void CalculateAxisTurn(typeDcMotor *motor);
extern void CalculateMotorRPS(typeDcMotor *motor);
extern void CalculateMotorRPM(typeDcMotor *motor);
extern void CalculateWheelRPS(typeDcMotor *motor);
extern void CalculateWheelRPM(typeDcMotor *motor);

extern int16_t FloatToInt16Limit(float f, int limit) ;
extern int16_t LimitInt16(int16_t input, int16_t  limit) ;
extern int32_t LimitInt32(int32_t input, int32_t  limit) ;
extern float LimitFloat(float input, float limit) ;
extern int16_t AvoidDeadzone(int16_t u, int16_t requirement_plus, int16_t requirement_minus);

