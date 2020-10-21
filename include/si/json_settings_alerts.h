/**
 * @file   	json_settings.h
 * @brief  	Contains prototype for functions that load the JSON settings.
 */
/*! Include Guard */
#ifndef __JSON_SETTINGS_ALERTS__H__
#define __JSON_SETTINGS_ALERTS__H__

/* --- Project Includes --- */
#include "si/twilio.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the Twilio Settings from the JSON file
 *
 * @param jsonSubName JSON object name that contains the Twilio settings
 * @return twilioObj with settings loaded on SUCCESS and
 *                   NULL pointers in twilioObj on failure
 */
extern twilioObj getTwilioJsonConfig(char *jsonSubName);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif  /* __JSON_SETTINGS_ALERTS__H__ */ /* End of Include Guard */