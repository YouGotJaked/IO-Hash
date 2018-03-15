CXX 				:= gcc
# references openssl library in a way that allows the compiled code to find the
# library no matter where the program is executed
OPENSSL_INC			:= $(shell pwd)/openssl/include
OPENSSL_LIB_DIR 	:= $(shell pwd)/openssl/lib
OPENSSL_LIB			:= crypto
CXXFLAGS			:= -I$(OPENSSL_INC) -L$(OPENSSL_LIB_DIR) -l$(OPENSSL_LIB) -Wl,-rpath=$(OPENSSL_LIB_DIR)
OBJ_DIR				:= obj/
BUILD_DIR			:= build/
VPATH				:= $(OBJ_DIR)
TARGET				:= Hasher

.PHONY: example

all: | lib example

lib: $(TARGET).o
	@mkdir -p $(BUILD_DIR)
	ar rcs $(BUILD_DIR)$(TARGET).a $(OBJ_DIR)$(TARGET).o

example:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)example example.c $(BUILD_DIR)$(TARGET).a

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(OBJ_DIR)

%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $< 
