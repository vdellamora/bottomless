#ifndef C_TEXT
#define C_TEXT

#include "inclusao.h"
#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include <memory>

class Text : public Component{

public:
	enum TextStyle{SOLID, SHADED, BLENDED};
	Text(GameObject&, std::string, int, TextStyle, std::string, SDL_Color);
	~Text();
	void Update(float);
	void Render();
	bool Is(std::string);

	void SetText(std::string);
	void SetColor(SDL_Color);
	void SetStyle(TextStyle);
	void SetFontFile(std::string);
	void SetFontSize(int);
private:
	void RemakeTexture();

	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	std::string fontFile;
	int fontSize;
	SDL_Color color;
};

#endif //C_TEXT