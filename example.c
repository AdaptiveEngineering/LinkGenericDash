/*
 example.c - A quick demo of the library

 Compile this with something like:
  gcc link_generic_dash.c example.c -o example

 Output should then be the following:

 Fuel Pressure is currently 300 kPa
 Fuel Pressure minimum possible value is 0 kPa, maximum possible value is 6550 kPa
 Fault code 15: An Volt 2 Signal Error

 */

#include "link_generic_dash.h"
#include <stdio.h>

char parameterName[maxGenericDashParameterNameLength];
char unitOfMeasurements[maxGenericDashParameterUomLength];

int main() {
  /*
   Generate a fake GenericDash CAN frame #8 with the following information:

   * Trig 1 Error Counter of 0
   * Fault Codes = 15
   * Fuel Pressure of 300 kPa

   */
  unsigned char sample_can_frame[] = { 0x7, 0x0, 0x0, 0x0, 0xF, 0x0, 0x2C, 0x1 };

  /*
   Feed that frame into the parser and throw error if it's invalid
   */
  if (!parseGenericDashCanFrame(sample_can_frame)) {
    printf("Unable to parse CAN frame!\n");
    return 1;
  }

  /*
   Get and display our fuel pressure
   Includes decimal point processing even if fuel pressure does not have a decimal point
   so that if you copy-paste from this you've got something workable
   */
  GenericDashParameters desiredParameter = ECU_FUEL_PRESSURE_KPA;

  float parameter_value = getGenericDashValue(desiredParameter);
  int parameter_name_length = getGenericDashParameterName(desiredParameter, parameterName);
  int parameter_uom_length = getGenericDashParameterUom(desiredParameter, unitOfMeasurements);
  signed int parameter_dp = getGenericDashParameterDecimalPlaces(desiredParameter);

  if (parameter_name_length != 0 && parameter_uom_length != 0 && parameter_dp != INT_MIN) {
    char format_string[26];
    sprintf(format_string, "%%s is currently %%0.%if %%s\n", parameter_dp);
    printf(format_string, parameterName, parameter_value, unitOfMeasurements);
  } else {
    printf("Unable to get specified parameter information!\n%i %i %i %i\n", parameter_name_length, parameter_uom_length, parameter_dp, Generic_Dash_Parameter_Count);
    return 1;
  }

  /*
   Might as well display our min and max values
   */
  signed int parameter_min_value = getGenericDashParameterMinimumValue(desiredParameter);
  signed int parameter_max_value = getGenericDashParameterMaximumValue(desiredParameter);

  if (parameter_min_value != INT_MIN && parameter_max_value != INT_MIN) {
    printf("%s minimum possible value is %i %s, maximum possible value is %i %s\n", parameterName, parameter_min_value, unitOfMeasurements, parameter_max_value, unitOfMeasurements);
  } else {
    printf("Unable to get min and max information!\n");
    return 1;
  }

  /*
   * Display any current fault code
   */
  char faultCodeDescription[maxLinkECUFaultCodeStringLength];
  LinkECUFaultCodes fault_code = (LinkECUFaultCodes)getGenericDashValue(ECU_FAULT_CODE);

  if (fault_code != ECU_FAULT_NONE) {
    if (getLinkECUFaultCode(fault_code, faultCodeDescription) != 0) {
      printf("Fault code %i: %s\n", (int)fault_code, faultCodeDescription);
    } else {
      printf("There was a fault code but we could not decode it!\n");
      return 1;
    }
  }

  return 0;
}