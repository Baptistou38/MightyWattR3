/**
 * VoltageSetter.cpp
 *
 * 2016-10-29
 * kaktus circuits
 * GNU GPL v.3
 */


/* <Includes> */ 

#include "Arduino.h"
#include "Control.h"
#include "DACC.h"
#include "Voltmeter.h"
#include "VoltageSetter.h"
#include "RangeSwitcher.h"

/* </Includes> */ 


/* <Module variables> */ 

//static uint16_t dacTargetValue;
static ErrorMessaging_Error VoltageSetterError;
static uint32_t presentVoltage;

/* </Module variables> */ 


/* <Implementations> */ 

void VoltageSetter_Init(void)
{
  VoltageSetterError.errorCounter = 0;
  VoltageSetterError.error = ErrorMessaging_VoltageSetter_SetVoltageOverload;
}

void VoltageSetter_Do(void)
{
  uint32_t dac;    
  RangeSwitcher_VoltageRanges previousRange = RangeSwitcher_GetVoltageRange();
  RangeSwitcher_VoltageRanges range;
  Control_CCCVStates previousCCCVState = Control_GetCCCV();  
  
  /* Calculate range */
  if ((presentVoltage > VOLTAGESETTER_HYSTERESIS_UP) || (RangeSwitcher_CanAutorangeVoltage() == false))
  {
    range = VoltageRange_HighVoltage;
  }
  else if (presentVoltage < VOLTAGESETTER_HYSTERESIS_DOWN)
  {
    range = VoltageRange_LowVoltage;
  }
  else
  {
    range = previousRange;
  }
      
  switch (range)
  {
    case VoltageRange_HighVoltage:
      if ((int32_t)presentVoltage + VOLTSETTER_OFFSET_HI > 0)
      {
        dac = ((((uint64_t)((int32_t)presentVoltage + VOLTSETTER_OFFSET_HI))) << 16) / VOLTSETTER_SLOPE_HI;
        if (dac > DAC_MAXIMUM) /* Set voltage higher than maximum */
        {
          VoltageSetterError.errorCounter++;
          VoltageSetterError.error = ErrorMessaging_VoltageSetter_SetVoltageOverload;
          dac = DAC_MAXIMUM;
        }
      }
    break;
    case VoltageRange_LowVoltage:
      if ((int32_t)presentVoltage + VOLTSETTER_OFFSET_LO > 0)
      {
          dac = ((((uint64_t)((int32_t)presentVoltage + VOLTSETTER_OFFSET_LO))) << 16) / VOLTSETTER_SLOPE_LO;
          if (dac > DAC_MAXIMUM) /* Set voltage higher than maximum */
          {
            dac = DAC_MAXIMUM;
          }
      }
    break;
    default:      
    return;
  }

  /* Set range if high voltage */
  if (range == VoltageRange_HighVoltage)
  {
    RangeSwitcher_SetVoltageRange(range);
  }
  /* Set calculated DAC value */
  if (!DACC_SetVoltage(dac & 0xFFFF))
  {
    VoltageSetterError.errorCounter++;
    VoltageSetterError.error = ErrorMessaging_VoltageSetter_SetVoltageOverload; 
  }  
  /* Set range if low voltage */
  if (range == VoltageRange_LowVoltage)
  {
    RangeSwitcher_SetVoltageRange(range);
  }
  /* Set phase CV */
  Control_SetCCCV(Control_CCCV_CV);

  /* If range or mode has changed, invalidate the next measurement because the measurement may occur during the change */
  if ((previousRange != range) || (previousCCCVState != Control_CCCV_CV))
  {
    Measurement_Invalidate();
  }
}

void VoltageSetter_SetVoltage(uint32_t voltage)
{
  presentVoltage = voltage;
}

uint32_t VoltageSetter_GetVoltage(void)
{
  return presentVoltage;
}

void VoltageSetter_Plus(uint32_t value)
{
  if ((presentVoltage + value) < presentVoltage || (presentVoltage + value) < value) // overflow check
  {  
    VoltageSetter_SetVoltage(VOLTAGE_SETTER_MAXIMUM_HIVOLTAGE - 1);
  }
  else if (value + presentVoltage < VOLTAGE_SETTER_MAXIMUM_HIVOLTAGE)
  {
    VoltageSetter_SetVoltage(value + presentVoltage);
  }
  else
  {
    VoltageSetter_SetVoltage(VOLTAGE_SETTER_MAXIMUM_HIVOLTAGE - 1);
  }
}

void VoltageSetter_Minus(uint32_t value)
{
  if (value > presentVoltage) // overflow check
  {  
    VoltageSetter_SetVoltage(0);
  }
  else
  {
    VoltageSetter_SetVoltage(presentVoltage - value); 
  }
}

const ErrorMessaging_Error * VoltageSetter_GetError(void)
{
  return &VoltageSetterError;
}

/* </Implementations> */ 
