CXX 				:= gcc
# references openssl library in a way that allows the compiled code to find the
# library no matter where the program is executed
OPENSSL_INC			:= $(shell pwd)/Hasher/openssl/include
OPENSSL_LIB_DIR 		:= $(shell pwd)/Hasher/openssl/lib
OPENSSL_LIB			:= crypto
CXXFLAGS			:= -I$(OPENSSL_INC) -L$(OPENSSL_LIB_DIR) -l$(OPENSSL_LIB) -Wl,-rpath=$(OPENSSL_LIB_DIR)

.PHONY: output invalid omission test CosmicRay

all: | output invalid omission test CosmicRay

output:
	$(CXX) $(CXXFLAGS) -o output output.c

invalid:
	$(CXX) $(CXXFLAGS) -o invalid invalid.c

omission:
	$(CXX) $(CXXFLAGS) -o omission omission.c

test:
	$(CXX) -o test test.c

CosmicRay:
	$(CXX) -o CosmicRay CosmicRay.c

clean:
	@rm -rf all

%.o : %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 
