################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bmp.cpp \
../cgvCamera.cpp \
../cgvColor.cpp \
../cgvInterface.cpp \
../cgvLight.cpp \
../cgvMaterial.cpp \
../cgvPoint3D.cpp \
../cgvScene3D.cpp \
../cgvTexture.cpp \
../pr4.cpp 

OBJS += \
./bmp.o \
./cgvCamera.o \
./cgvColor.o \
./cgvInterface.o \
./cgvLight.o \
./cgvMaterial.o \
./cgvPoint3D.o \
./cgvScene3D.o \
./cgvTexture.o \
./pr4.o 

CPP_DEPS += \
./bmp.d \
./cgvCamera.d \
./cgvColor.d \
./cgvInterface.d \
./cgvLight.d \
./cgvMaterial.d \
./cgvPoint3D.d \
./cgvScene3D.d \
./cgvTexture.d \
./pr4.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


