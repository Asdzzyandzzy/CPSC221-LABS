EXE = pa3
EXEStats = teststats
EXEThreetree = testthreetree
OBJS  = pa3.o PNG.o RGBAPixel.o lodepng.o threetree.o threetree-given.o stats.o
OBJS_S = teststats.o PNG.o RGBAPixel.o lodepng.o stats.o
OBJS_Q = testthreetree.o PNG.o RGBAPixel.o lodepng.o threetree.o threetree-given.o stats.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -Og -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm

all : pa3 teststats testthreetree

$(EXE) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

$(EXEStats) : $(OBJS_S)
	$(LD) $(OBJS_S) $(LDFLAGS) -o $(EXEStats)

$(EXEThreetree) : $(OBJS_Q)
	$(LD) $(OBJS_Q) $(LDFLAGS) -o $(EXEThreetree)

pa3.o : pa3.cpp threetree.h threetree-private.h cs221util/PNG.h cs221util/RGBAPixel.h stats.h stats-private.h
	$(CXX) $(CXXFLAGS) pa3.cpp -o $@

teststats.o : teststats.cpp cs221util/PNG.h cs221util/RGBAPixel.h stats.h stats-private.h
	$(CXX) $(CXXFLAGS) teststats.cpp -o $@

testthreetree.o : testthreetree.cpp threetree.h threetree-private.h cs221util/PNG.h cs221util/RGBAPixel.h stats.h stats-private.h
	$(CXX) $(CXXFLAGS) testthreetree.cpp -o $@

threetree.o : threetree.cpp threetree.h threetree-private.h stats.h stats-private.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) threetree.cpp -o $@

threetree-given.o : threetree-given.cpp threetree.h stats.h stats-private.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) threetree-given.cpp -o $@

stats.o : stats.cpp stats.h stats-private.h cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

clean :
	-rm -f *.o $(EXE) $(EXEStats) $(EXEThreetree)
