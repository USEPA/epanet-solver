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
@param
@return

*/
int EXPORT_OUT_API ENR_init(ENR_Handle* p_handle_out);

/**
@brief Opens the output binary file and reads prologue and epilogue.
@param
@return

*/
int EXPORT_OUT_API ENR_open(ENR_Handle p_handle_in, const char* path);

/**
@brief Returns EPANET version that produced the output file.
@param
@return

*/
int EXPORT_OUT_API ENR_getVersion(ENR_Handle p_handle_in, int* int_out);

/**
@brief Returns an array of element count values.
@param
@return

*/
int EXPORT_OUT_API ENR_getNetSize(ENR_Handle p_handle_in, int** int_out, int* int_dim);

/**
@brief Returns unit flag for pressure, flow, and quality.
@param
@return

*/
int EXPORT_OUT_API ENR_getUnits(ENR_Handle p_handle_in, ENR_Units t_enum, int* int_out);

/**
@brief Returns report and simulation time related parameters.
@param
@return

*/
int EXPORT_OUT_API ENR_getTimes(ENR_Handle p_handle_in, ENR_Time t_enum, int* int_out);

/**
@brief Retrieves name of a specified node or link element.
@param
@return

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
