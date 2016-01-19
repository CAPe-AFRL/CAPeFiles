################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sickLaser.cpp 

OBJS += \
./src/sickLaser.o 

CPP_DEPS += \
./src/sickLaser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/donald/BlackLib/v3_0 -I/home/donald/library/network/ -I/home/donald/library/ -include/home/donald/library/network/SocketClient.cpp -include/home/donald/library/network/SocketClient.h -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


