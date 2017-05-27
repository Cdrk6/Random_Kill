#include "IO.hpp"

const string IO::S = "/";
const string IO::IMG_PATH = "res/images";
const string IO::DAT_PATH = "res/data";
const string IO::FNT_PATH = "res/fonts";
const string IO::SND_PATH = "res/sounds";

IO::IO(SDL_Renderer* r) {
    gRenderer = r;
    loadImages();
    /*loadData();
    loadFonts();
    loadSounds();*/
}

IO::~IO() {
    for(int i = 0; i < images.size(); i++)
        delete images[i];
}

//Renvoie un tableau de string contenant tous les chemins vers tous les fichiers contenues dans p

vector<string>* IO::findAllFiles(const string &p) {
    filesystem::path path(p); //Initialisation
    if (!filesystem::exists(path) || !filesystem::is_directory(path)) { //Si le dossier n'existe pas
        cerr << "Unable to find the repository : " << p << endl;
        return NULL;
    }
    vector<string>* listPaths = new vector<string>();
    vector<string>* temp = NULL;
    for (filesystem::directory_iterator it(path), end; it != end; ++it) { //On itère les fichiers de ce dossier
        if (filesystem::is_directory(it->status())) { //Si le chemin (fichier) correspond à un dossier
            cout << "[DIR]" << it->path().filename() << endl;
            temp = findAllFiles(path.string() + S + it->path().filename().string()); //On liste les fichiers de ce dossier récursivement
            listPaths->insert(listPaths->end(), temp->begin(), temp->end());
            delete temp;
        } else if (filesystem::is_regular_file(it->status())) //Si c'est un fichier
            listPaths->push_back(it->path().relative_path().string());
    }
    return listPaths;
}

//Charge l'image de chemin path et renvoie une texture

Texture* IO::loadTexture(const string &path) {
    Texture* texture = NULL; //The final texture
    SDL_Texture* sdlTexture = NULL; //The SDL texture
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //Load image at specified path
    if (loadedSurface == NULL)
        cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF)); //Color key image
        sdlTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); //Create texture from surface pixels
        if (sdlTexture == NULL)
            cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
        texture = new Texture(sdlTexture, loadedSurface->w, loadedSurface->h, gRenderer);
        SDL_FreeSurface(loadedSurface); //Get rid of old loaded surface
    }
    return texture;
}

void IO::loadImages() {
    vector<string>* paths = findAllFiles(IMG_PATH);
    images = vector<Texture*>(paths->size());
    for (int i = 0; i < paths->size(); i++) {
        filesystem::path path((*paths)[i]);
        //cout << i << ". " << (*paths)[i] << " ;FN : "<< path.stem().string() << endl;
        images[stoi(path.stem().string())] = loadTexture((*paths)[i]);
    }
    cout << "[OK] Images loaded : " << images.size() << endl;
    delete paths;
}

vector<Texture*> IO::getImages() {
    return images;
}

/*bool Texture::loadFonts(string textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface != NULL) {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    } else {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }


    //Return success
    return mTexture != NULL;
}*/
