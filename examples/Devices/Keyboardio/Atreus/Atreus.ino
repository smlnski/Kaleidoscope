/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"
#include <Kaleidoscope-LongPress.h>
#include <Kaleidoscope-TapDance.h>

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

enum {
  QWERTY,
  SPC_UMLAUT,
  ARR_NUM
};

enum {
  MACRO_a_UMLAUT,
  MACRO_A_UMLAUT,
  MACRO_ESZETT,
  MACRO_u_UMLAUT,
  MACRO_U_UMLAUT,
  MACRO_o_UMLAUT,
  MACRO_O_UMLAUT
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
    Key_Q   ,Key_W            ,Key_E        ,Key_R      ,Key_T
    ,Key_A  ,Key_S            ,Key_D        ,Key_F      ,Key_G
    ,Key_Z  ,Key_X            ,Key_C        ,Key_V      ,Key_B          ,Key_Backtick
    ,TD(0)  ,SFT_T(CapsLock)  ,Key_LeftAlt  ,CTL_T(Tab) ,Key_Backspace  ,TG(ARR_NUM)

                      ,Key_Y  ,Key_U       ,Key_I     ,Key_O      ,Key_P
                      ,Key_H  ,Key_J       ,Key_K     ,Key_L      ,Key_Semicolon
    ,Key_Backslash    ,Key_N  ,Key_M       ,Key_Comma ,Key_Period ,Key_Slash
    ,OSL(SPC_UMLAUT)  ,TD(1)  ,Key_LeftGui ,Key_Minus ,Key_Quote  ,TD(2)
  ),

  [SPC_UMLAUT] =  KEYMAP_STACKED
  (
    Key_Exclamation       ,Key_At                 ,Key_Hash         ,Key_Dollar       ,Key_Percent
    ,M(MACRO_a_UMLAUT)    ,M(MACRO_ESZETT)        ,Key_LeftParen    ,Key_RightParen   ,___
    ,Key_LeftCurlyBracket ,Key_RightCurlyBracket  ,Key_LeftBracket  ,Key_RightBracket ,___          ,___
    ,___                  ,___                    ,___              ,___              ,___          ,XXX

          ,Key_Star   ,M(MACRO_u_UMLAUT) ,___ ,M(MACRO_o_UMLAUT) ,Key_KeypadDivide
          ,Key_And    ,___               ,___ ,___               ,Key_KeypadSubtract
    ,___  ,Key_Caret  ,___               ,___ ,___               ,Key_KeypadAdd
    ,___  ,___        ,___               ,___ ,___               ,Key_Equals
  ),

  [ARR_NUM] =  KEYMAP_STACKED
  (
    ___  ,___           ,Key_UpArrow    ,___            ,___
    ,___ ,Key_LeftArrow ,Key_DownArrow  ,Key_RightArrow ,___
    ,___ ,___           ,___            ,___            ,___ ,___
    ,___ ,___           ,___            ,___            ,___ ,TG(ARR_NUM)

        ,Key_KeypadMultiply ,Key_7  ,Key_8  ,Key_9      ,Key_KeypadDivide
        ,___                ,Key_4  ,Key_5  ,Key_6      ,Key_KeypadSubtract
   ,___ ,___                ,Key_1  ,Key_2  ,Key_3      ,Key_KeypadAdd
   ,XXX ,___                ,___    ,Key_0  ,Key_Period ,Key_Equals
  )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusSettingsCommand,
  FocusEEPROMCommand,
  FirmwareVersion,
  LayerNames,
  Qukeys,
  SpaceCadet,
  SpaceCadetConfig,
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,
  Macros,
  DynamicMacros,
  LongPress,
  LongPressConfig,
  TapDance);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
  case MACRO_a_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), U(LeftShift), T(A));
    }
    break;
  case MACRO_A_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), T(A), U(LeftShift));
    }
    break;
  case MACRO_ESZETT:
    if (keyToggledOn(event.state)) {
      return MACRO(SEQ(K(RightAlt), K(S), K(S)));
    }
    break;
  case MACRO_u_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), U(LeftShift), T(U));
    }
    break;
  case MACRO_U_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), T(U), U(LeftShift));
    }
    break;
  case MACRO_o_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), U(LeftShift), T(O));
    }
    break;
  case MACRO_O_UMLAUT:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), D(LeftShift), T(Quote), T(O), U(LeftShift));
    }
    break;
  default:
    break;
  }
  return MACRO_NONE;
}


void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case 0:
    // Esc/screenshot tapdance
    return tapDanceActionKeys(tap_count, tap_dance_action, Key_Esc, LSHIFT(LGUI(Key_S)));
  case 1:
    // Space/Enter tapdance
    return tapDanceActionKeys(tap_count, tap_dance_action, Key_Space, Key_Enter);
  case 2:
    // Del/Ctrl+Alt+Del tapdance
    return tapDanceActionKeys(tap_count, tap_dance_action, Key_Delete, LCTRL(LALT(Key_Delete)));
  }
}


void setup() {
  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  Qukeys.setOverlapThreshold(20); // Helps to make CTR_L work with Eike's typing habits
  OneShot.disableStickabilityForLayers();

  LongPress.enable();
  LongPress.setTimeout(130);
  LongPress.setAutoshiftEnabled(LongPress.letterKeys() | LongPress.symbolKeys());

  LONGPRESS(
    // Window overview on Esc
    kaleidoscope::plugin::LongPressKey(kaleidoscope::plugin::longpress::ALL_LAYERS, KeyAddr(3, 0), LGUI(Key_Tab)),
    // Delete last word on Backspace
    kaleidoscope::plugin::LongPressKey(kaleidoscope::plugin::longpress::ALL_LAYERS, KeyAddr(3, 4), LCTRL(Key_Backspace)),
    // Delete next word on Delete
    kaleidoscope::plugin::LongPressKey(kaleidoscope::plugin::longpress::ALL_LAYERS, KeyAddr(3, 11), LCTRL(Key_Delete)),
    // Autoshift umlauts
    kaleidoscope::plugin::LongPressKey(SPC_UMLAUT, M(MACRO_a_UMLAUT), M(MACRO_A_UMLAUT)),
    kaleidoscope::plugin::LongPressKey(SPC_UMLAUT, M(MACRO_u_UMLAUT), M(MACRO_U_UMLAUT)),
    kaleidoscope::plugin::LongPressKey(SPC_UMLAUT, M(MACRO_o_UMLAUT), M(MACRO_O_UMLAUT)),
    // F4 on 4
    kaleidoscope::plugin::LongPressKey(ARR_NUM, Key_4, Key_F4));
}

void loop() {
  Kaleidoscope.loop();
}
