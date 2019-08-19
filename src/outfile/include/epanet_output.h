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
@param[out] p_handle_out an EPANET output handle that gets passed into
all other Output API functions.
@return an error code -- 0 on success and -1 on failure

*/
int EXPORT_OUT_API ENR_init(ENR_Handle* p_handle_out);


/**
@brief Opens the output binary file and reads prologue and epilogue.
@param p_handle_out an EPANET output handle
@param path the name of the binary output file to be opened.
@return an error code
*/
int EXPORT_OUT_API ENR_open(ENR_Handle p_handle_in, const char* path);


/**
@brief Get the EPANET version that produced the output file.
@param[out] int_out the EPANET version number found in the output file prologue.
@return an error code

*/
int EXPORT_OUT_API ENR_getVersion(ENR_Handle p_handle_in, int* int_out);


/**
@brief Get an array of element count values.
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
int EXPORT_OUT_API ENR_getNetSize(ENR_Handle p_handle_in, int** int_out, int* int_dim);


/**
@brief Get unit flag for pressure, flow, and quality.
@param t_enum a unit type code (see @ref ENR_Units)
@param[out] int_out the flag value for the unit type (see @ref ENR_FlowUnits,
@ref ENR_PressUnits, @ref ENR_QualUnits)
@return an error code

*/
int EXPORT_OUT_API ENR_getUnits(ENR_Handle p_handle_in, ENR_Units t_enum, int* int_out);


/**
@brief Get report and simulation time related parameters.
@param t_enum a time parameter code (see @ref ENR_Time).
@param[out] int_out the value of the time parameter.
@return an error code

*/
int EXPORT_OUT_API ENR_getTimes(ENR_Handle p_handle_in, ENR_Time t_enum, int* int_out);


/**
@brief Retrieves name of a specified node or link element.
@param t_enum
@param elementIndex
@param[out] string_out
@param[out] slen
@return an error code

*/
int EXPORT_OUT_API ENR_getElementName(ENR_Handle p_handle_in, ENR_ElementType t_enum,
        int elementIndex, char** string_out, int* slen);


/**
@brief Returns pump energy usage statistics.
@param
@return

*/
int EXPORT_OUT_API ENR_getEnergyUsage(ENR_Handle p_handle_in, int pumpIndex,
        int* int_out, float** float_out, int* int_dim);


/**
@brief Returns network average reaction rates and average source mass inflow.
@param
@return

*/
int EXPORT_OUT_API ENR_getNetReacts(ENR_Handle p_handle_in, float** float_out, int* int_dim);


/**
@brief Get time series results for particular node attribute.
@param
@return

*/
int EXPORT_OUT_API ENR_getNodeSeries(ENR_Handle p_handle_in, int nodeIndex, ENR_NodeAttribute t_enum,
        int startPeriod, int endPeriod, float** outValueSeries, int* dim);


/**
@brief Get time series results for particular link attribute.
@param
@return

*/
int EXPORT_OUT_API ENR_getLinkSeries(ENR_Handle p_handle_in, int linkIndex, ENR_LinkAttribute t_enum,
        int startPeriod, int endPeriod, float** outValueSeries, int* dim);


/**
@brief Get a particular attribute for all nodes at given time.
@param
@return

*/
int EXPORT_OUT_API ENR_getNodeAttribute(ENR_Handle p_handle_in, int periodIndex,
        ENR_NodeAttribute t_enum, float** outValueArray, int* dim);


/**
@brief Get a particular attribute for all links at given time.
@param
@return

*/
int EXPORT_OUT_API ENR_getLinkAttribute(ENR_Handle p_handle_in, int periodIndex,
        ENR_LinkAttribute t_enum, float** outValueArray, int* dim);


/**
@brief Get all attributes for a node at given time.
@param
@return

*/
int EXPORT_OUT_API ENR_getNodeResult(ENR_Handle p_handle_in, int periodIndex, int nodeIndex,
        float** float_out, int* int_dim);


/**
@brief Get all attributes for a link at given time.
@param
@return

*/
int EXPORT_OUT_API ENR_getLinkResult(ENR_Handle p_handle_in, int periodIndex, int linkIndex,
        float** float_out, int* int_dim);


/**
@brief Close the output file and destroy the handle.
@param
@return

*/
int EXPORT_OUT_API ENR_close(ENR_Handle* p_handle_out);


/**
@brief Free memory allocated by API call.
@param
@return

*/
void EXPORT_OUT_API ENR_free(void** array);


/**
@brief Clears the current error status.
@param
@return

*/
void EXPORT_OUT_API ENR_clearError(ENR_Handle p_handle_in);


/**
@brief Checks the current error status.
@param
@return

*/
int EXPORT_OUT_API ENR_checkError(ENR_Handle p_handle_in, char** msg_buffer);


#ifdef __cplusplus
}
#endif

#endif /* EPANET_OUTPUT_H_ */
