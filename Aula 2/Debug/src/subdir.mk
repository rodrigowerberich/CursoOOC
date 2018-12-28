################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/circle.c \
../src/main.c \
../src/ooc.c \
../src/point.c 

OBJS += \
./src/circle.o \
./src/main.o \
./src/ooc.o \
./src/point.o 

C_DEPS += \
./src/circle.d \
./src/main.d \
./src/ooc.d \
./src/point.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/lua/Trabalho/Curso c/eclipse_workspace/Aula 2/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


