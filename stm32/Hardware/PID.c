float kp=1;
float ki=0.1;
float kd=1.5;

float pid_cal(int input,int measure)
{
	int limit =100;
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
