/*
 *  epanet_output.h - EPANET Output API
 *
 *  Created on: Jun 4, 2014
 *
 *      Author: Michael E. Tryby
 *              US EPA - ORD/NRMRL
 */

#ifndef EPANET_OUTPUT_H_
#define EPANET_OUTPUT_H_
/* Epanet output binary file API */


#define MAXFNAME     259   // Max characters in file name
#define MAXID         31   // Max characters in ID name


/**
@brief EPANET Output file handle
*/
typedef void* ENR_Handle;


#include "epanet_output_enums.h"
#include "epanet_output_export.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
@brief Initializes pointer to output handle.
@param[out] p_handle an EPANET output handle that gets passed into
all other Output API functions.
@return an error code -- 0 on success or -1 on failure

*/
int EXPORT_OUT_API ENR_init(ENR_Handle* p_handle);


/**
@brief Opens the output binary file and reads prologue and epilogue.
@param p_handle an EPANET output handle
@param path the name of the binary output file to be opened.
@return an error code
*/
int EXPORT_OUT_API ENR_open(ENR_Handle p_handle, const char* path);


/**
@brief Get the EPANET version that produced the output file.
@param p_handle an EPANET output handle
@param[out] int_out the EPANET version number found in the output file prologue.
@return an error code
*/
int EXPORT_OUT_API ENR_getVersion(ENR_Handle p_handle, int* int_out);


/**
@brief Get an array of element count values.
@param p_handle an EPANET output handle
@param[out] int_out array of element count values
@param[out] int_dim array size
@return an error code

Element count array contents:
  0. nodes
  1. tanks
  2. links
  3. pumps
  4. values

This function allocates memory for the element count array. The caller is
responsible for freeing it using ::ENR_free.
*/
int EXPORT_OUT_API ENR_getNetSize(ENR_Handle p_handle, int** int_out, int* int_dim);


/**
@brief Get unit flag for pressure, flow, and quality.
@param p_handle an EPANET output handle
@param t_enum a unit type code (see @ref ENR_Units)
@param[out] int_out the flag value for the unit type (see @ref ENR_FlowUnits,
@ref ENR_PressUnits, @ref ENR_QualUnits)
@return an error code
*/
int EXPORT_OUT_API ENR_getUnits(ENR_Handle p_handle, ENR_Units t_enum, int* int_out);


/**
@brief Get report and simulation time related parameters.
@param p_handle an EPANET output handle
@param t_enum a time parameter code (see @ref ENR_Time).
@param[out] int_out the value of the time parameter.
@return an error code
*/
int EXPORT_OUT_API ENR_getTimes(ENR_Handle p_handle, ENR_Time t_enum, int* int_out);


/**
@brief Retrieves name of a specified node or link element.
@param p_handle an EPANET output handle
@param t_enum
@param elementIndex
@param[out] string_out
@param[out] slen
@return an error code
*/
int EXPORT_OUT_API ENR_getElementName(ENR_Handle p_handle, ENR_ElementType t_enum,
    int elementIndex, char** string_out, int* slen);


/**
@brief Returns pump energy usage statistics.
@param p_handle an EPANET output handle
@param pumpIndex
@param int_out
@param float_out
@param int_dim
@return an error code
*/
int EXPORT_OUT_API ENR_getEnergyUsage(ENR_Handle p_handle, int pumpIndex,
    int* int_out, float** float_out, int* int_dim);


/**
@brief Returns network average reaction rates and average source mass inflow.
@param p_handle an EPANET output handle
@param float_out
@param int_dim
@return an error code
*/
int EXPORT_OUT_API ENR_getNetReacts(ENR_Handle p_handle, float** float_out, int* int_dim);


/**
@brief Get time series results for particular node attribute.
@param p_handle an EPANET output handle
@param nodeIndex the node index for time series
@param attr code for the node attribute to report (see @ref ENR_NodeAttribute)
@param startPeriod time period of series start
@param endPeriod time period of series end
@param outValueSeries array of time series values
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getNodeSeries(ENR_Handle p_handle, int nodeIndex, ENR_NodeAttribute attr,
    int startPeriod, int endPeriod, float** outValueSeries, int* length);


/**
@brief Get time series results for particular link attribute.
@param p_handle an EPANET output handle
@param linkIndex the link index for time series
@param attr code for the link attribute to report (see @ref ENR_LinkAttribute)
@param startPeriod time period of series start
@param endPeriod time period of series end
@param outValueSeries array of time series values
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getLinkSeries(ENR_Handle p_handle, int linkIndex, ENR_LinkAttribute attr,
    int startPeriod, int endPeriod, float** outValueSeries, int* length);


/**
@brief Get a particular attribute for all nodes at given time.
@param p_handle an EPANET output handle
@param periodIndex the time period index for reporting results
@param attr code for the node attribute to report (see @ref ENR_NodeAttribute)
@param outValueArray the array of node attributes
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getNodeAttribute(ENR_Handle p_handle, int periodIndex,
    ENR_NodeAttribute attr, float** outValueArray, int* dim);


/**
@brief Get a particular attribute for all links at given time.
@param p_handle an EPANET output handle
@param periodIndex the time period index for reporting results
@param attr code for the link attribute to report (see @ref ENR_LinkAttribute)
@param outValueArray the array of link attributes
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getLinkAttribute(ENR_Handle p_handle, int periodIndex,
    ENR_LinkAttribute attr, float** outValueArray, int* length);


/**
@brief Get all attributes for a node at given time.
@param p_handle an EPANET output handle
@param periodIndex the time period index for reporting results
@param nodeIndex the node index for reporting results
@param outValueArray the array of node attributes
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getNodeResult(ENR_Handle p_handle, int periodIndex,
    int nodeIndex, float** outValueArray, int* length);


/**
@brief Get all attributes for a link at given time.
@param p_handle an EPANET output handle
@param periodIndex the time period index for reporting results
@param linkIndex the link index for reporting results
@param outValueArray the array of link attributes
@param length the number of elements in the outValueArray
@return an error code
*/
int EXPORT_OUT_API ENR_getLinkResult(ENR_Handle p_handle, int periodIndex,
    int linkIndex, float** outValueArray, int* length);


/**
@brief Close the output file and destroy the handle.
@param p_handle an EPANET output handle
@return an error code -- 0 on success or -1 on failure
*/
int EXPORT_OUT_API ENR_close(ENR_Handle* p_handle);


/**
@brief Free memory allocated by API call.
@param array the memory to be freed.
@return an error code
*/
void EXPORT_OUT_API ENR_free(void** array);


/**
@brief Clears the current error status.
@param p_handle an EPANET output handle
*/
void EXPORT_OUT_API ENR_clearError(ENR_Handle p_handle);


/**
@brief Checks the current error status.
@param p_handle an EPANET output handle
@param[out] msg_buffer contains the message associated with the current error code.
@return the current error code
*/
int EXPORT_OUT_API ENR_checkError(ENR_Handle p_handle, char** msg_buffer);


#ifdef __cplusplus
}
#endif

#endif /* EPANET_OUTPUT_H_ */
