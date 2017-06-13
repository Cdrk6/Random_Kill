#ifndef IO_HPP
#define IO_HPP

#include "Texture.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;
using namespace boost;

class IO {
  public:
	//Constantes statiques :
	static const string S; //Séparateur
	static const string MEN_IMG_PATH; //Position des images du menu
	static const string MAP_IMG_PATH; //Position des images de la map
	static const string CHA_IMG_PATH; //Position des images des personnages
	static const string COL_DAT_PATH; //Position des données de collisions
	static const string NPC_DAT_PATH; //Position des données sur les pnj
	static const string FNT_PATH; //Position des polices
	static const string SND_PATH; //Position des sons
	
	//Méthodes :
	IO(SDL_Renderer*);
	~IO();
	vector<Texture*> getMenuImages();
	vector<Texture*> getMapImages();
	vector<Texture*> getCharacterImages();
	vector<vector<string>> getCollisionsData();
	vector<vector<string>> getNPCData();
	vector<TTF_Font*> getFonts();
	//vector<Texture*> getSounds();

  private:
	SDL_Renderer* gRenderer = NULL;
	vector<Texture*> menImgs;
	vector<Texture*> mapImgs;
	vector<Texture*> chaImgs;
	vector<vector<string>> colData;
	vector<vector<string>> npcData;
	vector<TTF_Font*> fonts;
	//vector<TTF_Font*> sounds;
	
	//Méthodes :
	vector<string>* findAllFiles(const string&); //Trouve tous les chemins de tous les fichiers dans un répertoire
	Texture* loadTexture(const string&); //Charge une image à l'aide du chemin passé en argument
	vector<string> loadTextFile(const string &); //Charge un fichier texte
	vector<Texture*> loadImages(string path); //Charge toutes les images de path
	vector<vector<string>> loadData(string path); //Charge toutes les données textuelles dans path
	void loadFonts(); //Charge toutes les polices
	//void loadSounds(); //Charge tous les sons*/
};

#endif /* IO_HPP */
