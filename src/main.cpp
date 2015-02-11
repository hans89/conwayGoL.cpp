// #include "player1.h"
// #include "player2.h"

#include "../lib/CImg.h"
#include "GameController.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace cimg_library;


int main(int argc, char* argv[]) {
  
  if (argc < 2) {
    std::cout << "Usage: golcpp seed.text";
    return 0;
  }
  
  GameController gameController(argv[1]);
  
  // 2. set up display
  CImgDisplay main_disp;

  gameController.setDisplay(&main_disp);
  gameController.updateDisplay();

  int delay = gameController.getDelayTime(); // in millisecond

  // main loop
  while (!main_disp.is_closed()) {

    const unsigned int keyPressed = main_disp.key();
    // check if "r" key is clicked: toggle auto-step and manual-step mode
    if (keyPressed == cimg::keyR) {
      // flush all keys
      main_disp.set_key();
      gameController.toggleMode();
      gameController.updateDisplay();
    }
    
    if (gameController.isInAutoMode()) {
    // check if auto-step or manual-step
      // auto step mode
      // in auto-step mode, the controller moves the game forward one step each iteration
      // wait for DELAY time
      gameController.nextTurn();
      gameController.updateDisplay();
      main_disp.wait(delay);
    } else {
      // manual-step mode
      // in manual-step mode, the controller wait for the key event "SPACE" to 
      // asks the next player to move
      if (keyPressed == cimg::keySPACE) {
        // flush all keys
        main_disp.set_key();
        gameController.nextTurn();
        gameController.updateDisplay();
      }
    }
  }
  return 0;
}