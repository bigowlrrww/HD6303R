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
TARGET-libMC6803E = libMC6803E.a
OBJS-libMC6803E   = $(LIBDIR)/Image.o \
					$(LIBDIR)/MC6803E_ALU.o \
					$(LIBDIR)/MC6803E_Memory.o \
					$(LIBDIR)/MC6803E_Core.o

# Files to copy
OBJS-copyLocal = 

# Test program
TARGET-test = MC6803_UNIT
OBJS-test   = MC6803_UNIT.o \
			  Tests.o

all: $(TARGET-libMC6803E) $(TARGET-test)

# Build static library
$(TARGET-libMC6803E): $(OBJS-libMC6803E)
	$(AR) rcs $@ $(OBJS-libMC6803E)
	$(CP) $(LIBDIR)\libMC6803E.h libMC6803E.h
	$(CP) $(LIBDIR)\Image.h Image.h
	$(CP) $(LIBDIR)\ROM.6803 ROM.6803

# Compile library object files
$(LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build test program
$(TARGET-test): $(OBJS-test) $(TARGET-libMC6803E)
	$(CC) $(CFLAGS) $(OBJS-test) $(TARGET-libMC6803E) -o $@

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	if exist *.o del /Q *.o
	if exist *.a del /Q *.a
	if exist $(TARGET-test).exe del /Q $(TARGET-test).exe
	if exist libMC6803E.h del /Q libMC6803E.h