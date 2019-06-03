#ifndef C_RESOURCES
#define C_RESOURCES

#include "inclusao.h"
#include <iostream>
#include <unordered_map>
#include <memory>

class Resources{

public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string);
	static std::shared_ptr<Mix_Music> GetMusic(std::string);
	static std::shared_ptr<Mix_Chunk> GetSound(std::string);
	static std::shared_ptr<TTF_Font> GetFont(std::string, int);

	static void ClearImages();
	static void ClearMusics();
	static void ClearSounds();
	static void ClearFonts();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > imageTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music> > musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> > soundTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font> > fontTable;
};



#endif //C_RESOURCES