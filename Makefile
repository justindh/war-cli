# the compiler: gcc for C program, define as g++ for C++
  CC = cl

  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -g -Wall

  # The build target 
  TARGET = war

  all: $(TARGET)

  $(TARGET): $(TARGET).cpp
  $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp GameManager.cpp Card.cpp Player.cpp

  clean:
    $(RM) $(TARGET)