/**
 * @file   	json_settings.h
 * @brief  	Contains prototype for functions that load the JSON settings.
 */
/*! Include Guard */
#ifndef __JSON_SETTINGS_IIOT__H__
#define __JSON_SETTINGS_IIOT__H__

/* --- Project Includes --- */
#include "si/plc_modbus.h"
#include "si/iec104_client.h"
#include "si/opcua_client.h"
#include "si/opcua_server.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the IEC 104 Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the IEC 104 settings.
 * @return iec104ClientObj with settings loaded on SUCCESS and
 *                   NULL pointers in iec104ClientObj on failure
 */
iec104ClientObj getIec104ClientSettings(char *jsonSubName);

/**
 * @brief Get the Mqtt Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the MQTT settings.
 * @return mqttObj with settings loaded on SUCCESS and
 *                   NULL pointers in twilioObj on failure
 */
opcuaClientObj getOpcuaClientSettings(char *jsonSubName);

/**
 * @brief Get the OPCUA server Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the OPCUA server settings.
 * @return opcuaServerObj with settings loaded on SUCCESS and
 *                   NULL pointers in opcuaServerObj on failure
 */
opcuaServerObj getOpcuaServerSettings(char *jsonSubName);

/**
 * @brief Get the Modbus Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the Modbus settings.
 * @return modbusObj with settings loaded on SUCCESS and
 *                   NULL pointers in modbusObj on failure
 */
modbusObj getModbusClientSettings(char *jsonSubName);

#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif  /* __JSON_SETTINGS_IIOT__H__ */ /* End of Include Guard */