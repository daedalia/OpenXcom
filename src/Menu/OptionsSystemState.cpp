#include "OptionsSystemState.h"

#ifdef __MOBILE__

#include "../Engine/Game.h"
#include "../Interface/Text.h"
#include "../Interface/TextButton.h"
#include "../Interface/ToggleTextButton.h"
#include "../Interface/ComboBox.h"
#include "../Engine/Palette.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Options.h"
#include "../Engine/CrossPlatform.h"
#include "OptionsControlsState.h"
#include "../Engine/Logger.h"

namespace OpenXcom
{

OptionsSystemState::OptionsSystemState(OptionsOrigin origin) : OptionsBaseState(origin)
{
	setCategory(_btnSystem);

	_txtControls = new Text(104, 9, 206, 8);
	_btnControls = new TextButton(104, 16, 206, 18);

	_txtLogDestination = new Text(104, 9, 94, 8);
	_btnLogFile = new ToggleTextButton(104, 16, 94, 18);

	_txtDebugOptions = new Text(104, 9, 94, 36);
	_btnLogTouchEvents = new ToggleTextButton(104, 16, 94, 46);
	_btnFakeEvents = new ToggleTextButton(104, 16, 94, 64);

	add(_txtControls, "text", "systemMenu");
	add(_btnControls, "button", "systemMenu");

	add(_txtLogDestination, "text", "systemMenu");
	add(_btnLogFile, "button", "systemMenu");

	add(_txtDebugOptions, "text", "systemMenu");
	add(_btnLogTouchEvents, "button", "systemMenu");
	add(_btnFakeEvents, "button", "systemMenu");;

	centerAllSurfaces();

	_txtLogDestination->setText(tr("STR_LOG_DESTINATION"));

	_btnLogFile->setText(tr("STR_LOG_FILE"));
	_btnLogFile->setPressed(Options::logToFile);
	_btnLogFile->onMouseClick((ActionHandler)&OptionsSystemState::btnLogClick);
	_btnLogFile->setTooltip("STR_LOG_FILE_DESC");
	_btnLogFile->onMouseIn((ActionHandler)&OptionsSystemState::txtTooltipIn);
	_btnLogFile->onMouseOut((ActionHandler)&OptionsSystemState::txtTooltipOut);

	_txtDebugOptions->setText(tr("STR_DEBUG_OPTIONS"));

	_btnLogTouchEvents->setText(tr("STR_LOG_TOUCH_EVENTS"));
	_btnLogTouchEvents->setPressed(Options::logTouch);
	_btnLogTouchEvents->onMouseClick((ActionHandler)&OptionsSystemState::btnLogTouchEventsClick);
	_btnLogTouchEvents->setTooltip("STR_LOG_TOUCH_EVENTS_DESC");
	_btnLogTouchEvents->onMouseIn((ActionHandler)&OptionsSystemState::txtTooltipIn);
	_btnLogTouchEvents->onMouseOut((ActionHandler)&OptionsSystemState::txtTooltipOut);

	_btnFakeEvents->setText(tr("STR_FAKE_EVENTS"));
	_btnFakeEvents->setPressed(Options::fakeEvents);
	_btnFakeEvents->onMouseClick((ActionHandler)&OptionsSystemState::btnFakeEventsClick);
	_btnFakeEvents->setTooltip("STR_FAKE_EVENTS_DESC");
	_btnFakeEvents->onMouseIn((ActionHandler)&OptionsSystemState::txtTooltipIn);
	_btnFakeEvents->onMouseOut((ActionHandler)&OptionsSystemState::txtTooltipOut);

	_txtControls->setText(tr("STR_CONTROLS_LABEL"));

	_btnControls->setText(tr("STR_CONTROLS"));
	_btnControls->onMouseClick((ActionHandler)&OptionsSystemState::btnControlsClick);
}


OptionsSystemState::~OptionsSystemState(void)
{
}

/**
 * Handles transitioning to the Controls state.
 */
void OptionsSystemState::btnControlsClick(Action *action)
{
	_game->popState();
	_game->pushState(new OptionsControlsState(_origin));
}

void OptionsSystemState::btnLogClick(Action *action)
{
	InteractiveSurface *sender = action->getSender();
	if (sender == _btnLogFile)
	{
		Options::logToFile = _btnLogFile->getPressed();
	}
}

void OptionsSystemState::btnLogTouchEventsClick(Action *action)
{
	Options::logTouch = _btnLogTouchEvents->getPressed();
}

void OptionsSystemState::btnFakeEventsClick(Action *action)
{
	Options::fakeEvents = _btnFakeEvents->getPressed();
}

}

#endif /*__MOBILE__*/
