#include "GameController.h"

#include <fstream>
#include <iostream>
using namespace std;

int r[3] = {-1, 0, 1};

GameController::GameController(const char* map) : _autoMode(false) {
  int w, h;
  w = h = 0;

  ifstream inputMap(map);

  if (!inputMap.is_open()) {
    cout << "Can't load map " << map << endl;
    return;
  }

  inputMap >> _width >> _height >> _scale >> _delay;

  inputMap >> _offsetX >> _offsetY;

  _scaleW = _scale * _width;
  _scaleH = _scale * _height;

  _map = vector<char>(_width * _height, 0);

  _displayImg = CImg<unsigned char>(_scaleW, _scaleH, 1, 3, 0);

  int x, y;
  x = y = 0;

  string line;
  int j = 0;
  // O : alive
  // . : dead
  while (getline(inputMap, line).good()) {
    if (!line.empty()) {
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == 'O') {
          x = _offsetX + i;
          y = _offsetY + j;
          if (x >= 0 && x < _width && y >= 0 && y < _height) {
            _map[y*_width + x] = 1;
          }
        }
      }
      j++;
      line = "";
    }
  }

  while (inputMap.good()) {
    inputMap >> x >> y;
    
    
  }
  inputMap.close();
}

int GameController::getDelayTime() const {
  return _delay;
}
void GameController::setDisplay(CImgDisplay* display) {
  _display = display;
}

int GameController::countLiveNeighbors(int x, int y) {
  int x0, y0, count = - _map[y*_width + x];
  for(int j = 0; j < 3; j++)
    for(int i = 0; i < 3; i++) {
      x0 = x + r[i];
      y0 = y + r[j];
      if (x0 >= 0 && x0 < _width && y0 >= 0 && y0 < _height)
        count += _map[y0*_width + x0];
    }
  return count;
}

bool GameController::nextTurn() {
  // return true if something changes
  bool change = false;
  int size = _map.size();
  vector<char> newMap(size, 0);

  // apply Conway rules
  int i = 0, n = 0;
  for (int y = 0; y < _height; y++)
    for (int x = 0; x < _width; x++) {
      n = countLiveNeighbors(x,y);
      if ((_map[i] && (n == 2 || n == 3)) || (!_map[i] && n == 3))
        newMap[i] = 1;
      i++;
    }
      
  // replace map
  _map = newMap;

  return change;
}

void GameController::toggleMode() {
  _autoMode = !_autoMode;
}

bool GameController::isInAutoMode() const {
  return _autoMode;
}

void GameController::on(int x, int y, unsigned char c) {
  int x1 = x * _scale,
      x2 = x1 + _scale,
      y1 = y * _scale,
      y2 = y1 + _scale;

  for (int j = y1; j < y2; j++)
    for (int i = x1; i < x2; i++)
      _displayImg(i,j,0)
        = _displayImg(i,j,1)
        = _displayImg(i,j,2)
        = c;
}

void GameController::updateDisplay() {
  int i = 0;
  for (int y = 0; y < _height; y++)
    for (int x = 0; x < _width; x++) {
      if (_map[i])
        on(x, y);
      else
        on(x,y, 0);
      i++;
    }

  _displayImg.display(*_display);
}