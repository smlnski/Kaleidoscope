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

#define MO(n) MoveToLayer(n)
#define TG(n) LockLayer(n)
#define SH(n) ShiftToLayer(n)

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
  LAY_QWERTY,
  LAY_SPC_UMLAUT,
  LAY_ARR_NUM,
  LAY_ALT_F,
  LAY_F
};

enum {
  MACRO_a_UMLAUT,
  MACRO_A_UMLAUT,
  MACRO_ESZETT,
  MACRO_u_UMLAUT,
  MACRO_U_UMLAUT,
  MACRO_o_UMLAUT,
  MACRO_O_UMLAUT,
  MACRO_e_AIGU,
  MACRO_E_AIGU
};

// clang-format off
KEYMAPS(
  [LAY_QWERTY] = KEYMAP_STACKED
  (
    Key_Q   ,Key_W            ,Key_E                  ,Key_R      ,Key_T
    ,Key_A  ,Key_S            ,Key_D                  ,Key_F      ,Key_G
    ,Key_Z  ,Key_X            ,Key_C                  ,Key_V      ,Key_B            ,Key_Backtick
    ,TD(0)  ,SFT_T(CapsLock)  ,ML(LeftAlt, LAY_ALT_F) ,CTL_T(Tab) ,OSL(LAY_ARR_NUM) ,OSL(LAY_SPC_UMLAUT)

                    ,Key_Y  ,Key_U        ,Key_I      ,Key_O       ,Key_P
                    ,Key_H  ,Key_J        ,Key_K      ,Key_L       ,Key_Semicolon
    ,Key_Backslash  ,Key_N  ,Key_M        ,Key_Comma  ,Key_Period  ,Key_Slash
    ,Key_Backspace  ,TD(1)  ,Key_LeftGui  ,Key_Minus  ,Key_Quote   ,Key_Delete
  ),

  [LAY_SPC_UMLAUT] =  KEYMAP_STACKED
  (
    Key_Exclamation     ,Key_At           ,Key_Hash             ,Key_Dollar             ,Key_Percent
    ,M(MACRO_a_UMLAUT)  ,M(MACRO_ESZETT)  ,Key_LeftParen        ,Key_RightParen         ,XXX
    ,Key_LeftBracket    ,Key_RightBracket ,Key_LeftCurlyBracket ,Key_RightCurlyBracket  ,XXX          ,___
    ,___                ,___              ,___                  ,___                    ,___          ,___

          ,Key_Star ,M(MACRO_u_UMLAUT)  ,Key_And  ,M(MACRO_o_UMLAUT)  ,Key_Caret
          ,XXX      ,XXX                ,XXX      ,XXX                ,___
    ,___  ,XXX      ,XXX                ,___      ,___                ,___
    ,___  ,___      ,___                ,___      ,___                ,___
  ),

  [LAY_ARR_NUM] =  KEYMAP_STACKED
  (
    Key_PageUp  ,LCTRL(Key_LeftArrow) ,Key_UpArrow    ,LCTRL(Key_RightArrow)  ,Key_PageDown
    ,Key_Home   ,Key_LeftArrow        ,Key_DownArrow  ,Key_RightArrow         ,Key_End
    ,___      ,___                    ,___            ,___                    ,XXX          ,___ // left Z, X, C, V transparent for undo, cut, copy, paste
    ,___      ,___                    ,SH(LAY_F)      ,___                    ,___          ,___

        ,Key_KeypadMultiply ,Key_7      ,Key_8  ,Key_9      ,Key_Minus
        ,Key_KeypadDivide   ,Key_4      ,Key_5  ,Key_6      ,Key_KeypadAdd
   ,___ ,Key_Semicolon      ,Key_1      ,Key_2  ,Key_3      ,Key_Equals
   ,___ ,___                ,Key_Comma  ,Key_0  ,Key_Period ,___
  ),

  [LAY_ALT_F] = KEYMAP_STACKED
  (
    ___   ,Key_Tab        ,___ ,Key_F4          ,___
    ,___  ,Key_LeftArrow  ,___ ,Key_RightArrow  ,___
    ,___  ,___            ,___ ,___             ,___ ,___
    ,___  ,___            ,___ ,___             ,___ ,___

         ,___ ,___ ,___ ,___ ,___
         ,___ ,___ ,___ ,___ ,___
    ,___ ,___ ,___ ,___ ,___ ,___
    ,___ ,___ ,___ ,___ ,___ ,___
  ),

  [LAY_F] = KEYMAP_STACKED
  (
    ___   ,___ ,___ ,___ ,___
    ,___  ,___ ,___ ,___ ,___
    ,___  ,___ ,___ ,___ ,___ ,___
    ,___  ,___ ,___ ,___ ,___ ,___

         ,___ ,Key_F7 ,Key_F8 ,Key_F9 ,Key_F10
         ,___ ,Key_F4 ,Key_F5 ,Key_F6 ,Key_F11
    ,___ ,___ ,Key_F1 ,Key_F2 ,Key_F3 ,Key_F12
    ,___ ,___ ,___    ,___    ,___    ,___
  )
)
// clang-format on

namespace kaleidoscope {
class CapsLockOffOnLayerSwitch : public Plugin {
 public:
  EventHandlerResult onLayerChange() {
    if (!(Layer.isActive(LAY_SPC_UMLAUT) ||
          Layer.isActive(LAY_ARR_NUM) ||
          Layer.isActive(LAY_ALT_F) ||
          Layer.isActive(LAY_F))) {
      return EventHandlerResult::OK;
    }

    constexpr uint8_t caps_lock_led = 0x02;
    if (!(Runtime.hid().keyboard().getKeyboardLEDs() & caps_lock_led)) {
      return EventHandlerResult::OK;
    }

    Runtime.hid().keyboard().pressRawKey(Key_CapsLock);
    Runtime.hid().keyboard().sendReport();
    Runtime.hid().keyboard().releaseRawKey(Key_CapsLock);
    Runtime.hid().keyboard().sendReport();

    return EventHandlerResult::OK;
  }
};
}  // namespace kaleidoscope

kaleidoscope::CapsLockOffOnLayerSwitch CapsLockOffOnLayerSwitch;

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusSettingsCommand,
  FocusEEPROMCommand,
  FirmwareVersion,
  LayerNames,
  CapsLockOffOnLayerSwitch,
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
  case MACRO_e_AIGU:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), T(Quote), T(E));
    }
    break;
  case MACRO_E_AIGU:
    if (keyToggledOn(event.state)) {
      return MACRO(T(RightAlt), T(Quote), D(LeftShift), T(E), U(LeftShift));
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

  Qukeys.setOverlapThreshold(20);  // Helps to make CTR_L work with Eike's typing habits

  LongPress.enable();
  LongPress.setTimeout(130);
  LongPress.setAutoshiftEnabled(LongPress.letterKeys() | LongPress.symbolKeys());

  LONGPRESS(
    // Window overview on Esc
    kaleidoscope::plugin::LongPressKey(kaleidoscope::plugin::longpress::ALL_LAYERS, TD(0), LGUI(Key_Tab)),
    // Autoshift umlauts
    kaleidoscope::plugin::LongPressKey(LAY_SPC_UMLAUT, M(MACRO_a_UMLAUT), M(MACRO_A_UMLAUT)),
    kaleidoscope::plugin::LongPressKey(LAY_SPC_UMLAUT, M(MACRO_u_UMLAUT), M(MACRO_U_UMLAUT)),
    kaleidoscope::plugin::LongPressKey(LAY_SPC_UMLAUT, M(MACRO_o_UMLAUT), M(MACRO_O_UMLAUT)));
}

void loop() {
  Kaleidoscope.loop();
}
