#ifndef C_TEXT
#define C_TEXT

#include "inclusao.h"
#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include <memory>
#include "Timer.h"

class Dialogue : public Component{
  
public:
  enum TextStyle{SOLID, SHADED, BLENDED};
  Dialogue(GameObject&, std::string, int, TextStyle, std::string, SDL_Color);
  ~Dialogue();
  void Update(float);
  void Render();
  bool Is(std::string);
  
  void SetText(std::string);
  void SetColor(SDL_Color);
  void SetStyle(TextStyle);
  void SetFontFile(std::string);
  void SetFontSize(int);
  void SetTextSpeed(int);
private:
  void RemakeTexture();
  bool shouldRender;
  
  std::shared_ptr<TTF_Font> font;
  SDL_Texture* texture;
  std::string text;
  TextStyle style;
  std::string fontFile;
  int fontSize;
  int index;
  SDL_Color color;
  Timer timer;
  
  std::string partialText;
  float textSpeed;
};

#endif //C_TEXT
