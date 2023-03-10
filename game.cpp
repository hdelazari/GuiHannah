#ifndef GAME_CPP
#define GAME_CPP

#include <X11/Xlib.h>
#include "shapes.cpp"
#include "game_display.cpp"
#include "physics.cpp"

class Game {
public:
  Game();

  void run(std::vector<Circle> c, Vector gravity, Bounds b);

private:
  GameDisplay gamedisplay_;
  XEvent event_;
  bool is_running_ = true;

  bool getEvent();
};


Game::Game() {}

void Game::run(std::vector<Circle> circles, Vector gravity, Bounds b) {
  int i=0;
  while (is_running_) {
    if (i==10000){
        gamedisplay_.drawScreen(circles);
        for (Circle &c : circles) {
            updateCircle(c, gravity, b);
        }
        i=0;
    }
    i++;
    if (getEvent()) {
      gamedisplay_.drawScreen(circles);
    }
  }
}

bool Game::getEvent() {
  if (XPending(gamedisplay_.getDisplay())) {
    XNextEvent(gamedisplay_.getDisplay(), &event_);
    printf("EVENT: %d\n", event_.type);
    return true;
  }

  return false;
}
#endif /* GAME_CPP */
