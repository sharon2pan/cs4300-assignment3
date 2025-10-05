OBJS = CameraViews.o View.o Controller.o Model.o
INCLUDES = -I../include
LIBS = -L../lib
LDFLAGS = -lglad -lglfw3
CFLAGS = -g -std=c++11
PROGRAM = CameraViews


ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    LDFLAGS += -lopengl32 -lgdi32
    PROGRAM :=$(addsuffix .exe,$(PROGRAM))
    COMPILER = g++
else ifeq ($(shell uname -s),Darwin)     # is MACOSX
    LDFLAGS += -framework Cocoa -framework OpenGL -framework IOKit
    COMPILER = g++
endif

CameraViews: clean $(OBJS)
	$(COMPILER) -o $(PROGRAM) $(OBJS) $(LIBS) $(LDFLAGS)

CameraViews.o: CameraViews.cpp
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c CameraViews.cpp

View.o: View.cpp View.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c View.cpp	

Controller.o: Controller.cpp Controller.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c Controller.cpp	

Model.o: Model.cpp Model.h
	$(COMPILER) $(INCLUDES) $(CFLAGS) -c Model.cpp		
	
RM = rm	-f
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    RM := del
endif
    
clean:
	$(RM) $(OBJS) $(PROGRAM)
    