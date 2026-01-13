/*
 Any additions to this file will need suitable additions to link_generic_dash.h
 For documentation please the above file.
 */

#include "link_generic_dash.h"

#define GenericDashFrames 14
#define GenericDashBytes 8
unsigned char GenericDash[GenericDashFrames][GenericDashBytes];

bool parseGenericDashCanFrame(unsigned char frame[8]) {
	if ((frame[0] >= GenericDashFrames) || (frame[1] != 0)) return false;
	for (int i = 0; i < sizeof(GenericDash[0]); i++) GenericDash[frame[0]][i] = frame[i];
	return true;
}

float getGenericDashValue(GenericDashParameters param) {
	switch (param) {
		case ECU_ENGINE_SPEED_RPM:
			return (signed int)((GenericDash[0][3] << 8) + (GenericDash[0][2] << 0));
			break;
		case ECU_MAP_KPA:
			return (signed int)((GenericDash[0][5] << 8) + (GenericDash[0][4] << 0));
			break;
		case ECU_MGP_KPA:
			return (signed int)((GenericDash[0][7] << 8) + (GenericDash[0][6] << 0)) - 100;
			break;
		case ECU_BAROMETRIC_PRESSURE_KPA:
			return (signed int)((GenericDash[1][3] << 8) + (GenericDash[1][2] << 0)) * 0.1;
			break;
		case ECU_THROTTLE_POSITION_PERCENT:
			return (signed int)((GenericDash[1][5] << 8) + (GenericDash[1][4] << 0)) * 0.1;
			break;
		case ECU_INJECTOR_DUTY_CYCLE_PERCENT:
			return (signed int)((GenericDash[1][7] << 8) + (GenericDash[1][6] << 0)) * 0.1;
			break;
		case ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT:
			return (signed int)((GenericDash[2][3] << 8) + (GenericDash[2][2] << 0)) * 0.1;
			break;
		case ECU_INJECTOR_PULSE_WIDTH_MS:
			return (signed int)((GenericDash[2][5] << 8) + (GenericDash[2][4] << 0)) * 0.001;
			break;
		case ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C:
			return (signed int)((GenericDash[2][7] << 8) + (GenericDash[2][6] << 0)) - 50;
			break;
		case ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C:
			return (signed int)((GenericDash[3][3] << 8) + (GenericDash[3][2] << 0)) - 50;
			break;
		case ECU_BATTERY_VOLTAGE:
			return (signed int)((GenericDash[3][5] << 8) + (GenericDash[3][4] << 0)) * 0.01;
			break;
		case ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND:
			return (signed int)((GenericDash[3][7] << 8) + (GenericDash[3][6] << 0)) * 0.1;
			break;
		case ECU_GEAR_POSITION:
			return (signed int)((GenericDash[4][3] << 8) + (GenericDash[4][2] << 0));
			break;
		case ECU_INJECTOR_TIMING_DEGREES:
			return (signed int)((GenericDash[4][5] << 8) + (GenericDash[4][4] << 0));
			break;
		case ECU_IGNITION_TIMING_DEGREES:
			return (signed int)(((GenericDash[4][7] << 8) + (GenericDash[4][6] << 0)) * 0.1) - 100;
			break;
		case ECU_CAM_INLET_POSITION_L_DEGREES:
			return (signed int)((GenericDash[5][3] << 8) + (GenericDash[5][2] << 0)) * 0.1;
			break;
		case ECU_CAM_INLET_POSITION_R_DEGREES:
			return (signed int)((GenericDash[5][5] << 8) + (GenericDash[5][4] << 0)) * 0.1;
			break;
		case ECU_CAM_EXHAUST_POSITION_L_DEGREES:
			return (signed int)((GenericDash[5][7] << 8) + (GenericDash[5][6] << 0)) * -0.1;
			break;
		case ECU_CAM_EXHAUST_POSITION_R_DEGREES:
			return (signed int)((GenericDash[6][3] << 8) + (GenericDash[6][2] << 0)) * -0.1;
			break;
		case ECU_LAMBDA_1_LAMBDA:
			return (signed int)((GenericDash[6][5] << 8) + (GenericDash[6][4] << 0)) * 0.001;
			break;
		case ECU_LAMBDA_2_LAMBDA:
			return (signed int)((GenericDash[6][7] << 8) + (GenericDash[6][6] << 0)) * 0.001;
			break;
		case ECU_TRIGGER_1_ERROR_COUNT:
			return (signed int)((GenericDash[7][3] << 8) + (GenericDash[7][2] << 0));
			break;
		case ECU_FAULT_CODE:
			return (signed int)((GenericDash[7][5] << 8) + (GenericDash[7][4] << 0));
			break;
		case ECU_FUEL_PRESSURE_KPA:
			return (signed int)((GenericDash[7][7] << 8) + (GenericDash[7][6] << 0));
			break;
		case ECU_OIL_TEMPERATURE_DEGREES_C:
			return (signed int)((GenericDash[8][3] << 8) + (GenericDash[8][2] << 0)) - 50;
			break;
		case ECU_OIL_PRESSURE_KPA:
			return (signed int)((GenericDash[8][5] << 8) + (GenericDash[8][4] << 0));
			break;
		case ECU_LEFT_FRONT_WHEEL_SPEED_KPH:
			return (signed int)((GenericDash[8][7] << 8) + (GenericDash[8][6] << 0)) * 0.1;
			break;
		case ECU_LEFT_REAR_WHEEL_SPEED_KPH:
			return (signed int)((GenericDash[9][3] << 8) + (GenericDash[9][2] << 0)) * 0.1;
			break;
		case ECU_RIGHT_FRONT_WHEEL_SPEED_KPH:
			return (signed int)((GenericDash[9][5] << 8) + (GenericDash[9][4] << 0)) * 0.1;
			break;
		case ECU_RIGHT_REAR_WHEEL_SPEED_KPH:
			return (signed int)((GenericDash[9][7] << 8) + (GenericDash[9][6] << 0)) * 0.1;
			break;
		case ECU_KNOCK_LEVEL_1_COUNT:
			return (signed int)((GenericDash[10][3] << 8) + (GenericDash[10][2] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_2_COUNT:
			return (signed int)((GenericDash[10][5] << 8) + (GenericDash[10][4] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_3_COUNT:
			return (signed int)((GenericDash[10][7] << 8) + (GenericDash[10][6] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_4_COUNT:
			return (signed int)((GenericDash[11][3] << 8) + (GenericDash[11][2] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_5_COUNT:
			return (signed int)((GenericDash[11][5] << 8) + (GenericDash[11][4] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_6_COUNT:
			return (signed int)((GenericDash[11][7] << 8) + (GenericDash[11][6] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_7_COUNT:
			return (signed int)((GenericDash[12][3] << 8) + (GenericDash[12][2] << 0)) * 5;
			break;
		case ECU_KNOCK_LEVEL_8_COUNT:
			return (signed int)((GenericDash[12][5] << 8) + (GenericDash[12][4] << 0)) * 5;
			break;
		case ECU_LIMIT_FLAGS_BITFIELD:
			return (signed int)((GenericDash[12][7] << 8) + (GenericDash[12][6] << 0));
			break;
		case ECU_ACCELERATOR_POSITION_PERCENT:
			return (signed int)((GenericDash[13][3] << 8) + (GenericDash[13][2] << 0)) * 0.1;
			break;
		case ECU_ETHANOL_CONTENT_PERCENT:
			return (signed int)((GenericDash[13][5] << 8) + (GenericDash[13][4] << 0)) * 0.1;
			break;
		case ECU_STATUS_BITFIELD:
			return (signed int)((GenericDash[13][7] << 8) + (GenericDash[13][6] << 0));
			break;
		default:
			return -1;
			break;
	}
}

bool getGenericDashLimitFlag(GenericDashLimitFlags param) {
		unsigned int flags = (unsigned int)getGenericDashValue(ECU_LIMIT_FLAGS_BITFIELD);
		return (bool)((flags >> (unsigned int)param) & 0x1);
}

unsigned char getGenericDashFeatureStatus(GenericDashFeatureStatuses param) {
		unsigned int statuses = (unsigned int)getGenericDashValue(ECU_STATUS_BITFIELD);
		switch (param) {
		case STATUS_ANTI_LAG:
				return (unsigned char)((statuses >> 0x5) & 0x7);
				break;
		case STATUS_LAUNCH_CONTROL:
				return (unsigned char)((statuses >> 0x3) & 0x3);
				break;
		case STATUS_TRACTION_CONTROL:
				return (unsigned char)((statuses >> 0x0) & 0x7);
				break;
		case STATUS_CRUISE_CONTROL:
				return (unsigned char)((statuses >> 0xC) & 0x7);
				break;
		default:
				return -1;
				break;
		}
}

#ifndef NO_DASH_VALUE_STRINGS

/*
 Dash parameters packed in the format:
 "Friendly Name|Units of measurement|Decimal Places|Lowest Possible Value|Highest Possible Value"
 */
const char *GenericDashParameterNames[] = {
  "Engine Speed|RPM|0|0|15000",
  "Manifold Abs. Pres.|kPa|0|0|650",
  "Manifold Gauge Pres.|kPa|0|-100|550",
  "Barometric Pressure|kPa|0|0|200",
  "Throttle Position|%|1|0|100",
  "Injector Duty Cycle|%|1|0|100",
  "Secondary Injector DC|%|1|0|100",
  "Injector Pulse Width|ms|2|0|65",
  "Engine Coolant Temp|°C|0|-50|205",
  "Intake Air Temp|°C|0|-20|205",
  "Battery Voltage|V|2|0|65",
  "Mass Air Flow|g/s|1|0|6500",
  "Gear Position| |0|0|15",
  "Injector Timing|°|0|0|719",
  "Ignition Timing|°|1|-100|100",
  "Cam Inlet Position L|°|1|0|60",
  "Cam Inlet Position R|°|1|0|60",
  "Cam Exhaust Position L|°|1|-60|0",
  "Cam Exhaust Position R|°|1|-60|0",
  "Lambda Sensor 1|λ|3|0|3",
  "Lambda Sensor 2|λ|3|0|3",
  "Trigger 1 Errors|total|0|0|255",
  "Fault Codes|code|0|0|255",
  "Fuel Pressure|kPa|0|0|6550",
  "Oil Temp|°C|0|-50|205",
  "Oil Pressure|kPa|0|0|6550",
  "LF Wheel Speed|KPH|1|0|1000",
  "LR Wheel Speed|KPH|1|0|1000",
  "RF Wheel Speed|KPH|1|0|1000",
  "RR Wheel Speed|KPH|1|0|1000",
  "Knock Level Cyl 1|level|0|0|1000",
  "Knock Level Cyl 2|level|0|0|1000",
  "Knock Level Cyl 3|level|0|0|1000",
  "Knock Level Cyl 4|level|0|0|1000",
  "Knock Level Cyl 5|level|0|0|1000",
  "Knock Level Cyl 6|level|0|0|1000",
  "Knock Level Cyl 7|level|0|0|1000",
  "Knock Level Cyl 8|level|0|0|1000",
  "Limit Flags| |0|0|65535",
  "Accelerator Position|%|1|0|100",
  "Ethanol Content|%|0|0|100",
  "Statuses| |0|0|65535",
};

int linkGenericDashSplitString(const char* inputArray, const char* inputDelimeter, int itemIndex, char* outputArray) {
	int i = 0;
	char buffer[strlen(inputArray)];
	strcpy(buffer, inputArray);
	char* itemPtr = strtok(buffer, inputDelimeter);
	while (itemPtr != NULL) {
		if (i == itemIndex) return sprintf(outputArray, "%s", itemPtr);
		itemPtr = strtok(NULL, inputDelimeter); i++;
	}
	return 0;
}

int getGenericDashParameterName(GenericDashParameters param, char* dashParameterInfo) {
	if ((int)param < 0 || (int)param > Generic_Dash_Parameter_Count) return 0;
	return linkGenericDashSplitString(GenericDashParameterNames[param], "|", 0, dashParameterInfo);
}

int getGenericDashParameterUom(GenericDashParameters param, char* dashParameterUom) {
	if ((int)param < 0 || (int)param > Generic_Dash_Parameter_Count) return 0;
	return linkGenericDashSplitString(GenericDashParameterNames[param], "|", 1, dashParameterUom);
}

signed int getGenericDashParameterDecimalPlaces(GenericDashParameters param) {
	if ((int)param < 0 || (int)param > Generic_Dash_Parameter_Count)
		return INT_MIN;
	char numberBuffer[maxGenericDashParameterNameLength];
	int returnVal = linkGenericDashSplitString(GenericDashParameterNames[param], "|", 2, numberBuffer);
	if (returnVal == 0)
		return INT_MIN;
	return strtol(numberBuffer, NULL, 10);
}

signed int getGenericDashParameterMinimumValue(GenericDashParameters param) {
	if ((int)param < 0 || (int)param > Generic_Dash_Parameter_Count)
		return INT_MIN;
	char numberBuffer[maxGenericDashParameterNameLength];
	int returnVal = linkGenericDashSplitString(GenericDashParameterNames[param], "|", 3, numberBuffer);
	if (returnVal == 0)
		return INT_MIN;
	return strtol(numberBuffer, NULL, 10);
}

signed int getGenericDashParameterMaximumValue(GenericDashParameters param) {
	if ((int)param < 0 || (int)param > Generic_Dash_Parameter_Count)
		return INT_MIN;
	char numberBuffer[maxGenericDashParameterNameLength];
	int returnVal = linkGenericDashSplitString(GenericDashParameterNames[param], "|", 4, numberBuffer);
	if (returnVal == 0)
		return INT_MIN;
	return strtol(numberBuffer, NULL, 10);
}

/*
 Limit flags
 */
const char *GenericDashLimitFlagsNames[] = {
  "RPM Limit",
  "MAP Limit",
  "Speed Limit",
  "Max Ign Timing",
  "Anti-Lag Ign Cut",
  "ECU High Voltage",
  "Overrun",
  "Traction Limit",
  "ECU Low Voltage",
  "Launch RPM Limit",
  "Wakeup",
  "GP RPM Limit 1",
  "Max ISC Steps",
  "GP RPM Limit 2",
  "E-Throttle Limit",
  "Cyclic Idle",
};

int getGenericDashLimitFlagName(GenericDashLimitFlags param, char* dashLimitFlagInfo) {
	if ((int)param < 0 || (int)param > Generic_Dash_Limit_Flag_Count) return 0;
	return sprintf(dashLimitFlagInfo, "%s", GenericDashLimitFlagsNames[param]);
}

#endif // NO_DASH_VALUE_STRINGS


#ifndef NO_FAULT_CODE_STRINGS

/*
 Link ECU Fault Codes - Must be kept in lockstep with enum LinkECUFaultCodes
 */
const char *LinkECUFaultCodeStrings[] = {
	"No Fault",
	"RPM limit reached",
	"MAP limit reached",
	"Ethanol Sensor Fault",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"Consult Link Dealership",
	"An Volt 1 above Error High Value",
	"An Volt 1 below Error Low Value",
	"An Volt 1 Signal Error",
	"An Volt 2 above Error High Value",
	"An Volt 2 below Error Low Value",
	"An Volt 2 Signal Error",
	"An Volt 3 above Error High Value",
	"An Volt 3 below Error Low Value",
	"An Volt 3 Signal Error",
	"An Volt 4 above Error High Value",
	"An Volt 4 below Error Low Value",
	"An Volt 4 Signal Error",
	"An Volt 5 above Error High Value",
	"An Volt 5 below Error Low Value",
	"An Volt 5 Signal Error",
	"An Volt 6 above Error High Value",
	"An Volt 6 below Error Low Value",
	"An Volt 6 Signal Error",
	"An Volt 7 above Error High Value",
	"An Volt 7 below Error Low Value",
	"An Volt 7 Signal Error",
	"An Volt 8 above Error High Value",
	"An Volt 8 below Error Low Value",
	"An Volt 8 Signal Error",
	"An Volt 9 above Error High Value",
	"An Volt 9 below Error Low Value",
	"An Volt 9 Signal Error",
	"An Volt 10 above Error High Value",
	"An Volt 10 below Error Low Value",
	"An Volt 10 Signal Error",
	"An Volt 11 above Error High Value",
	"An Volt 11 below Error Low Value",
	"An Volt 11 Signal Error",
	"An Temp 1 above Error High Value",
	"An Temp 1 below Error Low Value",
	"An Temp 1 Signal Error",
	"An Temp 2 above Error High Value",
	"An Temp 2 below Error Low Value",
	"An Temp 2 Signal Error",
	"An Temp 3 above Error High Value",
	"An Temp 3 below Error Low Value",
	"An Temp 3 Signal Error",
	"An Temp 4 above Error High Value",
	"An Temp 4 below Error Low Value",
	"An Temp 4 Signal Error",
	"Consult Link Dealership",
	"MAP Above Fault Code Value",
	"MAP Signal Error",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"ECT Above Fault Code Value",
	"ECT Signal Error",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"See Link Manual",
	"Consult Link Dealership",
	"E-Throttle 1 Max %DC Limit",
	"E-Throttle 1 Min %DC Limit",
	"Aux 9/10 Supply Error - E-Throttle",
	"Analog 5V Supply Error - E-Throttle (E-Throttle Sensor Supply Voltage)",
	"Aux 9/10 Supply Error - E-Throttle",
	"Analog 5V Supply Error",
	"E-Throttle 1 TPS /Target Error",
	"TPS(main) /TPS(sub) tracking Error",
	"APS(main) /APS(sub) tracking Error",
	"TPS(Main) Fault - E-Throttle.",
	"TPS(Sub) Fault - E-Throttle",
	"TPS(Main) Above Fault Code Value",
	"TPS(Sub) Above Fault Code Value",
	"TPS(Main) Not Selected",
	"TPS(Sub) Not Selected",
	"Aux9/10 E-Throttle IC Over Temp / Under Voltage",
	"APS(Main) Fault - E-Throttle.",
	"APS(Sub) Fault - E-Throttle",
	"See Link Manual",
	"APS(Sub) Above Fault Code Value",
	"APS(Main) Not Selected",
	"APS(Sub) Not Selected",
	"Consult Link Dealership",
	"APS CAN Signal Lost",
	"E-Throttle 2 Max %DC Limit",
	"E-Throttle 2 Min %DC Limit",
	"E-Throttle 2 TPS 2 /Target Error",
	"TPS 2 (Main) Fault - E-Throttle 2",
	"TPS 2 (Sub) Fault - E-Throttle 2",
	"TPS 2 (Main) / TPS 2 (Sub) tracking Error",
	"Aux 17-20 Supply Error",
	"Aux 17-20 Supply Error - E-Throttle",
	"An Volt 12 above Error High Value",
	"An Volt 12 below Error Low Value",
	"An Volt 12 Signal Error",
	"An Volt 13 above Error High Value",
	"An Volt 13 below Error Low Value",
	"An Volt 13 Signal Error",
	"An Volt 14 above Error High Value",
	"An Volt 14 below Error Low Value",
	"An Volt 14 Signal Error",
	"An Volt 15 above Error High Value",
	"An Volt 15 below Error Low Value",
	"An Volt 15 Signal Error",
	"An Volt 16 above Error High Value",
	"An Volt 16 below Error Low Value",
	"An Volt 16 Signal Error",
	"Analog 5V Supply Error - E-Throttle 2 (E-Throttle 2 Sensor Supply Voltage)",
	"Aux 17-20 E-Throttle IC Over Temp / Under Voltage",
	"DI Fuel Pump Control Low Pressure Fault",
	"DI Fuel Pump Control High Pressure Fault",
	"Ethrottle Control Error",
	"Ethrottle No Relay Selected",
	"Maximum Injector Duty Cycle Reached",
	"DI Driver Fault"
};

int getLinkECUFaultCode(LinkECUFaultCodes param, char* faultCodeInfo) {
	if ((int)param < 0 || (int)param > Link_ECU_Fault_Code_Count) return 0;
	return sprintf(faultCodeInfo, "%s", LinkECUFaultCodeStrings[param]);
}

#endif // NO_FAULT_CODE_STRINGS
