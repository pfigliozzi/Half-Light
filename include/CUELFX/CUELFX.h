#pragma once

#include "CUELFXGlobal.h"
#include "Shared/LFX.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/// Contains list of effect speeds.
	enum CorsairLightingEffectSpeed 
	{
		CLES_Slow,
		CLES_Medium,
		CLES_Fast
	};

	/// Contains list of circular effect directions.
	enum CorsairLightingEffectCircularDirection 
	{
		CLECD_Clockwise,
		CLECD_CounterClockwise
	};

	/// Contains list of linear effect directions.
	enum CorsairLightingEffectLinearDirection
	{
		CLELD_Left,
		CLELD_Right,
		CLELD_Up,
		CLELD_Down,
	};

	/// Contains list of color modes.
	enum CorsairLightingEffectColorMode
	{
		CLECM_Random,
		CLECM_Alternating
	};

	/// Color options to be used in the effect.
	struct CorsairLightingEffectColorOptions 
	{
		enum CorsairLightingEffectColorMode mode;  /**< Enum describing color mode for the effect */
		struct CorsairColor color1;                /**< First color is only used if mode is set to CLECM_Alternating */
		struct CorsairColor color2;                /**< Second color is only used if mode is set to CLECM_Alternating */

	};

	/**
	 * @brief Gets the frame for specified effect id and offset.
	 *
	 * @warning Client of this function is responsible for freeing memory used by CorsairFrame structure
	 * and it's fields using CUELFXFreeFrame() function.
	 *
	 * @param effectId Unique identifier of the effect. Can be obtained from CorsairEffect struct.
	 * @param offset   Offset in milliseconds.
	 * @return Pointer to CorsairFrame structure or NULL if effect is finished at specified offset.
	 */
	CUELFX_EXPORT struct CorsairFrame *CUELFXGetFrame(Guid effectId, int offset);

	/**
	 * @brief Frees the memory allocated by CorsairFrame structure and its fields.
	 *       
	 * @attention The frame data cannot be accessed after call to this function.
	 *
	 * @param pFrame Pointer to the frame structure that has to be freed.
	 */
	CUELFX_EXPORT void CUELFXFreeFrame(struct CorsairFrame *pFrame);

	/**
	 * @brief Assigns effect to LEDs.
	 * @param effectId     Unique identifier of the effect
	 * @param deviceIndex  Zero-based index of device.
	 * @param size         Number of leds in ledPositions array.
	 * @param ledPositions Array of LEDs to be used in effect with their positions retrieved using CorsairGetLedPositions() or CorsairGetLedPositionsByDeviceIndex().
	 */
	CUELFX_EXPORT void CUELFXAssignEffectToLeds(Guid effectId, int deviceIndex, int size, const CorsairLedPosition *ledPositions);

	/**
	 * @brief Creates spiral rainbow effect.
	 * @param speed     Speed of the effect.
	 * @param direction Circular direction of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateSpiralRainbowEffect(enum CorsairLightingEffectSpeed speed, enum CorsairLightingEffectCircularDirection direction);

	/**
	 * @brief Creates rainbow wave effect.
	 * @param speed     Speed of the effect.
	 * @param direction Linear direction of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateRainbowWaveEffect(enum CorsairLightingEffectSpeed speed, enum CorsairLightingEffectLinearDirection direction);

	/**
	 * @brief Creates visor effect.
	 * @param speed        Speed of the effect.
	 * @param colorOptions Color option to be used in the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateVisorEffect(enum CorsairLightingEffectSpeed speed, struct CorsairLightingEffectColorOptions colorOptions);

	/**
	 * @brief Creates rain effect.
	 * @param speed        Speed of the effect.
	 * @param colorOptions Color option to be used in the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateRainEffect(enum CorsairLightingEffectSpeed speed, struct CorsairLightingEffectColorOptions colorOptions);

	/**
	 * @brief Creates color shift effect.
	 * @param speed        Speed of the effect.
	 * @param colorOptions Color option to be used in the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateColorShiftEffect(enum CorsairLightingEffectSpeed speed, struct CorsairLightingEffectColorOptions colorOptions);

	/**
	 * @brief Creates color pulse effect.
	 * @param speed        Speed of the effect.
	 * @param colorOptions Color option to be used in the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateColorPulseEffect(enum CorsairLightingEffectSpeed speed, struct CorsairLightingEffectColorOptions colorOptions);

	/**
	 * @brief Creates color wave effect.
	 * @param speed        Speed of the effect.
	 * @param direction    Linear direction of the effect.
	 * @param colorOptions Color option to be used in the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateColorWaveEffect(enum CorsairLightingEffectSpeed speed, enum CorsairLightingEffectLinearDirection direction, struct CorsairLightingEffectColorOptions colorOptions);

	/**
	 * @brief Creates ripple effect.
	 *
	 * @note In order to construct effect properly, intensity points has to be added using CUELFXAddPointToEffect().
	 * @param tail        Tail size (in LED units).
	 * @param velocity    Velocity (in LED/second).
	 * @param duration    Duration in milliseconds.
	 * @param repeatCount Number of times to repeat this effect. Specify 0 to run effect continuously.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateRippleEffect(double tail, double velocity, int duration, int repeatCount);

	/**
	 * @brief Creates wave effect.
	 *
	 * @note In order to construct effect properly, intensity points has to be added using CUELFXAddPointToEffect().
	 *
	 * @param tail         Tail size (in LED units).
	 * @param velocity     Velocity (in LED/second).
	 * @param duration     Duration in milliseconds.
	 * @param orientation  Orientation in degrees within a range [0..359].
	 * @param twoSides Specifies if the effect is one or two sided.
	 * @param repeatCount  Number of times to repeat this effect. Specify 0 to run effect continuously.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateWaveEffect(double tail, double velocity, int duration, int orientation, bool twoSides, int repeatCount);

	/**
	 * @brief Creates solid color effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateSolidColorEffect(struct CorsairColor color);

	/**
	 * @brief Creates rainbow pulse effect.
	 * @param speed Speed of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateRainbowPulseEffect(enum CorsairLightingEffectSpeed speed);

	/**
	 * @brief Creates single blink effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateSingleBlinkEffect(struct CorsairColor color);

	/**
	 * @brief Creates double blink effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateDoubleBlinkEffect(struct CorsairColor color);

	/**
	 * @brief Creates rapid blink effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateRapidBlinkEffect(struct CorsairColor color);

	/**
	 * @brief Creates alternating rapid blink effect.
	 * @param firstColor  First color of the effect.
	 * @param secondColor Second color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateAlternatingRapidBlinkEffect(struct CorsairColor firstColor, struct CorsairColor secondColor);

	/**
	 * @brief Creates heart beat effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateHeartbeatEffect(struct CorsairColor color);
	
	/**
	 * @brief Creates off beat effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateOffBeatEffect(struct CorsairColor color);
	
	/**
	 * @brief Creates breathe effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateBreatheEffect(struct CorsairColor color);

	/**
	 * @brief Creates slow breathe effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateSlowBreatheEffect(struct CorsairColor color);

	/**
	 * @brief Creates slow long breathe effect.
	 * @param color Color of the effect.
	 * @return Pointer to CorsairEffect structure.
	 */
	CUELFX_EXPORT struct CorsairEffect *CUELFXCreateSlowLongBreatheEffect(struct CorsairColor color);

	/**
	 * @brief Adds point to specified wave or ripple effect intensity chart.
	 * @param effectId Unique identifier of the effect. Can be obtained from CorsairEffect struct.
	 * @param position Position to insert the point within a range [0..1].
	 * @param color    The color of the point to insert.
	 */
	CUELFX_EXPORT void CUELFXAddPointToEffect(Guid effectId, double position, CorsairColor color);

#ifdef __cplusplus
} //exten "C"
#endif
