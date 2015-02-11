#ifndef __GAMECONTROLLER__
#define __GAMECONTROLLER__

#include "../lib/CImg.h"
using namespace cimg_library;

#include <vector>
using namespace std;

class GameController {

public:
  GameController(const char* map);

  void toggleMode();
  bool isInAutoMode() const;
  bool nextTurn();
  void updateDisplay();
  void setDisplay(CImgDisplay* display);
  int getDelayTime() const;

protected:
  CImg<unsigned char> _displayImg;
  CImgDisplay* _display;

  bool _autoMode;
  vector<char> _map;
  int _width, _height;
  int _scale, _scaleW, _scaleH;
  int _offsetX, _offsetY;
  int _delay;

  void on(int x, int y, unsigned char c = 255);
  int countLiveNeighbors(int x, int y);

};
#endif