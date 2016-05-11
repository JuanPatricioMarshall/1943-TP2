################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Server/AlanTuring.cpp \
../Server/DrawMessagesPacker.cpp \
../Server/MessageFactory.cpp \
../Server/server.cpp 

OBJS += \
./Server/AlanTuring.o \
./Server/DrawMessagesPacker.o \
./Server/MessageFactory.o \
./Server/server.o 

CPP_DEPS += \
./Server/AlanTuring.d \
./Server/DrawMessagesPacker.d \
./Server/MessageFactory.d \
./Server/server.d 


# Each subdirectory must supply rules for building sources it contributes
Server/%.o: ../Server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0  -lSDL2 -lSDL2_image -lSDL_ttf  -std=c++11  -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


