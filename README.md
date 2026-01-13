
<!-- omit in toc -->
# Link Generic Dash decoder

<!-- toc -->
- [Purpose](#purpose)
- [Acknowledgements](#acknowledgements)
- [Contributing](#contributing)
- [Goals](#goals)
- [Installation](#installation)
  - [PlatformIO](#platformio)
  - [Arduino IDE](#arduino-ide)
  - [Raw-dogging it](#raw-dogging-it)
  - [Enabling in your code](#enabling-in-your-code)
- [Basic Usage](#basic-usage)
- [Function List](#function-list)
- [Changelog](#changelog)

<!-- tocstop -->

## Purpose

This C library parses the Link Generic Dash CAN Frame stream. Feed it received
CAN frames and it will maintain a list of Generic Dash values, fault codes and
statuses that you can access elsewhere in your project.

## Acknowledgements

[Link Engine Management Limited](https://linkecu.com/) (aka "_Link_" in any
other files in this repository) for their awesome ECUs and documentation.
 
## Contributing

Feel free to raise pull requests, we will review contributions within due
course and if we use your code we will add your contributions below.

## Goals

The goal of this project is to target widescale compatibility, with the hope
this code will work as well on small Arduino-like microcontrollers all the way
up to full-blown Raspberry Pi-like small board computers.

Because of this goal, the code here is highly optimised, not particularly easy
to read in places and returns data in legacy ways. It's designed for speed and
to use as little RAM as possible. This readme will guide you through it though.

## Installation

This library should be compatible with both PlatformIO and Arduino IDE.

### PlatformIO

PlatformIO users add this to your `platformio.ini` file under `lib_deps`:

```ini
	AdaptiveEngineering/LinkGenericDash@^1.0.0
```

### Arduino IDE

Arduino IDE users should locate the package within the Arduino Library Manager
and install it like any other library.

### Raw-dogging it

Brave. Just download the .zip file and extract link_generic_dash.* into your
projects source folder.

### Enabling in your code

Adding the following will enable this library in your code:

```c
#include "link_generic_dash.h"
```

If you need to limit the footprint of this library, you can selectively disable
features as required by adding the following before the above `#include` line:
- `#define NO_FAULT_CODE_STRINGS` will remove all fault code strings - this
  will dramatically reduce requirements of this library but the following calls
  will no longer be available:
  - `getGenericDashParameterName`
  - `getGenericDashLimitFlagName`
- `#define NO_DASH_VALUE_STRINGS` can be used if you _really_ need to scrape
  the barrel to reduce resource usage and this is ideal for ATTiny85-like
  devices but the following calls will no longer be available:
  - `getLinkECUFaultCode`

## Basic Usage

Start by including the above header. You will then need to feed CAN frames to
the library as they are received with the `parseGenericDashCanFrame` function.

This function takes an 8 byte unsigned char array and returns a boolean true
or false on whether the frames were processed successfully.

Here is an example based off the ESP32-Arduino-CAN library:

```c
/* Logic before this snippet gets CAN frames in some kind of loop */
if (received_can_frame.MsgID == 1000) { // CAN ID 1000 configurable in PCLink
	unsigned char DashCanFrame[8];
	for (int i = 0; i < 8; i++) DashCanFrame[i] = received_can_frame.data.u8[i];
	if (!parseGenericDashCanFrame(DashCanFrame)) {
		/* Do something here to handle errors */
	}
}
```

To get data back out, when drawing a screen for example, request as follows:

```c
// Default return format is float to cover values with decimal places
float throttle_percentage = getGenericDashValue(ECU_THROTTLE_POSITION_PERCENT); // 45.4%

// You can cast as you request the data as well
unsigned int engine_rpm = (unsigned int)getGenericDashValue(ECU_ENGINE_SPEED_RPM); // 5252
```

## Function list

All of the below functions are documented in `link_generic_dash.h` in such a
way that PlatformIO / VSCode / Doxygen picks them up nicely. Here you can
find some usage examples as well:

#### bool parseGenericDashCanFrame(unsigned char frame[8]);

This is described in the [Basic Usage](#basic-usage) section above. Feeding
this CAN frames with the desired CAN ID will update the internal registers
so you can poll this library for the information you desire. It returns true
on successful decode or false if it couldn't be decoded.

#### float getGenericDashValue(GenericDashParameters param);

This is also described in the [Basic Usage](#basic-usage) section above,
you can find a list of requestable values in `link_generic_dash.h`.

All values are returned as float even if you'd expect otherwise. This is to
simplify the code and cover all eventualities. Just typecast it to what you
need ie. `(unsigned int)getGenericDashValue(ECU_ENGINE_SPEED_RPM);`

The following dash values require special consideration:

- `ECU_FAULT_CODE` returns a fault code or `ECU_FAULT_NONE` if there are none.
  If there are two or more fault codes this value will cycle through each fault
  code, pausing for 2 seconds or so on each code. Don't assume a fault code has
  cleared just based off not seeing it again - only when `ECU_FAULT_NONE` is
  returned can you truly expect all fault codes have been cleared
- `ECU_LIMIT_FLAGS_BITFIELD` returns the raw value for the limit flags bitfield
  and it is best to use the `getGenericDashLimitFlag` function below to get
  these in a more usable boolean format
- `ECU_STATUS_BITFIELD` is much the same as ECU_LIMIT_FLAGS_BITFIELD above and
  has its own helper function `getGenericDashFeatureStatus` as documented below

#### bool getGenericDashLimitFlag(GenericDashLimitFlags param);

A limit flag is a boolean true / false on whether a particular limit or feature
in the Link ECU is currently active, for example the RPM or speed limiters, or
if cyclic idle is active or if idle stepper motor has reached its limits.

Usage example:

```c
  if (getGenericDashLimitFlag(LIMITS_FLAG_RPM_LIMIT)) {
    printf("You are hitting the rev limiter!\n");
  }
```

The full list of limit flags can be found in `link_generic_dash.h`.

#### unsigned char getGenericDashFeatureStatus(GenericDashFeatureStatuses param);

This operates similar to the limit flags above but gets the status of one of
a few additional Link ECU features such as launch control, cruise control etc.
Each dash feature has their own subset of statuses to compare against.

Usage example:

```c
  switch (getGenericDashFeatureStatus(STATUS_LAUNCH_CONTROL)) {
    case STATE_LAUNCH_CONTROL_OFF:
      printf("Launch control is turned off\n");
      break;
    case STATE_LAUNCH_CONTROL_ON_ACTIVE:
      printf("Launch control is active!\n");
      break;
    case STATE_LAUNCH_CONTROL_ON_INACTIVE:
      printf("Launch control is inactive.\n");
      break;
    default:
      printf("Unknown launch control state!\n");
      break;
  }
```

The full list of feature flags and particular feature statuses can be found in
`link_generic_dash.h`.


#### int getGenericDashParameterName(GenericDashParameters param, char* dashParameterInfo);
#### int getGenericDashParameterUom(GenericDashParameters param, char* dashParameterUom);

_Only available if `NO_DASH_VALUE_STRINGS` is not defined_

These retrieve the specified parameters human-friendly name, sets it into the
specified char* array and returns the number of bytes written. This is a rather
old way to do things (yes, String exists etc) but _widescale compatibility_ is
the name of the game.

You'll need to initialise a char* array of `maxGenericDashParameterNameLength`
or `maxGenericDashParameterUomLength` length before using either function.

The below example demonstrates the usage of both of these functions:

```c
  char parameterName[maxGenericDashParameterNameLength];
  char unitOfMeasurements[maxGenericDashParameterUomLength];

  signed int parameter_value = getGenericDashValue(ECU_MGP_KPA);

  int parameter_name_length = getGenericDashParameterName(ECU_MGP_KPA, parameterName);
  int parameter_uom_length = getGenericDashParameterUom(ECU_MGP_KPA, unitOfMeasurements);

  if (parameter_name_length != 0 && parameter_uom_length != 0) {
    printf("%s is currently %i %s\n", parameterName, parameter_value, unitOfMeasurements);
    // Example output:
    // Manifold Gauge Pres. is currently 145 kPa
  } else {
    printf("Unable to get specified parameter information!\n");
  }
```

#### signed int getGenericDashParameterDecimalPlaces(GenericDashParameters param);
#### signed int getGenericDashParameterMinimumValue(GenericDashParameters param);
#### signed int getGenericDashParameterMaximumValue(GenericDashParameters param);

_Only available if `NO_DASH_VALUE_STRINGS` is not defined_

These retrieve the specified parameters numerical information ie. maximum value
or decimal places as a signed integer. Useful for when graphing for example.

Here is a more advanced example based off the previous one that neatly renders
a value with a decimal place:

```c
  char parameterName[maxGenericDashParameterNameLength];
  char unitOfMeasurements[maxGenericDashParameterUomLength];

  float parameter_value = getGenericDashValue(ECU_BATTERY_VOLTAGE); // 13.850000...
  signed int parameter_dp = getGenericDashParameterDecimalPlaces(ECU_BATTERY_VOLTAGE); // 2

  int parameter_name_length = getGenericDashParameterName(ECU_BATTERY_VOLTAGE, parameterName);
  int parameter_uom_length = getGenericDashParameterUom(ECU_BATTERY_VOLTAGE, unitOfMeasurements);

  // Format a string including the decimal places from the above
  char format_string[26];
  sprintf(format_string, "%%s is currently %%0.%if %%s\n", parameter_dp);
  // If parameter_dp == 2, sets format_string to "%s is currently %0.2f %s\n"

  if (parameter_name_length != 0 && parameter_uom_length != 0) {
    printf(format_string, parameterName, parameter_value, unitOfMeasurements);
    // Example output:
    // Battery Voltage is currently 13.85 V
  } else {
    printf("Unable to get specified parameter information!\n");
  }
```

The min and max functions just return the absolute minimum and absolute
maximum this value can be. These may be useful for setting up graphing.

#### int getGenericDashLimitFlagName(GenericDashLimitFlags param, char* dashLimitFlagInfo);

_Only available if `NO_DASH_VALUE_STRINGS` is not defined_

This operates much like the `getGenericDashParameterName` function above except
it returns the specified limit flag name. Here is a quick example of use:

```c
  char dashLimitFlagName[maxGenericDashParameterNameLength];
  int parameter_name_length;

  if (getGenericDashLimitFlag(LIMITS_FLAG_TRACTION_LIMIT)) {
      parameter_name_length = getGenericDashLimitFlagName(LIMITS_FLAG_TRACTION_LIMIT, dashLimitFlagName);
      printf("%s active!\n", dashLimitFlagName);
      // Output:
      // Traction Limit active!
  }
```

#### int getLinkECUFaultCode(LinkECUFaultCodes param, char* faultCodeInfo);

_Only available if `NO_FAULT_CODE_STRINGS` is not defined_

Another function that also behaves a lot like `getGenericDashParameterName` in
that it sets a variable, but this function you feed a fault code number and it
returns a human-friendly description of the fault code.

You'll need to initialise a char* array of `maxLinkECUFaultCodeStringLength`
length before using either function. Here is a basic example:

```c
  char faultCodeDescription[maxLinkECUFaultCodeStringLength];
  LinkECUFaultCodes fault_code = (LinkECUFaultCodes)getGenericDashValue(ECU_FAULT_CODE);

  if (fault_code != ECU_FAULT_NONE) {
    if (getLinkECUFaultCode(fault_code, faultCodeDescription) != 0) {
      printf("Fault code %i: %s\n", (int)fault_code, faultCodeDescription);
      // Output:
      // Fault code 15: An Volt 2 Signal Error
    } else {
      printf("There was a fault code but we could not decode it!\n");
    }
  }
```

## Changelog

- v1.0.0 - Initial commit 