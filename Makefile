CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = UTrello.exe

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(BUILD_DIR)/main.o \
            $(BUILD_DIR)/handlers.o \
            $(BUILD_DIR)/response.o \
            $(BUILD_DIR)/request.o \
            $(BUILD_DIR)/utilities.o \
            $(BUILD_DIR)/strutils.o \
            $(BUILD_DIR)/server.o \
            $(BUILD_DIR)/route.o \
            $(BUILD_DIR)/template_parser.o \
            $(BUILD_DIR)/System.o \
            $(BUILD_DIR)/HolidayManager.o \
            $(BUILD_DIR)/User.o \
            $(BUILD_DIR)/Date.o \
            $(BUILD_DIR)/DateUtilities.o \
            $(BUILD_DIR)/Event.o \
            $(BUILD_DIR)/Task.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: src/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: src/main.cpp src/System.hpp src/HolidayManager.hpp src/User.hpp src/DateUtilities.hpp src/Event.hpp src/Task.hpp src/Date.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/System.o: src/System.cpp src/System.hpp src/User.hpp src/Event.hpp src/Task.hpp src/Date.hpp src/DateUtilities.hpp src/HolidayManager.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/HolidayManager.o: src/HolidayManager.cpp src/HolidayManager.hpp src/Date.hpp src/DateUtilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/User.o: src/User.cpp src/User.hpp src/Event.hpp src/Task.hpp src/Date.hpp src/DateUtilities.hpp src/HolidayManager.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Date.o: src/Date.cpp src/Date.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/DateUtilities.o: src/DateUtilities.cpp src/DateUtilities.hpp src/Date.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Event.o: src/Event.cpp src/Event.hpp src/DateUtilities.hpp src/Date.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Task.o: src/Task.cpp src/Task.hpp src/Date.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(BUILD_DIR) $(OUT_EXE)
