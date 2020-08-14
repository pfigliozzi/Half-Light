#pragma once

#include "CorsairLayersGlobal.h"
#include "Shared/LFX.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/** Defines type for Guid returned by function CorsairLayersPlayEffect(). */
	typedef struct LayerEffectGuidTag *LayerGuid;

	/** Defines type for pointer to CUESDK function for setting colors. */
	typedef bool(*CorsairSetLedsColorsBufferByDeviceIndexType)(int , int , CorsairLedColor* );

	/** Defines type for pointer to CUESDK function for flushing buffer. */
	typedef bool (*CorsairSetLedsColorsFlushBufferAsyncType)(void (*)(void *, bool, CorsairError), void *);

	/**
	 * @brief Initializes the library with pointer to CUESDK function.
	 *       
	 * @warning This function has to be called before any of CorsairLayersPlayEffect() calls.
	 *
	 * @param setColorsByDeviceIndexFunc pointer to function that can fill drawing buffer for devices.
	 *                                   This should be CorsairSetLedsColorsBufferByDeviceIndex function from CUESDK
	 * @param flushBufferAsyncFunc pointer to async function that can perform drawing on devices by flushing drawing buffer.
	 *                             This should be CorsairSetLedsColorsFlushBufferAsync function from CUESDK
	 */
	CORSAIRLAYERS_EXPORT void CorsairLayersInitialize(CorsairSetLedsColorsBufferByDeviceIndexType setColorsByDeviceIndexFunc, CorsairSetLedsColorsFlushBufferAsyncType flushBufferAsyncFunc);

	/**
	 * @brief Plays effect specified by CorsairEffect parameter.
	 * @param effect Pointer to CorsairEffect structure 
	 * @param layer  The layer for effect to play on
	 * @return Guid that represents runtime effect identifier and can be later
	 * used in CorsairLayersStopEffect() function to stop the effect playback.
	 */
	CORSAIRLAYERS_EXPORT LayerGuid CorsairLayersPlayEffect(CorsairEffect* effect, int layer);

	/**
	 * @brief Stops effect playback.
	 * @param layerId Runtime effect identifier returned by CorsairLayersPlayEffect()
	 */
	CORSAIRLAYERS_EXPORT void CorsairLayersStopEffect(LayerGuid layerId);

#ifdef __cplusplus
} //exten "C"
#endif
