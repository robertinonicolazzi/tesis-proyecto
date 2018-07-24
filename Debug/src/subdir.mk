################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Jugador.cpp \
../src/Lugar.cpp \
../src/Partido.cpp \
../src/WindowManager.cpp \
../src/WrapperAG.cpp \
../src/WrapperCV.cpp 

OBJS += \
./src/Jugador.o \
./src/Lugar.o \
./src/Partido.o \
./src/WindowManager.o \
./src/WrapperAG.o \
./src/WrapperCV.o 

CPP_DEPS += \
./src/Jugador.d \
./src/Lugar.d \
./src/Partido.d \
./src/WindowManager.d \
./src/WrapperAG.d \
./src/WrapperCV.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/media/rober/DatosLinux/ProyectosEclipse/00_Tesis/include" -O0 -g3 -Wall -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


