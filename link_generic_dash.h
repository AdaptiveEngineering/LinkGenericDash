/*
 link_generic_dash.h - Link Generic Dash decoder library
 For copyright and license information see LICENSE

 Some optional defines you can add before including this file will configure
 this library for smaller devices by disabling non-essential features:

 #define NO_DASH_VALUE_STRINGS
 Will not include parameter names, their units of measurement or their min
 and max values - you can still get raw values by using the enums below but
 note the default units of measurement ie. all pressure values are kPa,
 all temperature values are °C and all time-based values are milliseconds..

 #define NO_FAULT_CODE_STRINGS
 Same as above, will not include fault code strings, meaning you won't be
 able to decode what a fault code number means.

 NO NEED TO EDIT BELOW THIS POINT UNLESS YOU *REALLY* NEED TO
 */

#ifndef link_generic_dash_h
#define link_generic_dash_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Maximum string length of any dash parameter name
 */
#define maxGenericDashParameterNameLength 24

/**
 * @brief Maximum string length of any unit of measurement
 */
#define maxGenericDashParameterUomLength 8

/**
 * @brief Maximum string length of any error message
 */
#define maxLinkECUFaultCodeStringLength 75

/**
 * @brief List of known parameters sent via Generic Dash
 */
typedef enum {
	ECU_ENGINE_SPEED_RPM,
	ECU_MAP_KPA,
	ECU_MGP_KPA,
	ECU_BAROMETRIC_PRESSURE_KPA,
	ECU_THROTTLE_POSITION_PERCENT,
	ECU_INJECTOR_DUTY_CYCLE_PERCENT,
	ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT,
	ECU_INJECTOR_PULSE_WIDTH_MS,
	ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C,
	ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C,
	ECU_BATTERY_VOLTAGE,
	ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND,
	ECU_GEAR_POSITION,
	ECU_INJECTOR_TIMING_DEGREES,
	ECU_IGNITION_TIMING_DEGREES,
	ECU_CAM_INLET_POSITION_L_DEGREES,
	ECU_CAM_INLET_POSITION_R_DEGREES,
	ECU_CAM_EXHAUST_POSITION_L_DEGREES,
	ECU_CAM_EXHAUST_POSITION_R_DEGREES,
	ECU_LAMBDA_1_LAMBDA,
	ECU_LAMBDA_2_LAMBDA,
	ECU_TRIGGER_1_ERROR_COUNT,
	ECU_FAULT_CODE,
	ECU_FUEL_PRESSURE_KPA,
	ECU_OIL_TEMPERATURE_DEGREES_C,
	ECU_OIL_PRESSURE_KPA,
	ECU_LEFT_FRONT_WHEEL_SPEED_KPH,
	ECU_LEFT_REAR_WHEEL_SPEED_KPH,
	ECU_RIGHT_FRONT_WHEEL_SPEED_KPH,
	ECU_RIGHT_REAR_WHEEL_SPEED_KPH,
	ECU_KNOCK_LEVEL_1_COUNT,
	ECU_KNOCK_LEVEL_2_COUNT,
	ECU_KNOCK_LEVEL_3_COUNT,
	ECU_KNOCK_LEVEL_4_COUNT,
	ECU_KNOCK_LEVEL_5_COUNT,
	ECU_KNOCK_LEVEL_6_COUNT,
	ECU_KNOCK_LEVEL_7_COUNT,
	ECU_KNOCK_LEVEL_8_COUNT,
	ECU_LIMIT_FLAGS_BITFIELD,
	ECU_ACCELERATOR_POSITION_PERCENT,
	ECU_ETHANOL_CONTENT_PERCENT,
	ECU_STATUS_BITFIELD,
} GenericDashParameters;
/**
 * @brief Total number of Generic Dash parameters
 */
#define Generic_Dash_Parameter_Count ECU_STATUS_BITFIELD + 1

/**
 * @brief List of known limits flags sent as ECU_LIMIT_FLAGS_BITFIELD
 */
typedef enum {
	LIMITS_FLAG_RPM_LIMIT,
	LIMITS_FLAG_MAP_LIMIT,
	LIMITS_FLAG_SPEED_LIMIT,
	LIMITS_FLAG_MAXIMUM_IGNITION_FLAG,
	LIMITS_FLAG_ANTI_LAG_IGNITION_CUT,
	LIMITS_FLAG_HIGH_VOLTAGE_SUPPLY_LIMIT,
	LIMITS_FLAG_OVERRUN_FLAG,
	LIMITS_FLAG_TRACTION_LIMIT,
	LIMITS_FLAG_LOW_VOLTAGE_SUPPLY_LIMIT,
	LIMITS_FLAG_LAUNCH_RPM_LIMIT,
	LIMITS_FLAG_WAKEUP_FLAG,
	LIMITS_FLAG_GP_RPM_LIMIT_1,
	LIMITS_FLAG_CL_STEPPER_LIMIT,
	LIMITS_FLAG_GP_RPM_LIMIT_2,
	LIMITS_FLAG_ETHROTTLE_LIMIT,
	LIMITS_FLAG_CYCLIC_IDLE_ACTIVE,
} GenericDashLimitFlags;
/**
 * @brief Total number of Generic Dash limit flags
 */
#define Generic_Dash_Limit_Flag_Count LIMITS_FLAG_CYCLIC_IDLE_ACTIVE + 1

/**
 * @brief List of known statuses sent via ECU_STATUS_BITFIELD
 */
typedef enum {
	STATUS_ANTI_LAG,
	STATUS_LAUNCH_CONTROL,
	STATUS_TRACTION_CONTROL,
	STATUS_CRUISE_CONTROL,
} GenericDashFeatureStatuses;
/**
 * @brief Total number of statuses
 */
#define Generic_Dash_Feature_Statuses_Count STATUS_CRUISE_CONTROL + 1

/**
 * @brief Anti-Lag states
 */
typedef enum {
	STATE_ANTI_LAG_SYSTEM_OFF,
	STATE_ANTI_LAG_ANTILAG_ACTIVE,
	STATE_ANTI_LAG_OFF_LOW_RPM,
	STATE_ANTI_LAG_ARMED_CYCLIC_OFF,
	STATE_ANTI_LAG_ARMED_CYCLIC_ACTIVE,
	STATE_ANTI_LAG_CYCLIC_COOLDOWN_ACTIVE,
	STATE_ANTI_LAG_DISARMED_CYCLIC_ACTIVE
} GenericDashStatesAntiLag;
/**
 * @brief Total number of Anti-Lag states
 */
#define Generic_Dash_States_AntiLag_Count STATE_ANTI_LAG_DISARMED_CYCLIC_ACTIVE + 1

/**
 * @brief Launch Control states
 */
typedef enum {
	STATE_LAUNCH_CONTROL_OFF,
	STATE_LAUNCH_CONTROL_ON_ACTIVE,
	STATE_LAUNCH_CONTROL_ON_INACTIVE
} GenericDashStatesLaunchControl;
/**
 * @brief Total number of Launch Control states
 */
#define Generic_Dash_States_Launch_Control_Count STATE_LAUNCH_CONTROL_ON_INACTIVE + 1

/**
 * @brief Traction Control states
 */
typedef enum {
	STATE_TRACTION_CONTROL_OFF,
	STATE_TRACTION_CONTROL_OFF_RPM_LOCKOUT,
	STATE_TRACTION_CONTROL_OFF_TPS_LOCKOUT,
	STATE_TRACTION_CONTROL_OFF_SPEED_LOCKOUT,
	STATE_TRACTION_CONTROL_READY,
	STATE_TRACTION_CONTROL_ACTIVE,
	STATE_TRACTION_CONTROL_DISABLED
} GenericDashStatesTractionControl;
/**
 * @brief Total number of Traction Control states
 */
#define Generic_Dash_States_Traction_Control_Count STATE_TRACTION_CONTROL_DISABLED + 1

/**
 * @brief Cruise Control states
 */
typedef enum {
	STATE_CRUISE_CONTROL_OFF,
	STATE_CRUISE_CONTROL_ENABLED,
	STATE_CRUISE_CONTROL_ACTIVE,
	STATE_CRUISE_CONTROL_STARTUP_LOCKOUT,
	STATE_CRUISE_CONTROL_MIN_RPM,
	STATE_CRUISE_CONTROL_MAX_RPM,
	STATE_CRUISE_CONTROL_CAN_ERROR
} GenericDashStatesCruiseControl;
/**
 * @brief Total number of Cruise Control states
 */
#define Generic_Dash_States_Cruise_Control_Count STATE_CRUISE_CONTROL_CAN_ERROR + 1

/**
 * @brief Amalgamated list of known fault codes between G4+, G4X and G5 boards
 */
typedef enum {
	ECU_FAULT_NONE = 0,
	ECU_FAULT_RPM_LIMIT_REACHED = 1,
	ECU_FAULT_MAP_LIMIT_REACHED = 2,
	ECU_FAULT_ETHANOL_SENSOR = 3,
	ECU_FAULT_INTERNAL_FAULT_4 = 4,
	ECU_FAULT_INTERNAL_FAULT_5 = 5,
	ECU_FAULT_INTERNAL_FAULT_6 = 6,
	ECU_FAULT_INTERNAL_FAULT_7 = 7,
	ECU_FAULT_INTERNAL_FAULT_8 = 8,
	ECU_FAULT_INTERNAL_FAULT_9 = 9,
	ECU_FAULT_ANVOLT_1_ERROR_HIGH = 10,
	ECU_FAULT_ANVOLT_1_ERROR_LOW = 11,
	ECU_FAULT_ANVOLT_1_ERROR_SIGNAL = 12,
	ECU_FAULT_ANVOLT_2_ERROR_HIGH = 13,
	ECU_FAULT_ANVOLT_2_ERROR_LOW = 14,
	ECU_FAULT_ANVOLT_2_ERROR_SIGNAL = 15,
	ECU_FAULT_ANVOLT_3_ERROR_HIGH = 16,
	ECU_FAULT_ANVOLT_3_ERROR_LOW = 17,
	ECU_FAULT_ANVOLT_3_ERROR_SIGNAL = 18,
	ECU_FAULT_ANVOLT_4_ERROR_HIGH = 19,
	ECU_FAULT_ANVOLT_4_ERROR_LOW = 20,
	ECU_FAULT_ANVOLT_4_ERROR_SIGNAL = 21,
	ECU_FAULT_ANVOLT_5_ERROR_HIGH = 22,
	ECU_FAULT_ANVOLT_5_ERROR_LOW = 23,
	ECU_FAULT_ANVOLT_5_ERROR_SIGNAL = 24,
	ECU_FAULT_ANVOLT_6_ERROR_HIGH = 25,
	ECU_FAULT_ANVOLT_6_ERROR_LOW = 26,
	ECU_FAULT_ANVOLT_6_ERROR_SIGNAL = 27,
	ECU_FAULT_ANVOLT_7_ERROR_HIGH = 28,
	ECU_FAULT_ANVOLT_7_ERROR_LOW = 29,
	ECU_FAULT_ANVOLT_7_ERROR_SIGNAL = 30,
	ECU_FAULT_ANVOLT_8_ERROR_HIGH = 31,
	ECU_FAULT_ANVOLT_8_ERROR_LOW = 32,
	ECU_FAULT_ANVOLT_8_ERROR_SIGNAL = 33,
	ECU_FAULT_ANVOLT_9_ERROR_HIGH = 34,
	ECU_FAULT_ANVOLT_9_ERROR_LOW = 35,
	ECU_FAULT_ANVOLT_9_ERROR_SIGNAL = 36,
	ECU_FAULT_ANVOLT_10_ERROR_HIGH = 37,
	ECU_FAULT_ANVOLT_10_ERROR_LOW = 38,
	ECU_FAULT_ANVOLT_10_ERROR_SIGNAL = 39,
	ECU_FAULT_ANVOLT_11_ERROR_HIGH = 40,
	ECU_FAULT_ANVOLT_11_ERROR_LOW = 41,
	ECU_FAULT_ANVOLT_11_ERROR_SIGNAL = 42,
	ECU_FAULT_ANTEMP_1_ERROR_HIGH = 43,
	ECU_FAULT_ANTEMP_1_ERROR_LOW = 44,
	ECU_FAULT_ANTEMP_1_SIGNAL_ERROR = 45,
	ECU_FAULT_ANTEMP_2_ERROR_HIGH = 46,
	ECU_FAULT_ANTEMP_2_ERROR_LOW = 47,
	ECU_FAULT_ANTEMP_2_SIGNAL_ERROR = 48,
	ECU_FAULT_ANTEMP_3_ERROR_HIGH = 49,
	ECU_FAULT_ANTEMP_3_ERROR_LOW = 50,
	ECU_FAULT_ANTEMP_3_SIGNAL_ERROR = 51,
	ECU_FAULT_ANTEMP_4_ERROR_HIGH = 52,
	ECU_FAULT_ANTEMP_4_ERROR_LOW = 53,
	ECU_FAULT_ANTEMP_4_SIGNAL_ERROR = 54,
	ECU_FAULT_INTERNAL_FAULT_55 = 55,
	ECU_FAULT_MAP_VALUE_TOO_HIGH = 56,
	ECU_FAULT_MAP_SIGNAL = 57,
	ECU_FAULT_MULTIPLE_REASONS_58 = 58,
	ECU_FAULT_MULTIPLE_REASONS_59 = 59,
	ECU_FAULT_MULTIPLE_REASONS_60 = 60,
	ECU_FAULT_MULTIPLE_REASONS_61 = 61,
	ECU_FAULT_ECT_TOO_HIGH = 62,
	ECU_FAULT_ECT_SIGNAL_ERROR = 63,
	ECU_FAULT_MULTIPLE_REASONS_64 = 64,
	ECU_FAULT_MULTIPLE_REASONS_65 = 65,
	ECU_FAULT_MULTIPLE_REASONS_66 = 66,
	ECU_FAULT_MULTIPLE_REASONS_67 = 67,
	ECU_FAULT_INTERNAL_FAULT_68 = 68,
	ECU_FAULT_ETHROTTLE_1_MAX_DUTY = 69,
	ECU_FAULT_ETHROTTLE_1_MIN_DUTY = 70,
	ECU_FAULT_ETHROTTLE_1_AUX9_10_SUPPLY_1 = 71,
	ECU_FAULT_ETHROTTLE_1_ANALOG_5V_SUPPLY = 72,
	ECU_FAULT_ETHROTTLE_1_AUX9_10_SUPPLY_2 = 73,
	ECU_FAULT_ANALOG_5V_SUPPLY = 74,
	ECU_FAULT_ETHROTTLE_1_TARGET = 75,
	ECU_FAULT_ETHROTTLE_1_TPS_TRACKING = 76,
	ECU_FAULT_APS_TRACKING = 77,
	ECU_FAULT_ETHROTTLE_1_TPS_MAIN = 78,
	ECU_FAULT_ETHROTTLE_1_TPS_SUB = 79,
	ECU_FAULT_ETHROTTLE_1_TPS_MAIN_ERROR_HIGH = 80,
	ECU_FAULT_ETHROTTLE_1_TPS_SUB_ERROR_HIGH = 81,
	ECU_FAULT_ETHROTTLE_1_TPS_NO_MAIN = 82,
	ECU_FAULT_ETHROTTLE_1_TPS_NO_SUB = 83,
	ECU_FAULT_ETHROTTLE_1_IC_OVERHEAT = 84,
	ECU_FAULT_APS_MAIN = 85,
	ECU_FAULT_APS_SUB = 86,
	ECU_FAULT_MULTIPLE_REASONS_9 = 87,
	ECU_FAULT_APS_SUB_ERROR_HIGH = 88,
	ECU_FAULT_APS_NO_MAIN = 89,
	ECU_FAULT_APS_NO_SUB = 90,
	ECU_FAULT_INTERNAL_FAULT_91 = 91,
	ECU_FAULT_APS_CAN_SIGNAL = 92,
	ECU_FAULT_ETHROTTLE_2_MAX_DUTY = 93,
	ECU_FAULT_ETHROTTLE_2_MIN_DUTY = 94,
	ECU_FAULT_ETHROTTLE_2_TARGET = 95,
	ECU_FAULT_ETHROTTLE_2_TPS_MAIN = 96,
	ECU_FAULT_ETHROTTLE_2_TPS_SUB = 97,
	ECU_FAULT_ETHROTTLE_2_TPS_TRACKING = 98,
	ECU_FAULT_AUX17_20_SUPPLY = 99,
	ECU_FAULT_ETHROTTLE_2_AUX17_20_SUPPLY = 100,
	ECU_FAULT_ANVOLT_12_ERROR_HIGH = 101,
	ECU_FAULT_ANVOLT_12_ERROR_LOW = 102,
	ECU_FAULT_ANVOLT_12_ERROR_SIGNAL = 103,
	ECU_FAULT_ANVOLT_13_ERROR_HIGH = 104,
	ECU_FAULT_ANVOLT_13_ERROR_LOW = 105,
	ECU_FAULT_ANVOLT_13_ERROR_SIGNAL = 106,
	ECU_FAULT_ANVOLT_14_ERROR_HIGH = 107,
	ECU_FAULT_ANVOLT_14_ERROR_LOW = 108,
	ECU_FAULT_ANVOLT_14_ERROR_SIGNAL = 109,
	ECU_FAULT_ANVOLT_15_ERROR_HIGH = 110,
	ECU_FAULT_ANVOLT_15_ERROR_LOW = 111,
	ECU_FAULT_ANVOLT_15_ERROR_SIGNAL = 112,
	ECU_FAULT_ANVOLT_16_ERROR_HIGH = 113,
	ECU_FAULT_ANVOLT_16_ERROR_LOW = 114,
	ECU_FAULT_ANVOLT_16_ERROR_SIGNAL = 115,
	ECU_FAULT_ETHROTTLE_2_ANALOG_5V_SUPPLY = 116,
	ECU_FAULT_ETHROTTLE_2_IC_OVERHEAT = 117,
	ECU_FAULT_DI_FUEL_PUMP_LOW = 118,
	ECU_FAULT_DI_FUEL_PUMP_HIGH = 119,
	ECU_FAULT_ETHROTTLE_CONTROL = 120,
	ECU_FAULT_ETHROTTLE_NO_RELAY = 121,
	ECU_FAULT_INJECTOR_MAX_DUTY = 122,
	ECU_FAULT_DI_DRIVER = 123,
} LinkECUFaultCodes;
/**
 * @brief Total number of Link ECU Fault Codes
 */
#define Link_ECU_Fault_Code_Count ECU_FAULT_DI_DRIVER + 1

/**
 * @brief Parse the Link Generic Dash CAN frames ready for later use
 * @param frame is an 8 unsigned char bytes CAN frame to decode
 * @return true if successfully decoded, false otherwise
 */
bool parseGenericDashCanFrame(unsigned char frame[8]);

/**
 * @brief Get a specific value from the Generic Dash buffer
 * @param param is one of enum GenericDashParameters to return
 * @return float value of the requested parameter
 */
float getGenericDashValue(GenericDashParameters param);

/**
 * @brief Get a specific limit flag from the Generic Dash Buffer
 * @param param is one of enum GenericDashLimitFlags to return
 * @return bool value of the requested limit flag
 */
bool getGenericDashLimitFlag(GenericDashLimitFlags param);

/**
 * @brief Get a specific feature status from the Generic Dash Buffer
 * @param param is one of enum GenericDashLimitFlags to return
 * @return unsigned char value of the requested feature status
 */
unsigned char getGenericDashFeatureStatus(GenericDashFeatureStatuses param);

#ifndef NO_DASH_VALUE_STRINGS

/**
 * @brief Gets human-readable data for a given GenericDashParameters
 * @param param is one of enum GenericDashParameters to return
 * @param dashParameterInfo is a char array pointer that will get filled with the requested data
 * @return int value of the number of bytes written to dashParameterInfo (0 on failure)
 */
int getGenericDashParameterName(GenericDashParameters param, char* dashParameterInfo);

/**
 * @brief Gets the unit of measurement for a given GenericDashParameters
 * @param param is one of enum GenericDashParameters to return
 * @param dashParameterUom is a char array pointer that will get filled with the requested data
 * @return int value of the number of bytes written to dashParameterUom (0 on failure)
 */
int getGenericDashParameterUom(GenericDashParameters param, char* dashParameterUom);

/**
 * @brief Gets the requested numerical parameter for a given GenericDashParameters
 * @param param is one of enum GenericDashParameters to return
 * @return signed int value of the requested numerical parameter or INT_MIN on failure
 */
signed int getGenericDashParameterDecimalPlaces(GenericDashParameters param);
signed int getGenericDashParameterMinimumValue(GenericDashParameters param);
signed int getGenericDashParameterMaximumValue(GenericDashParameters param);

/**
 * @brief Gets a human-readable name for a given GenericDashLimitFlags
 * @param param is one of enum GenericDashLimitFlags to return
 * @param dashLimitFlagInfo is a char array pointer that will get filled with the requested data
 * @return int value of the number of bytes written to dashLimitFlagInfo (0 on failure)
 */
int getGenericDashLimitFlagName(GenericDashLimitFlags param, char* dashLimitFlagInfo);

#endif // NO_DASH_VALUE_STRINGS

#ifndef NO_FAULT_CODE_STRINGS

/**
 * @brief Gets a human-readable description for a given LinkECUFaultCodes
 * @param param is one of enum LinkECUFaultCodes to return
 * @param faultCodeInfo is a char array pointer that will get filled with the requested data
 * @return int value of the number of bytes written to faultCodeInfo (0 on failure)
 */
int getLinkECUFaultCode(LinkECUFaultCodes param, char* faultCodeInfo);

#endif // NO_FAULT_CODE_STRINGS

#ifdef __cplusplus
}
#endif

#endif // link_generic_dash_h