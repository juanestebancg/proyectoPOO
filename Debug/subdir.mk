################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Controlador.cpp \
../Main.cpp \
../Programa.cpp \
../Subversion.cpp \
../Version.cpp \
../Vista.cpp 

OBJS += \
./Controlador.o \
./Main.o \
./Programa.o \
./Subversion.o \
./Version.o \
./Vista.o 

CPP_DEPS += \
./Controlador.d \
./Main.d \
./Programa.d \
./Subversion.d \
./Version.d \
./Vista.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


