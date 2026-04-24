
all: 
	g++ -c main.cpp -D SFML_STATIC -DAL_LIBTYPE_STATIC -I"./required/SFML-2.5.1/include" -o main.o
	g++ main.o -o TaxiGame.exe -L"./required/SFML-2.5.1/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lopenal32 -lsfml-network-s -lsfml-system-s -lvorbisfile -lvorbisenc -lvorbis -logg -lflac -lws2_32 -lgdi32 -lwinmm -lopengl32 -lfreetype



