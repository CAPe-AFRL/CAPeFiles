################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/joystickctr.cpp 

OBJS += \
./src/joystickctr.o 

CPP_DEPS += \
./src/joystickctr.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/donald/BlackLib/v3_0/ -I/home/donald/BlackLib/v3_0 -include/home/donald/BlackLib/v3_0/BlackADC/BlackADC.cpp -include/home/donald/BlackLib/v3_0/BlackCore.cpp -include/home/donald/BlackLib/v3_0/BlackGPIO/BlackGPIO.cpp -include/home/donald/BlackLib/v3_0/BlackI2C/BlackI2C.cpp -include/home/donald/BlackLib/v3_0/BlackPWM/BlackPWM.cpp -include/home/donald/BlackLib/v3_0/BlackSPI/BlackSPI.cpp -include/home/donald/BlackLib/v3_0/BlackUART/BlackUART.cpp -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


