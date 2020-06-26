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
#include "OptionsVideoState.h"
#include "../Engine/Language.h"
#include "../Interface/TextButton.h"
#include "../Engine/Action.h"
#include "../Interface/Text.h"
#include "../Interface/TextEdit.h"
#include "../Interface/ToggleTextButton.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Interface/ArrowButton.h"
#include "../Engine/FileMap.h"
#include "../Engine/Logger.h"
#include "../Interface/ComboBox.h"
#include "../Engine/Game.h"
#include "SetWindowedRootState.h"
#include "../Engine/Renderer.h"

namespace OpenXcom
{
/**
 * Initializes all the elements in the Video Options screen.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 */
OptionsVideoState::OptionsVideoState(OptionsOrigin origin) : OptionsBaseState(origin)
{
	setCategory(_btnVideo);

	// Create objects
	_displaySurface = new InteractiveSurface(110, 32, 94, 18);
	_txtDisplayResolution = new Text(114, 9, 94, 8);
	_txtDisplayWidth = new Text(40, 17, 94, 26);
	_txtDisplayX = new Text(16, 17, 132, 26);
	_txtDisplayHeight = new Text(40, 17, 144, 26);

	_txtLanguage = new Text(114, 9, 94, 52);
	_cbxLanguage = new ComboBox(this, 104, 16, 94, 62);

	_txtFilter = new Text(114, 9, 206, 52);
	_cbxFilter = new ComboBox(this, 104, 16, 206, 62);

	_txtGeoScale = new Text(114, 9, 94, 82);
	_cbxGeoScale = new ComboBox(this, 104, 16, 94, 92);

	_txtBattleScale = new Text(114, 9, 94, 112);
	_cbxBattleScale = new ComboBox(this, 104, 16, 94, 122);

	_txtOptions = new Text(114, 9, 206, 82);
	_btnLetterbox = new ToggleTextButton(104, 16, 206, 92);


	add(_displaySurface);
	add(_txtDisplayResolution, "text", "videoMenu");
	add(_txtDisplayWidth, "resolution", "videoMenu");
	add(_txtDisplayX, "resolution", "videoMenu");
	add(_txtDisplayHeight, "resolution", "videoMenu");

	add(_txtLanguage, "text", "videoMenu");
	add(_txtFilter, "text", "videoMenu");

	add(_txtOptions, "text", "videoMenu");
	add(_btnLetterbox, "button", "videoMenu");

	add(_cbxFilter, "button", "videoMenu");

	add(_txtBattleScale, "text", "videoMenu");
	add(_cbxBattleScale, "button", "videoMenu");

	add(_txtGeoScale, "text", "videoMenu");
	add(_cbxGeoScale, "button", "videoMenu");

	add(_cbxLanguage, "button", "videoMenu");
	centerAllSurfaces();

	// Set up objects
	_txtDisplayResolution->setText(tr("STR_DISPLAY_RESOLUTION"));

	_txtDisplayWidth->setAlign(ALIGN_CENTER);
	_txtDisplayWidth->setBig();

	_txtDisplayX->setAlign(ALIGN_CENTER);
	_txtDisplayX->setBig();
	_txtDisplayX->setText("x");

	_txtDisplayHeight->setAlign(ALIGN_CENTER);
	_txtDisplayHeight->setBig();

	std::ostringstream ssW, ssH;
	ssW << Options::displayWidth;
	ssH << Options::displayHeight;
	_txtDisplayWidth->setText(ssW.str());
	_txtDisplayHeight->setText(ssH.str());

	_txtOptions->setText(tr("STR_DISPLAY_OPTIONS"));

	_btnLetterbox->setText(tr("STR_LETTERBOXED"));
	_btnLetterbox->setPressed(Options::keepAspectRatio);
	_btnLetterbox->onMouseClick((ActionHandler)&OptionsVideoState::btnLetterboxClick);
	_btnLetterbox->setTooltip("STR_LETTERBOXED_DESC");
	_btnLetterbox->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_btnLetterbox->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtLanguage->setText(tr("STR_DISPLAY_LANGUAGE"));

	std::vector<std::string> names;
	Language::getList(_langs, names);
	_cbxLanguage->setOptions(names);
	for (size_t i = 0; i < names.size(); ++i)
	{
		if (_langs[i] == Options::language)
		{
			_cbxLanguage->setSelected(i);
			break;
		}
	}
	_cbxLanguage->onChange((ActionHandler)&OptionsVideoState::cbxLanguageChange);
	_cbxLanguage->setTooltip("STR_DISPLAY_LANGUAGE_DESC");
	_cbxLanguage->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxLanguage->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	std::vector<std::string> filterNames;
	auto upscalers = getRegisteredUpscalers();
	size_t selFilter = 0;
	for(size_t i = 0; i < upscalers.size(); ++i)
	{
		const auto& upscaler = upscalers[i];
		std::ostringstream wss;
		wss << "(" << upscaler.first << ") " << upscaler.second;
		filterNames.push_back(wss.str());
		_filters.push_back(upscaler.second);
		if (upscaler.first == Options::renderer && upscaler.second == Options::scalerName)
		{
			selFilter = i;
		}
	}

	_txtFilter->setText(tr("STR_DISPLAY_FILTER"));

	_cbxFilter->setOptions(filterNames);
	_cbxFilter->setSelected(selFilter);
	_cbxFilter->onChange((ActionHandler)&OptionsVideoState::cbxFilterChange);
	_cbxFilter->setTooltip("STR_DISPLAY_FILTER_DESC");
	_cbxFilter->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxFilter->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtGeoScale->setText(tr("STR_GEOSCAPE_SCALE"));

	std::vector<std::string> scales;
	scales.push_back(tr("STR_ORIGINAL"));
	scales.push_back(tr("STR_1_5X"));
	scales.push_back(tr("STR_2X"));
	scales.push_back(tr("STR_THIRD_DISPLAY"));
	scales.push_back(tr("STR_HALF_DISPLAY"));
	scales.push_back(tr("STR_FULL_DISPLAY"));
	scales.push_back(tr("STR_FOURTH_DISPLAY"));
	scales.push_back(tr("STR_FIFTH_DISPLAY"));
	scales.push_back(tr("STR_SIXTH_DISPLAY"));

	_cbxGeoScale->setOptions(scales);
	_cbxGeoScale->setSelected(Options::geoscapeScale);
	_cbxGeoScale->onChange((ActionHandler)&OptionsVideoState::updateGeoscapeScale);
	_cbxGeoScale->setTooltip("STR_GEOSCAPESCALE_SCALE_DESC");
	_cbxGeoScale->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxGeoScale->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtBattleScale->setText(tr("STR_BATTLESCAPE_SCALE"));

	_cbxBattleScale->setOptions(scales);
	_cbxBattleScale->setSelected(Options::battlescapeScale);
	_cbxBattleScale->onChange((ActionHandler)&OptionsVideoState::updateBattlescapeScale);
	_cbxBattleScale->setTooltip("STR_BATTLESCAPE_SCALE_DESC");
	_cbxBattleScale->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxBattleScale->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

}

OptionsVideoState::~OptionsVideoState()
{

}

/**
 * Uppercases all the words in a string.
 * @param str Source string.
 * @return Destination string.
 */
std::string OptionsVideoState::ucWords(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (i == 0)
			str[0] = toupper(str[0]);
		else if (str[i] == ' ' || str[i] == '-' || str[i] == '_')
		{
			str[i] = ' ';
			if (str.length() > i + 1)
				str[i + 1] = toupper(str[i + 1]);
		}
	}
	return str;
}

/**
 * Changes the Language option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::cbxLanguageChange(Action *)
{
	Options::language = _langs[_cbxLanguage->getSelected()];
}

/**
 * Changes the Filter options.
 * @param action Pointer to an action.
 */
void OptionsVideoState::cbxFilterChange(Action *)
{
	const auto upscalers = getRegisteredUpscalers();
	size_t selectedFilter = _cbxFilter->getSelected();
	Options::newRenderer = upscalers[selectedFilter].first;
	Options::newScalerName = upscalers[selectedFilter].second;
}

/**
 * Changes the Letterboxing option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnLetterboxClick(Action *)
{
	Options::keepAspectRatio = _btnLetterbox->getPressed();
}

/**
 * Changes the geoscape scale.
 * @param action Pointer to an action.
 */
void OptionsVideoState::updateGeoscapeScale(Action *)
{
	Options::newGeoscapeScale = _cbxGeoScale->getSelected();
}

/**
 * Updates the Battlescape scale.
 * @param action Pointer to an action.
 */
void OptionsVideoState::updateBattlescapeScale(Action *)
{
	Options::newBattlescapeScale = _cbxBattleScale->getSelected();
}

/**
 * Updates the scale.
 * @param dX delta of X;
 * @param dY delta of Y;
 */
void OptionsVideoState::resize(int &dX, int &dY)
{
	OptionsBaseState::resize(dX, dY);
	std::ostringstream ss;
	ss << Options::displayWidth;
	_txtDisplayWidth->setText(ss.str());
	ss.str("");
	ss << Options::displayHeight;
	_txtDisplayHeight->setText(ss.str());
}

/**
 * Takes care of any events from the core game engine.
 * @param action Pointer to an action.
 */
void OptionsVideoState::handle(Action *action)
{
	State::handle(action);
	if (action->getDetails()->key.keysym.sym == SDLK_g && (SDL_GetModState() & KMOD_CTRL) != 0)
	{
		_btnLockMouse->setPressed(Options::captureMouse);
	}

}
}
