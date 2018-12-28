################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc_base/ooc.c 

OBJS += \
./ooc_base/ooc.o 

C_DEPS += \
./ooc_base/ooc.d 


# Each subdirectory must supply rules for building sources it contributes
ooc_base/%.o: ../ooc_base/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/lua/Trabalho/Curso c/eclipse_workspace/Aula 3/ooc_base" -I"/home/lua/Trabalho/Curso c/eclipse_workspace/Aula 3/figure" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


