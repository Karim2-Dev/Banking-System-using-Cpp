

#include "classes/BankSystem/LoginScreen/clsLoginScreen.h"

int main() {
  while (true) {
    if (!clsLoginScreen::LoginScreen()) { break; }
  }

  return 0;
};