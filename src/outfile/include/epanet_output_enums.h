/*
 *  epanet_output_enums.h - EPANET Output API enums
 *
 *  Created on: March 11, 2019
 *
 *      Author: Michael E. Tryby
 *              US EPA - ORD/NRMRL
 */

 /**
 @file epanet_output_enums.h
 @brief Epanet output API enum types
 */

#ifndef EPANET_OUTPUT_ENUMS_H_
#define EPANET_OUTPUT_ENUMS_H_

/**
@defgroup OutputEnums Enumerated Types
@ingroup OutputGroup
@{
*/

/**
Defines element types used by @ref ENR_getElementName to distinguish
which network element type is being queried.
*/
typedef enum {
    ENR_node        = 1,  //!< Nodes
    ENR_link        = 2   //!< Links
} ENR_ElementType;

/**
Defines the unit type -- flow, pressure, or quality -- used by
@ref ENR_getUnits to distinguish which unit type is being queried.
*/
typedef enum {
    ENR_flowUnits   = 1,  //!< Flow units
    ENR_pressUnits  = 2,  //!< Pressure units
    ENR_qualUnits   = 3   //!< Quality units
} ENR_Units;

/**
Defines flow unit types.
*/
typedef enum {
    ENR_CFS         = 0,  //!< Cubic feet per second
    ENR_GPM         = 1,  //!< Gallons per minute
    ENR_MGD         = 2,  //!< Million gallons per day
    ENR_IMGD        = 3,  //!< Imperial million gallons per day
    ENR_AFD         = 4,  //!< Acre-feet per day
    ENR_LPS         = 5,  //!< Liters per second
    ENR_LPM         = 6,  //!< Liters per minute
    ENR_MLD         = 7,  //!< Million liters per day
    ENR_CMH         = 8,  //!< Cubic meters per hour
    ENR_CMD         = 9   //!< Cubic meters per day
} ENR_FlowUnits;

/**
Defines pressure unit types.
*/
typedef enum {
	ENR_PSI         = 0,  //!< Pounds per square inch psi
	ENR_MTR         = 1,  //!< Meters m
	ENR_KPA         = 2   //!< Kilo Pascal kPa
} ENR_PressUnits;

/**
Defines quality unit types.
*/
typedef enum {
    ENR_NONE        = 0,  //!< None
    ENR_MGL         = 1,  //!< Milli gram per liter mg/L
    ENR_UGL         = 2,  //!< Micro gram per liter ug/L
    ENR_HOURS       = 3,  //!< Hours hrs
    ENR_PRCNT       = 4   //!< Percent %
} ENR_QualUnits;

/**
Defines report and time types used by @ref ENR_getTimes to distinguish the
desired parameter of the query.
*/
typedef enum {
    ENR_reportStart = 1,  //!< Report start
    ENR_reportStep  = 2,  //!< Report step
    ENR_simDuration = 3,  //!< Simulation duration
    ENR_numPeriods  = 4   //!< Number of time periods
}ENR_Time;

/**
Defines node attribute types used by @ref ENR_getNodeResult,
@ref ENR_getNodeSeries, and @ref ENR_getNodeAttribute to distinguish the
desired parameter of the query.
*/
typedef enum {
    ENR_demand      = 1,  //!< Nodal demand
    ENR_head        = 2,  //!< Nodal hydraulic head
    ENR_pressure    = 3,  //!< Nodal pressure
    ENR_quality     = 4   //!< Nodel quality
} ENR_NodeAttribute;

/**
Defines link attribute types used by @ref ENR_getLinkResult,
@ref ENR_getLinkSeries, and @ref ENR_getLinkAttribute to distinguish the
desired parameter of the query.
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

/**
@}
*/

#endif /* EPANET_OUTPUT_ENUMS_H_ */
