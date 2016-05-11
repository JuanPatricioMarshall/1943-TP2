################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Weapons/BasicWeapon.cpp \
../Weapons/BlueBullet.cpp \
../Weapons/Bullet.cpp \
../Weapons/BulletsHandler.cpp \
../Weapons/FiveBulletsWeapon.cpp 

OBJS += \
./Weapons/BasicWeapon.o \
./Weapons/BlueBullet.o \
./Weapons/Bullet.o \
./Weapons/BulletsHandler.o \
./Weapons/FiveBulletsWeapon.o 

CPP_DEPS += \
./Weapons/BasicWeapon.d \
./Weapons/BlueBullet.d \
./Weapons/Bullet.d \
./Weapons/BulletsHandler.d \
./Weapons/FiveBulletsWeapon.d 


# Each subdirectory must supply rules for building sources it contributes
Weapons/%.o: ../Weapons/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0  -lSDL2 -lSDL2_image -lSDL_ttf  -std=c++11  -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


