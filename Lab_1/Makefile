CPPFLAGS = -std=c++11
all: main.exe

main.exe: openningMessage.o QA.o main.o
	g++ -o $@ $(CPPFLAGS) openningMessage.o QA.o main.o


%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

clean:
	del  *.o *.exe
# On Windows, use: del *.o *.exe
# On Linux or MacOS, use: rm -f *.o *.exe

# Utility 'makedepend' finds the .h dependencies automatically
depend:
	path\to\UnxUtils\usr\local\wbin\makedepend -o.o $(SRCS)
