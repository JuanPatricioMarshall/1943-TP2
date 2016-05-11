################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utils/Parser/ParserCliente.cpp \
../Utils/Parser/ParserNivel.cpp \
../Utils/Parser/ParserServidor.cpp 

OBJS += \
./Utils/Parser/ParserCliente.o \
./Utils/Parser/ParserNivel.o \
./Utils/Parser/ParserServidor.o 

CPP_DEPS += \
./Utils/Parser/ParserCliente.d \
./Utils/Parser/ParserNivel.d \
./Utils/Parser/ParserServidor.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/Parser/%.o: ../Utils/Parser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0  -lSDL2 -lSDL2_image -lSDL_ttf  -std=c++11  -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


