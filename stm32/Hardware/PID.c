//float kp=1.2;
//float ki=0.20;
//float kd=8	;

float kp=1.6;
float ki=0;
float kd=3.2;

float pid_cal(int input,int measure)
{
	int limit =60;
	static int err_last ,integral;
	int err=input-measure;
	integral+=err;
	if(integral>limit)integral=limit;
	if(integral<-limit)integral=-limit;
	float output=kp*err+ki*integral+kd*(err-err_last);
	if(output>limit)output=limit;
	if(output<-limit)output=-limit;
	err_last=err;
	return output;
}
