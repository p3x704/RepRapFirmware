/*
 * Fan.h
 *
 *  Created on: 29 Jun 2016
 *      Author: David
 */

#ifndef SRC_FAN_H_
#define SRC_FAN_H_

#include "RepRapFirmware.h"

class GCodeBuffer;

class Fan
{
public:
	// Set or report the parameters for this fan
	// If 'mCode' is an M-code used to set parameters for the current kinematics (which should only ever be 106 or 107)
	// then search for parameters used to configure the fan. If any are found, perform appropriate actions and return true.
	// If errors were discovered while processing parameters, put an appropriate error message in 'reply' and set 'error' to true.
	// If no relevant parameters are found, print the existing ones to 'reply' and return false.
	bool Configure(unsigned int mcode, int fanNum, GCodeBuffer& gb, StringRef& reply, bool& error);

	bool IsEnabled() const { return pin != NoPin; }
	float GetValue() const { return val; }

	void Init(Pin p_pin, bool hwInverted);
	void SetValue(float speed);
	void SetHeatersMonitored(uint16_t h);
	void Check();
	void Disable();

private:
	float val;
	float lastVal;
	float minVal;
	float triggerTemperatures[2];
	float lastPwm;
	uint32_t blipTime;						// in milliseconds
	uint32_t blipStartTime;
	uint16_t freq;
	uint16_t heatersMonitored;
	Pin pin;
	bool inverted;
	bool hardwareInverted;
	bool blipping;

	void Refresh();
	void SetHardwarePwm(float pwmVal);
};

#endif /* SRC_FAN_H_ */
