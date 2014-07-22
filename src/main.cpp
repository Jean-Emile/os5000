#include "compassCore_SR.h"


int main(int argc,char **argv){
	Compass *compass = new Compass("/dev/ttyUSB0",19200,15,1000);

	while(1){

		compass->GetData();

		std::cout << compass->yaw << " " << compass->roll << " "<< compass->pitch << std::endl;
		usleep(10000);
	}
}
