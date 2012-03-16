/*
 * Copyright 2010-2012 OpenXcom Developers.
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
#ifndef OPENXCOM_LISTPOSSIBLEPRODUCTIONSTATE_H
#define OPENXCOM_LISTPOSSIBLEPRODUCTIONSTATE_H

#include "../Engine/State.h"
#include <vector>

namespace OpenXcom
{
class Base;
class TextButton;
class Window;
class Text;
class TextList;
class RuleManufactureInfo;
class ManufactureState;

/**
 * Screen which list possible productions.
 */
class ListPossibleProductionState : public State
{
private:
	Base *_base;
	TextButton *_btnOk;
	Window *_window;
	Text *_txtTitle, *_txtItem, *_txtCategory;
	TextList *_lstManufacture;
	ManufactureState * _manufactureState;
	std::vector<RuleManufactureInfo *> _possibleProductions;

public:
	/// Create the state
	ListPossibleProductionState(Game *game, Base *base);
	/// Initialize state
	void init ();
	/// Handler for clicking the OK button
	void btnOkClick(Action * action);
	/// Handler for clicking on the list
	void lstProdClick (Action * action);
	/// Fill the list with Base production's
	void fillProductionList();
};
}
#endif
