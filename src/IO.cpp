#include "IO.hpp"

const string IO::S = "/";
const string IO::MEN_IMG_PATH = "res/images/menu";
const string IO::MAP_IMG_PATH = "res/images/map";
const string IO::CHA_IMG_PATH = "res/images/character";
const string IO::DAT_PATH = "res/data";
const string IO::FNT_PATH = "res/fonts";
const string IO::SND_PATH = "res/sounds";

IO::IO(SDL_Renderer* r) {
    gRenderer = r;
    menImgs = loadImages(MEN_IMG_PATH);
    mapImgs = loadImages(MAP_IMG_PATH);
    chaImgs = loadImages(CHA_IMG_PATH);
    loadData();
    loadFonts();
    //loadSounds();
}

IO::~IO() {
    for (int i = 0; i < menImgs.size(); i++)
        delete menImgs[i];
    for (int i = 0; i < mapImgs.size(); i++)
        delete mapImgs[i];
    for (int i = 0; i < chaImgs.size(); i++)
        delete chaImgs[i];
    for (int i = 0; i < fonts.size(); i++) {
        TTF_CloseFont(fonts[i]);
        fonts[i] = NULL;
    }
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
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str()); //IMG_Load(path.c_str()); //Load image at specified path
    if (loadedSurface == NULL)
        cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF)); //Color key image
        sdlTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); //Create texture from surface pixels
        if (sdlTexture == NULL)
            cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
        texture = new Texture(sdlTexture, loadedSurface->w, loadedSurface->h, gRenderer);
        SDL_FreeSurface(loadedSurface); //Get rid of old loaded surface
    }
    return texture;
}

vector<string> IO::loadTextFile(const string &path) {
    vector<string> dat;
    string line;
    ifstream file(path);
    if (file.is_open()) {
        while (getline(file, line))
            dat.push_back(line);
        file.close();
    }
    else cout << "Unable to open file";
    return dat;
}

vector<Texture*> IO::loadImages(string path) {
    vector<string>* paths = findAllFiles(path);
    vector<Texture*> images = vector<Texture*>(paths->size());
    for (int i = 0; i < paths->size(); i++) {
        filesystem::path path((*paths)[i]);
        //cout << i << ". " << (*paths)[i] << " ;FN : "<< path.stem().string() << endl;
        images[stoi(path.stem().string())] = loadTexture((*paths)[i]);
    }
    cout << "[OK] Images loaded from " << path << " : " << images.size() << endl;
    delete paths;
    return images;
}

void IO::loadData() {
    vector<string>* paths = findAllFiles(DAT_PATH);
    data = vector<vector < string>>(paths->size());
    for (int i = 0; i < paths->size(); i++) {
        filesystem::path path((*paths)[i]);
        //cout << i << ". " << (*paths)[i] << " ;FN : "<< path.stem().string() << endl;
        data[stoi(path.stem().string())] = loadTextFile((*paths)[i]);
    }
    cout << "[OK] Text files loaded : " << data.size() << endl;
    //cout << data[0][0] << endl;
    delete paths;
}

void IO::loadFonts() {
    vector<string>* paths = findAllFiles(FNT_PATH);
    fonts = vector<TTF_Font*>(paths->size());
    for (int i = 0; i < paths->size(); i++) {
        filesystem::path path((*paths)[i]);
        //cout << i << ". " << (*paths)[i] << " ;FN : "<< path.stem().string() << endl;
        fonts[stoi(path.stem().string())] = TTF_OpenFont((*paths)[i].c_str(), 30);
        if (!fonts[stoi(path.stem().string())])
            cerr << "Unable to load font from " << path.relative_path() << "! TTF Error: " << TTF_GetError() << endl;
    }
    cout << "[OK] Fonts loaded : " << fonts.size() << endl;
    delete paths;
}

vector<Texture*> IO::getMenuImages() {
    return menImgs;
}

vector<Texture*> IO::getMapImages() {
    return mapImgs;
}

vector<Texture*> IO::getCharacterImages() {
    return chaImgs;
}

vector<vector<string>> IO::getData() {
    return data;
}

vector<TTF_Font*> IO::getFonts() {
    return fonts;
}
