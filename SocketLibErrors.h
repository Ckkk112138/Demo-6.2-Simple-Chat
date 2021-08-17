#ifndef SOCKETLIBERRORS_H
#define SOCKETLIBERRORS_H

#include "SocketLibTypes.h"
#include <exception>
#include <string>


namespace SocketLib
{
	enum Error
	{
        // errors that shouldn't happen, so if they do, something is wrong:
        ESeriousError,

        // these errors are common
        ENetworkDown,
        ENoSocketsAvailable,
        ENoMemory,
        EAddressNotAvailable,
        EAlreadyConnected,
        ENotConnected,
        EConnectionRefused,
        ENetworkUnreachable,
        ENetworkReset,
        EHostUnreachable,
        EHostDown,
        EConnectionAborted,
        EConnectionReset,
        EOperationWouldBlock,

        // DNS errors
        EDNSNotFound,
        EDNSError,
        ENoDNSData,

        // These errors are specific errors that should never or rarely occur.
        EInProgress,
        EInterrupted,
        EAccessDenied,
        EInvalidParameter,
        EAddressFamilyNotSupported,
        EProtocolFamilyNotSupported,
        EProtocolNotSupported,
        EProtocolNotSupportedBySocket,
        EOperationNotSupported,
        EInvalidSocketType,
        EInvalidSocket,
        EAddressRequired,
        EMessageTooLong,
        EBadProtocolOption,
        EAddressInUse,
        ETimedOut,
        EShutDown,


        // auxilliary socketlib errors
        ESocketLimitReached,
        ENotAvailable,
        EConnectionClosed
	};

    Error TranslateError(int p_error, bool p_errno);
    Error GetError(bool p_errno = true);

    class Exception : public std::exception
    {
    public:
        Exception(Error p_code);
        Error ErrorCode();
        std::string PrintError();
    protected:
        Error m_code;
    };
}
#endif // !SOCKETLIBERRORS_H

