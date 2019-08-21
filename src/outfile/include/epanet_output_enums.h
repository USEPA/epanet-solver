/*
 *  epanet_output_enums.h - EPANET Output API enums
 *
 *  Created on: March 11, 2019
 *
 *      Author: Michael E. Tryby
 *              US EPA - ORD/NRMRL
 */


#ifndef EPANET_OUTPUT_ENUMS_H_
#define EPANET_OUTPUT_ENUMS_H_

/**
 Network element types
*/
typedef enum {
    ENR_node        = 1,  //!< Nodes
    ENR_link        = 2   //!< Links
} ENR_ElementType;

/**
Unit types
*/
typedef enum {
    ENR_flowUnits   = 1,  //!< Flow units
    ENR_pressUnits  = 2,  //!< Pressure units
    ENR_qualUnits   = 3   //!< Quality units
} ENR_Units;

/**
Flow unit types
*/
typedef enum {
  EN_CFS            = 0,  //!< Cubic feet per second
  EN_GPM            = 1,  //!< Gallons per minute
  EN_MGD            = 2,  //!< Million gallons per day
  EN_IMGD           = 3,  //!< Imperial million gallons per day
  EN_AFD            = 4,  //!< Acre-feet per day
  EN_LPS            = 5,  //!< Liters per second
  EN_LPM            = 6,  //!< Liters per minute
  EN_MLD            = 7,  //!< Million liters per day
  EN_CMH            = 8,  //!< Cubic meters per hour
  EN_CMD            = 9   //!< Cubic meters per day
} EN_FlowUnits;

/**
Pressure unit types
*/
typedef enum {
	ENR_PSI         = 0,  //!< Pounds per square inch psi
	ENR_MTR         = 1,  //!< Meters m
	ENR_KPA         = 2   //!< Kilo Pascal kPa
} ENR_PressUnits;

/**
Quality unit types
*/
typedef enum {
    ENR_NONE        = 0,  //!< None
    ENR_MGL         = 1,  //!< Milli gram per liter mg/L
    ENR_UGL         = 2,  //!< Micro gram per liter ug/L
    ENR_HOURS       = 3,  //!< Hours hrs
    ENR_PRCNT       = 4   //!< Percent %
} ENR_QualUnits;

/**
Report and time types
*/
typedef enum {
    ENR_reportStart = 1,  //!< Report start
    ENR_reportStep  = 2,  //!< Report step
    ENR_simDuration = 3,  //!< Simulation duration
    ENR_numPeriods  = 4   //!< Number of time periods
}ENR_Time;

/**
Node attribute types
*/
typedef enum {
    ENR_demand      = 1,  //!< Nodal demand
    ENR_head        = 2,  //!< Nodal hydraulic head
    ENR_pressure    = 3,  //!< Nodal pressure
    ENR_quality     = 4   //!< Nodel quality
} ENR_NodeAttribute;

/**
Link attribute types
*/
typedef enum {
    ENR_flow        = 1,  //!< Link flow rate
    ENR_velocity    = 2,  //!< Link velocity
    ENR_headloss    = 3,  //!< Link head loss
    ENR_avgQuality  = 4,  //!< Link average quality
    ENR_status      = 5,  //!< Link status
    ENR_setting     = 6,  //!< Link setting
    ENR_rxRate      = 7,  //!< Link reaction rate
    ENR_frctnFctr   = 8   //!< Link friction factor
} ENR_LinkAttribute;


#endif /* EPANET_OUTPUT_ENUMS_H_ */
