/*  Copyright 2021-2022 MarcosHCK
 *  This file is part of dotdashair.
 *
 *  dotdashair is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dotdashair is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dotdashair.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __PA_ERROR__
#define __PA_ERROR__
#include <portaudio.h>
#include <glib.h>

/**
 * PA_ERROR:
 *
 * Error domain for Portaudio backend. Errors in this domain will be from the #PaGError enumeration.
 * See #GError for more information on error domains.
 */
#define PA_ERROR (pa_error_quark ())

/**
 * PaGError:
 * @PA_ERROR_FAILED: generic error condition.
 *
 * Error code returned by Portaudio backend.
 * Note that %PA_ERROR_FAILED is here only for compatibility with
 * error domain definition paradigm as defined on GLib documentation.
 */
typedef enum
{
  PA_ERROR_FAILED = 0,
  PA_ERROR_NO_ERROR = paNoError,                                                                  /*<nick=paNoError>*/
  PA_ERROR_NOT_INITIALIZED = paNotInitialized,                                                    /*<nick=paNotInitialized>*/
  PA_ERROR_UNANTICIPATED_HOST_ERROR = paUnanticipatedHostError,                                   /*<nick=paUnanticipatedHostError>*/
  PA_ERROR_INVALID_CHANNEL_COUNT = paInvalidChannelCount,                                         /*<nick=paInvalidChannelCount>*/
  PA_ERROR_INVALID_SAMPLE_RATE = paInvalidSampleRate,                                             /*<nick=paInvalidSampleRate>*/
  PA_ERROR_INVALID_DEVICE = paInvalidDevice,                                                      /*<nick=paInvalidDevice>*/
  PA_ERROR_INVALID_FLAG = paInvalidFlag,                                                          /*<nick=paInvalidFlag>*/
  PA_ERROR_SAMPLE_FORMAT_NOT_SUPPORTED = paSampleFormatNotSupported,                              /*<nick=paSampleFormatNotSupported>*/
  PA_ERROR_BAD_IO_DEVICE_COMBINATION = paBadIODeviceCombination,                                  /*<nick=paBadIODeviceCombination>*/
  PA_ERROR_INSUFFICIENT_MEMORY = paInsufficientMemory,                                            /*<nick=paInsufficientMemory>*/
  PA_ERROR_BUFFER_TOO_BIG = paBufferTooBig,                                                       /*<nick=paBufferTooBig>*/
  PA_ERROR_BUFFER_TOO_SMALL = paBufferTooSmall,                                                   /*<nick=paBufferTooSmall>*/
  PA_ERROR_NULL_CALLBACK = paNullCallback,                                                        /*<nick=paNullCallback>*/
  PA_ERROR_BAD_STREAM_PTR = paBadStreamPtr,                                                       /*<nick=paBadStreamPtr>*/
  PA_ERROR_TIMEOUT = paTimedOut,                                                                  /*<nick=paTimedOut>*/
  PA_ERROR_INTERNAL_ERROR = paInternalError,                                                      /*<nick=paInternalError>*/
  PA_ERROR_DEVICE_UNAVAILABLE = paDeviceUnavailable,                                              /*<nick=paDeviceUnavailable>*/
  PA_ERROR_INCOMPATIBLE_HOST_API_SPECIFIC_STREAM_INFO = paIncompatibleHostApiSpecificStreamInfo,  /*<nick=paIncompatibleHostApiSpecificStreamInfo>*/
  PA_ERROR_STREAM_IS_STOPPED = paStreamIsStopped,                                                 /*<nick=paStreamIsStopped>*/
  PA_ERROR_STREAM_IS_NOT_STOPPED = paStreamIsNotStopped,                                          /*<nick=paStreamIsNotStopped>*/
  PA_ERROR_INPUT_OVERFLOWED = paInputOverflowed,                                                  /*<nick=paInputOverflowed>*/
  PA_ERROR_OUTPUT_UNDERFLOWED = paOutputUnderflowed,                                              /*<nick=paOutputUnderflowed>*/
  PA_ERROR_HOST_API_NOT_FOUND = paHostApiNotFound,                                                /*<nick=paHostApiNotFound>*/
  PA_ERROR_INVALID_HOST_API = paInvalidHostApi,                                                   /*<nick=paInvalidHostApi>*/
  PA_ERROR_CAN_NOT_READ_FROM_CALLBACK_STREAM = paCanNotReadFromACallbackStream,                   /*<nick=paCanNotReadFromACallbackStream>*/
  PA_ERROR_CAN_NOT_WRITE_TO_CALLBACK_STREAM = paCanNotWriteToACallbackStream,                     /*<nick=paCanNotWriteToACallbackStream>*/
  PA_ERROR_CAN_NOT_READ_FROM_OUTPUT_STREAM = paCanNotReadFromAnOutputOnlyStream,                  /*<nick=paCanNotReadFromAnOutputOnlyStream>*/
  PA_ERROR_CAN_NOT_WRITE_TO_INPUT_STREAM = paCanNotWriteToAnInputOnlyStream,                      /*<nick=paCanNotWriteToAnInputOnlyStream>*/
  PA_ERROR_INCOMPATIBLE_STREAM_HOST_API = paIncompatibleStreamHostApi,                            /*<nick=paIncompatibleStreamHostApi>*/
  PA_ERROR_BAD_BUFFER_PTR = paBadBufferPtr,                                                       /*<nick=paBadBufferPtr>*/
} PaGError;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
pa_error_quark () G_GNUC_CONST;

void
pa_error_propagate(GError** error, PaError paer);

#if __cplusplus
}
#endif // __cplusplus

#endif // __PA_ERROR__
