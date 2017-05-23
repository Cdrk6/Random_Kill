#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>

using namespace std;
using namespace boost;

class IO {
  public:
	IO();
	int findAllFiles(const string&);
	//SDL_Surface* loadSurface(const string&);
	int loadImages();
	/*int loadData();
	int loadFonts();
	int loadSounds();*/
	static const string S;
	static const string IMG_PATH;
	static const string DAT_PATH;
	static const string FNT_PATH;
	static const string SND_PATH;

  private:
};

//const string S("/");
//const string IMG_PATH("res/images");

#endif /* IO_HPP */
