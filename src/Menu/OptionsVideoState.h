#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <vector>
#include "../Engine/State.h"
#include "OptionsBaseState.h"
#include <SDL.h>

namespace OpenXcom
{

class TextButton;
class ToggleTextButton;
class Text;
class TextEdit;
class ArrowButton;
class ComboBox;
class InteractiveSurface;

/**
 * Screen that lets the user configure various
 * Video options.
 */
class OptionsVideoState : public OptionsBaseState
{
private:
	InteractiveSurface *_displaySurface;
	Text *_txtDisplayResolution, *_txtDisplayX, *_txtDisplayWidth, *_txtDisplayHeight;

	Text *_txtLanguage, *_txtFilter, *_txtGeoScale, *_txtBattleScale;
	ComboBox *_cbxLanguage, *_cbxFilter, *_cbxGeoScale, *_cbxBattleScale;
	Text *_txtOptions;
	ToggleTextButton *_btnLetterbox, *_btnLockMouse;

	std::vector<SDL_DisplayMode> _res;
	int _resCurrent;
	std::vector<std::string> _langs, _filters;

	std::string ucWords(std::string str);
	void updateDisplayResolution();
public:
	/// Creates the Options state.
	OptionsVideoState(OptionsOrigin origin);
	/// Cleans up the Options state.
	~OptionsVideoState();
	/// Handler for changing the Language combobox.
	void cbxLanguageChange(Action *action);
	/// Handler for changing the Filter combobox.
	void cbxFilterChange(Action *action);
	/// Handler for clicking the Letterboxed button.
	void btnLetterboxClick(Action *action);
	/// Handler for updating the selected battlescape scale.
	void updateBattlescapeScale(Action *action);
	/// Handler for updating the selected geoscape scale.
	void updateGeoscapeScale(Action *action);
	/// Update the resolution settings, we just resized the window.
	void resize(int &, int &) override;
	/// Update the game's resolution
	void updateGameResolution();
	/// Handles keypresses.
	void handle(Action *action) override;
	/// Unpresses Root Window Pos button.
	void unpressRootWindowedMode();
};

}
