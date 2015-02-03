/*
 * Author: Garth 'L-H' de Wet
 * Initialises the explosives system
 *
 * Arguments:
 * None
 *
 * Return Value:
 * None
 *
 * Example:
 * None
 *
 * Public: No
 */
#include "script_component.hpp"

ADDON = false;

PREP(addClacker);
PREP(canDefuse);
PREP(canDetonate);
PREP(defuseExplosive);
PREP(detonateExplosive);

PREP(handleScrollWheel);

PREP(hasExplosives);
PREP(hasPlacedExplosives);

PREP(getDetonators);
PREP(getPlacedExplosives);

PREP(openDetonateUI);
PREP(openPlaceUI);
PREP(openTransmitterUI);
PREP(openTimerSetUI);
PREP(openTriggerSelectionUI);

PREP(place_Approve);
PREP(place_Cancel);

PREP(placeExplosive);

PREP(selectTrigger);
PREP(setupExplosive);
PREP(setPosition);
PREP(startDefuse);
PREP(startTimer);
PREP(triggerType);

ADDON = true;
