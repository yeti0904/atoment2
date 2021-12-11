#pragma once
#include "atoment.hh"

void builtin_println(ATM::Language_Components atm, ATM::Arglist args);
void builtin_push(ATM::Language_Components atm, ATM::Arglist args);
void builtin_pop(ATM::Language_Components atm, ATM::Arglist args);
void builtin_putchar(ATM::Language_Components atm, ATM::Arglist args);