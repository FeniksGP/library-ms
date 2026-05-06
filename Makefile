MODE := debug
OPTIMIZATION_LEVEL := 2
EXE := .x

CXXFLAGS := 
CXX := g++
LD := g++
LDFLAGS := 

#Directories
BUILD_DIR := ./bin
OBJ_DIR := ./obj
SOURCE_DIR := ./source
LIB_DIR := ./lib



ifeq ($(MODE),debug)
  OPTIMIZATION_LEVEL := 0
  CXXFLAGS += -o$(OPTIMIZATION_LEVEL) -Wall -pedantic -Wextra
else
  CXXFLAGS += -o$(OPTIMIZATION_LEVEL)
endif

$(OBJ_DIR)/cli_tools.o: $(SOURCE_DIR)/cli_tools.cpp $(SOURCE_DIR)/cli_tools.h $(SOURCE_DIR)/library_sys/library.h $(SOURCE_DIR)/library_sys/users.h $(SOURCE_DIR)/data.h \
$(SOURCE_DIR)/library_sys/database.h $(SOURCE_DIR)/entity/book.h $(SOURCE_DIR)/entity/entity.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/data.o: $(SOURCE_DIR)/data.cpp $(SOURCE_DIR)/data.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/database.o: $(SOURCE_DIR)/library_sys/database.cpp $(SOURCE_DIR)/library_sys/database.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/library.o: $(SOURCE_DIR)/library_sys/library.cpp $(SOURCE_DIR)/library_sys/library.h $(SOURCE_DIR)/library_sys/database.h $(SOURCE_DIR)/data.h  \
$(SOURCE_DIR)/entity/book.h $(SOURCE_DIR)/entity/entity.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/users.o: $(SOURCE_DIR)/library_sys/users.cpp $(SOURCE_DIR)/library_sys/users.h $(SOURCE_DIR)/library_sys/database.h $(SOURCE_DIR)/data.h \
$(SOURCE_DIR)/entity/book.h $(SOURCE_DIR)/entity/user.h $(SOURCE_DIR)/library_sys/library.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/book.o: $(SOURCE_DIR)/entity/book.cpp $(SOURCE_DIR)/entity/book.h $(SOURCE_DIR)/entity/entity.h $(SOURCE_DIR)/library_sys/users.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/entity.o: $(SOURCE_DIR)/entity/entity.cpp $(SOURCE_DIR)/entity/entity.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/user.o: $(SOURCE_DIR)/entity/user.cpp $(SOURCE_DIR)/entity/user.h $(SOURCE_DIR)/entity/entity.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/library-ms.o: $(SOURCE_DIR)/library-ms.cpp $(SOURCE_DIR)/cli_tools.h $(SOURCE_DIR)/library_sys/library.h $(SOURCE_DIR)/library_sys/users.h \
$(SOURCE_DIR)/library_sys.h $(SOURCE_DIR)/data.h $(SOURCE_DIR)/library_sys/database.h $(SOURCE_DIR)/entity/book.h $(SOURCE_DIR)/entity/entity.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(BUILD_DIR)/library-ms$(EXE): $(OBJ_DIR)/library-ms.o $(OBJ_DIR)/cli_tools.o $(OBJ_DIR)/book.o $(OBJ_DIR)/database.o $(OBJ_DIR)/library.o \
	$(OBJ_DIR)/users.o $(OBJ_DIR)/data.o $(OBJ_DIR)/entity.o $(OBJ_DIR)/user.o
	$(LD) $(LDFLAGS) -o $@ $+

#Targets
.PHONY: build clean help info

build: $(BUILD_DIR)/library-ms$(EXE)

clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*

