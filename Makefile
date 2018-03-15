CXX 				:= gcc
# references openssl library in a way that allows the compiled code to find the
# library no matter where the program is executed
OPENSSL_INC			:= $(shell pwd)/Hasher/openssl/include
OPENSSL_LIB_DIR 		:= $(shell pwd)/Hasher/openssl/lib
OPENSSL_LIB			:= crypto
CXXFLAGS			:= -I$(OPENSSL_INC) -L$(OPENSSL_LIB_DIR) -l$(OPENSSL_LIB) -Wl,-rpath=$(OPENSSL_LIB_DIR)
GNU99				:= -std=gnu99
.PHONY: output invalid omission test CosmicRay

all: | output invalid omission test CosmicRay

output:
	$(CXX) $(GNU99) $(CXXFLAGS) -o output output.c

invalid:
	$(CXX) $(GNU99) $(CXXFLAGS) -o invalid invalid.c

omission:
	$(CXX) $(GNU99) $(CXXFLAGS) -o omission omission.c

test:
	$(CXX) $(GNU99) -o test test.c

CosmicRay:
	$(CXX) -o CosmicRay CosmicRay.c

clean:
	@rm -rf all

%.o : %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 
