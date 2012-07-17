CXX=g++
RELEASE=-Wall -std=c++0x -Wno-sign-compare -fpermissive
INCLUDEDIR=-I /usr/local/include/SDL2/
LIBDIR=-L /usr/local/lib/
LINKLIB=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf 
CFLAGS=$(RELEASE) -c $(INCLUDEDIR)
LFLAGS=$(RELEASE) $(INCLUDEDIR) $(LIBDIR) $(LINKLIB)
SRCPATH=LPCGame/src/
OBJPATH=LPCGame/obj/
EXEC=Debug/game
DEPS=$(SRCPATH)rect.h $(SRCPATH)vectors.h $(SRCPATH)rect.h $(SRCPATH)objectpool.h
OBJS=$(OBJPATH)math.o $(OBJPATH)timer.o $(OBJPATH)debugger.o $(OBJPATH)physics.o $(OBJPATH)image.o \
	$(OBJPATH)window.o $(OBJPATH)gameobject.o $(OBJPATH)player.o $(OBJPATH)npc.o $(OBJPATH)button.o \
	$(OBJPATH)gameobjectmanager.o $(OBJPATH)input.o $(OBJPATH)map.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)
%.h:
	echo making header file

$(EXEC): $(SRCPATH)main.cpp $(OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)

$(OBJPATH)map.o: $(SRCPATH)map.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)input.o: $(SRCPATH)input.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)gameobjectmanager.o: $(SRCPATH)gameobjectmanager.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)button.o: $(SRCPATH)button.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)npc.o: $(SRCPATH)npc.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)player.o: $(SRCPATH)player.cpp 
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)gameobject.o: $(SRCPATH)gameobject.cpp 
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)window.o: $(SRCPATH)window.cpp 
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)image.o: $(SRCPATH)image.cpp 
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)physics.o: $(SRCPATH)physics.cpp 
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)debugger.o: $(SRCPATH)debugger.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)timer.o: $(SRCPATH)timer.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJPATH)math.o: $(SRCPATH)math.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJPATH)*