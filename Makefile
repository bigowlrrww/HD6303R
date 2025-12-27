CC      = gcc
AR      = ar
CFLAGS  = -I. -O0 -g
RM      = rm -f

# Library
TARGET-libHD6303R = libHD6303R.a
OBJS-libHD6303R   = Image.o HD6303R_ALU.o HD6303R_Memory.o HD6303R_Core.o

# Test program
TARGET-test = HD6303_TEST
OBJS-test   = HD6303_TEST.o

library: $(TARGET-libHD6303R)

all: $(TARGET-libHD6303R) $(TARGET-test)

# Build static library
$(TARGET-libHD6303R): $(OBJS-libHD6303R)
	$(AR) rcs $@ $(OBJS-libHD6303R)

# Build test program
$(TARGET-test): $(OBJS-test) $(TARGET-libHD6303R)
	$(CC) $(CFLAGS) $(OBJS-test) $(TARGET-libHD6303R) -o $@

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	if exist *.o del /Q *.o
	if exist *.a del /Q *.a
	if exist $(TARGET-test).exe del /Q $(TARGET-test).exe