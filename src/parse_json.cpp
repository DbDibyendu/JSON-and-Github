/**
* @file parse_json.cpp
* @brief Contians functions used for parsing and retrieveing settings when the
*        API calls for it.
*/

/* --- Standard Includes --- */
#include <fstream>
#include <cstdlib>
#include <string>
#include <error.h>

/* --- RapidJson Includes --- */
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"

/* --- Project Includes --- */
#include "si/json_settings_alerts.h"
#include "si/json_settings_dash.h"
#include "si/json_settings_iiot.h"
#include "si/json_settings_conn.h"
#include "si/json_settings_cloud.h"

#define SI_CONFIG_FILE "/etc/shunya/config.json"
#define JSON_MAX_READ_BUF_SIZE 65536

using namespace rapidjson;
using namespace std;

/* Declare a JSON document. JSON document parsed will be stored in this variable */
static Document config;

/*
 * @brief Parse and store JSON document into global variable
 *
 * @return int8_t 0 on SUCCESS and -1 on FAILURE
 */
int8_t loadJsonConfig()
{
    int8_t ret = -1;
    /* Open the example.json file in read mode */
    FILE *fp = fopen(SI_CONFIG_FILE, "rb");

    if (fp != NULL) {
        /* Declare read buffer */
        char readBuffer[JSON_MAX_READ_BUF_SIZE];
        /* Declare stream for reading the example stream */
        FileReadStream frstream(fp, readBuffer, sizeof(readBuffer));
        /* Parse example.json and store it in `d` */
        config.ParseStream(frstream);
        ParseResult ok = config.ParseStream(frstream);

        if (!ok) {
            fprintf(stderr, "Error Reading JSON config file: JSON parse error: %s (%u)",
                    GetParseError_En(ok.Code()), ok.Offset());
        }

        ret = 0;

    } else {
        fprintf(stderr,"Error Reading JSON config file: %s", strerror(errno));
    }

    /* Close the example.json file*/
    fclose(fp);
    return ret;
}

/*
 * @brief Get the Twilio Settings from the JSON file
 *
 * @param jsonSubName JSON object name that contains the Twilio settings
 * @return twilioObj with settings loaded on SUCCESS and
 *                   NULL pointers in twilioObj on failure
 */
twilioObj getTwilioJsonConfig(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    twilioObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("account sid")) {
            strncpy(obj.auth_token, sub["auth token"].GetString(), sub["auth token"].GetStringLength());

        } else {
            obj.account_sid = NULL;
        }

        if (sub.HasMember("auth token")) {
            strncpy(obj.auth_token, sub["auth token"].GetString(), sub["auth token"].GetStringLength());

        } else {
            obj.auth_token = NULL;
        }

    } else {
        obj.account_sid = NULL;
        obj.auth_token = NULL;
    }

    return obj;
}

/*
 * @brief Get the Mqtt Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the MQTT settings.
 * @return mqttObj with settings loaded on SUCCESS and
 *                   NULL pointers in mqttObj on failure
 */
mqttObj getMqttSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    mqttObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("broker url")) {
            strncpy(obj.set.brokerUrl, sub["broker url"].GetString(),
                    sub["broker url"].GetStringLength());

        } else {
            obj.set.brokerUrl[0] = '\0';
        }

        if (sub.HasMember("username")) {
            strncpy(obj.set.userName, sub["username"].GetString(),
                    sub["username"].GetStringLength());

        } else {
            obj.set.userName[0] = '\0';
        }

        if (sub.HasMember("password")) {
            strncpy(obj.set.password, sub["password"].GetString(),
                    sub["password"].GetStringLength());

        } else {
            obj.set.password[0] = '\0';
        }

        if (sub.HasMember("client id")) {
            strncpy(obj.set.clientId, sub["client id"].GetString(),
                    sub["client id"].GetStringLength());

        } else {
            obj.set.clientId[0] = '\0';
        }

    } else {
        obj.set.brokerUrl[0] = '\0';
    }

    return obj;
}

/*
 * @brief Get the AWS Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the AWS settings.
 * @return awsObj with settings loaded on SUCCESS and
 *                   NULL pointers in awsObj on failure
 */
awsObj getAwsSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    awsObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("broker url")) {
            strncpy(obj.set.endpoint, sub["broker url"].GetString(),
                    sub["broker url"].GetStringLength());

        } else {
            obj.set.endpoint[0] = '\0';
        }

        if (sub.HasMember("certificate dir")) {
            strncpy(obj.set.certDir, sub["certificate dir"].GetString(),
                    sub["certificate dir"].GetStringLength());

        } else {
            obj.set.certDir[0] = '\0';
        }

        if (sub.HasMember("root certificate")) {
            strncpy(obj.set.rootCA, sub["root certificate"].GetString(),
                    sub["root certificate"].GetStringLength());

        } else {
            obj.set.rootCA[0] = '\0';
        }
        if (sub.HasMember("client certificate")) {
            strncpy(obj.set.certName, sub["root certificate"].GetString(),
                    sub["client certificate"].GetStringLength());

        } else {
            obj.set.certName[0] = '\0';
        }
        if (sub.HasMember("private key")) {
            strncpy(obj.set.privKey, sub["private key"].GetString(),
                    sub["private key"].GetStringLength());

        } else {
            obj.set.privKey[0] = '\0';
        }

        if (sub.HasMember("port")) {
            obj.set.port = sub["port"].GetInt();

        } else {
            obj.set.port = 0;
        }

        if (sub.HasMember("client id")) {
            strncpy(obj.set.clientID, sub["client id"].GetString(),
                    sub["client id"].GetStringLength());

        } else {
            obj.set.clientID[0] = '\0';
        }

    } else {
        obj.set.endpoint[0] = '\0';
    }

    return obj;
}




/*
 * @brief Get the Influxdb Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the Influxdb settings.
 * @return influxdbObj with settings loaded on SUCCESS and
 *                   NULL pointers in influxdbObj on failure
 */
influxdbObj getInfluxdbSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    influxdbObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("influxdb url")) {
            strncpy(obj.set.dbUrl, sub["influxdb url"].GetString(),
                    sub["influxdb url"].GetStringLength());

        } else {
            obj.set.dbUrl[0] = '\0';
        }

        if (sub.HasMember("db name")) {
            strncpy(obj.set.dbName, sub["db name"].GetString(),
                    sub["db name"].GetStringLength());

        } else {
            obj.set.dbName[0] = '\0';
        }

    } else {
        obj.set.dbUrl[0] = '\0';
        obj.set.dbName[0] = '\0';
    }

    return obj;
}


/*
 * @brief Get the IEC 104 Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the IEC 104 settings.
 * @return iec104ClientObj with settings loaded on SUCCESS and
 *                   NULL pointers in iec104ClientObj on failure
 */
iec104ClientObj getIec104ClientSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    iec104ClientObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("address")) {
            strncpy(obj.set.ip, sub["address"].GetString(),
                    sub["address"].GetStringLength());

        } else {
            obj.set.ip[0] = '\0';
        }

        if (sub.HasMember("server certificate")) {
            strncpy(obj.set.serverCert, sub["server certificate"].GetString(),
                    sub["server certificate"].GetStringLength());

        } else {
            obj.set.serverCert[0] = '\0';
        }

        if (sub.HasMember("root certificate")) {
            strncpy(obj.set.rootCert, sub["root certificate"].GetString(),
                    sub["root certificate"].GetStringLength());

        } else {
            obj.set.rootCert[0] = '\0';
        }
        if (sub.HasMember("client certificate")) {
            strncpy(obj.set.clientCert, sub["root certificate"].GetString(),
                    sub["client certificate"].GetStringLength());

        } else {
            obj.set.clientCert[0] = '\0';
        }
        if (sub.HasMember("client key")) {
            strncpy(obj.set.clientKey, sub["client key"].GetString(),
                    sub["client key"].GetStringLength());

        } else {
            obj.set.clientKey[0] = '\0';
        }

        if (sub.HasMember("port")) {
            obj.set.port = sub["port"].GetInt();

        } else {
            obj.set.port = 0;
        }
        if (sub.HasMember("server address")) {
            obj.set.serverAddr = sub["server address"].GetInt();

        } else {
            obj.set.serverAddr = 0;
        }
        if (sub.HasMember("origin address")) {
            obj.set.originAddr = sub["origin address"].GetInt();

        } else {
            obj.set.originAddr = 0;
        }

    } else {
        obj.set.ip[0] = '\0';
    }

    return obj;
}

/*
 * @brief Get the Mqtt Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the MQTT settings.
 * @return mqttObj with settings loaded on SUCCESS and
 *                   NULL pointers in twilioObj on failure
 */
opcuaClientObj getOpcuaClientSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    opcuaClientObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("server url")) {
            strncpy(obj.set.url, sub["server url"].GetString(),
                    sub["server url"].GetStringLength());

        } else {
            obj.set.url[0] = '\0';
        }

        if (sub.HasMember("username")) {
            strncpy(obj.set.username, sub["username"].GetString(),
                    sub["username"].GetStringLength());

        } else {
            obj.set.username[0] = '\0';
        }

        if (sub.HasMember("password")) {
            strncpy(obj.set.password, sub["password"].GetString(),
                    sub["password"].GetStringLength());

        } else {
            obj.set.password[0] = '\0';
        }

    } else {
        obj.set.url[0] = '\0';
    }

    return obj;
}

/*
 * @brief Get the OPCUA server Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the OPCUA server settings.
 * @return opcuaServerObj with settings loaded on SUCCESS and
 *                   NULL pointers in opcuaServerObj on failure
 */
opcuaServerObj getOpcuaServerSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    opcuaServerObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("address")) {
            strncpy(obj.set.ipAddr, sub["address"].GetString(),
                    sub["address"].GetStringLength());

        } else {
            obj.set.ipAddr[0] = '\0';
        }

        if (sub.HasMember("port")) {
            obj.set.port =  sub["port"].GetInt();

        } else {
            obj.set.port = 0;
        }

    } else {
        obj.set.ipAddr[0] = '\0';
    }

    return obj;
}

/*
 * @brief Get the Modbus Settings from the JSON config file.
 *
 * @param jsonSubName JSON object name that contains the Modbus settings.
 * @return modbusObj with settings loaded on SUCCESS and
 *                   NULL pointers in modbusObj on failure
 */
modbusObj getModbusClientSettings(char *jsonSubName)
{
    int8_t ret = -1;
    Document sub;
    modbusObj obj;

    if (config.HasMember(jsonSubName)) {
        sub.CopyFrom(config[jsonSubName], config.GetAllocator());

        if (sub.HasMember("type")) {
            if (strncmp(sub["type"].GetString(), "tcp", sub["type"].GetStringLength() ) == 0) {
                obj.set.type = SI_MODBUS_TYPE_TCP;

            } else if (strncmp(sub["type"].GetString(), "rtu", sub["type"].GetStringLength() ) == 0) {
                obj.set.type = SI_MODBUS_TYPE_RTU;

            } else {
                obj.set.type = SI_MODBUS_TYPE_NONE;
            }

        } else {
            obj.set.type = SI_MODBUS_TYPE_NONE;
        }

        if (obj.set.type == SI_MODBUS_TYPE_RTU) {
            if (sub.HasMember("device")) {
                strncpy(obj.set.device, sub["device"].GetString(),
                        sub["device"].GetStringLength());

            } else {
                obj.set.device[0] = '\0';
            }

            if (sub.HasMember("baudrate")) {
                obj.set.baudrate = sub["baudrate"].GetInt();

            } else {
                obj.set.baudrate = 9600;
            }

        } else if (obj.set.type == SI_MODBUS_TYPE_TCP) {
            if (sub.HasMember("server ip")) {
                strncpy(obj.set.ip, sub["server ip"].GetString(),
                        sub["server ip"].GetStringLength());

            } else {
                obj.set.ip[0] = '\0';
            }

            if (sub.HasMember("port")) {
                obj.set.port = sub["port"].GetInt();

            } else {
                obj.set.port = 0;
            }
        }

    } else {
        obj.set.type = SI_MODBUS_TYPE_NONE;
    }

    return obj;
}
