################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../figure/circle.c \
../figure/point.c 

OBJS += \
./figure/circle.o \
./figure/point.o 

C_DEPS += \
./figure/circle.d \
./figure/point.d 


# Each subdirectory must supply rules for building sources it contributes
figure/%.o: ../figure/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/lua/Trabalho/Curso c/eclipse_workspace/Aula 3/ooc_base" -I"/home/lua/Trabalho/Curso c/eclipse_workspace/Aula 3/figure" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


