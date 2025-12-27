CC      = gcc
AR      = ar
CFLAGS  = -I. -O0 -g
RM      = rm -f

ifeq ($(OS),Windows_NT)
    CP = copy /Y
else
    CP = cp
endif

LIBDIR = ..

# Library
TARGET-libHD6303R = libHD6303R.a
OBJS-libHD6303R   = $(LIBDIR)/HD6303R_ALU.o \
					$(LIBDIR)/HD6303R_Memory.o \
					$(LIBDIR)/HD6303R_Core.o

# Test program
TARGET-test = HD6303_UNIT
OBJS-test   = HD6303_UNIT.o \
			  Tests.o \
			  ItemList.o

all: $(TARGET-libHD6303R) $(TARGET-test)

# Build static library
$(TARGET-libHD6303R): $(OBJS-libHD6303R) 
	$(CP) $(LIBDIR)\libHD6303R.h libHD6303R.h
	$(CP) $(LIBDIR)\ROM.6803 ROM.6803
	$(AR) rcs $@ $(OBJS-libHD6303R)

# Compile library object files
$(LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

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
	if exist libHD6303R.h del /Q libHD6303R.h