#include "IO.hpp"

const string IO::S = "/";
const string IO::IMG_PATH = "res/images";
const string IO::DAT_PATH = "res/data";
const string IO::FNT_PATH = "res/fonts";
const string IO::SND_PATH = "res/sounds";

IO::IO() {
}

//Renvoie un tableau de string contenant tous les chemins vers tous les fichiers contenues dans p

int IO::findAllFiles(const string &p) {
    filesystem::path path(p); //Initialisation
    if (!filesystem::exists(path)) { //Si le dossier n'existe pas
        cout << "Unable to find the repository : " << p << endl;
        return 0;
    }
    if (!filesystem::is_directory(path)) { //Si le chemin donné est un dossier
        cout << p << " is not a repository" << endl;
        return 0;
    }
    for (filesystem::directory_iterator it(path), end; it != end; ++it) { //On itère les fichiers de ce dossier
        if (filesystem::is_directory(it->status())) { //Si le chemin (fichier) est un dossier
            cout << "[DIR]" << it->path().filename() << endl;
            findAllFiles(path.string() + S + it->path().filename().string()); //On liste les fichiers de ce dossier récursivement
            cout << endl;
        } else if (filesystem::is_regular_file(it->status())) //Si c'est un fichier
            cout << it->path().filename() << endl;
    }
    return 0;
}

//Charge l'image de chemin path

/*SDL_Surface* IO::loadSurface(const string &path) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        cout << "Unable to load image" << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
    } else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
        if (optimizedSurface == NULL) {
            cout << "Unable to optimize image" << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}*/

int IO::loadImages() {
    findAllFiles(IMG_PATH);
    return 0;
}
