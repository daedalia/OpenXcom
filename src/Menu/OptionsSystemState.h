

#ifndef OPENXCOM_OPTIONSSYSTEMSTATE_H
#define OPENXCOM_OPTIONSSYSTEMSTATE_H

#ifdef __MOBILE__

#include "OptionsBaseState.h"

namespace OpenXcom
{

class ComboBox;
class Text;
class TextButton;
class ToggleTextButton;

/**
 * System-specific options menu (used in place of "Controls" menu)
 */
class OptionsSystemState : public OptionsBaseState
{
private:
	Text *_txtControls;
	Text *_txtLogDestination;
	Text *_txtDebugOptions;
	ToggleTextButton *_btnLogFile;
	ToggleTextButton *_btnLogTouchEvents;
	ToggleTextButton *_btnFakeEvents;
public:
	OptionsSystemState(OptionsOrigin origin);
	~OptionsSystemState();
	void btnControlsClick(Action *action);
	void btnLogClick(Action *action);
	void btnLogTouchEventsClick(Action *action);
	void btnFakeEventsClick(Action *action);
};

}

#endif /*__MOBILE__*/

#endif /*OPENXCOM_OPTIONSSYSTEMSATE_H*/
