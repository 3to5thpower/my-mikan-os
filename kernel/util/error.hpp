#pragma once

#include <array>

class Error {
   public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        kNoEnoughMemory,
        kIndexOutOfRange,
        kHostControllerNotHalted,
        kInvalidSlotID,
        kPortNotConnected,
        kInvalidEndpointNumber,
        kTransferRingNotSet,
        kAlreadyAllocated,
        kNotImplemented,
        kInvalidDescriptor,
        kBufferTooSmall,
        kUnknownDevice,
        kNoCorrespondingSetupStage,
        kTransferFailed,
        kInvalidPhase,
        kUnknownXHCISpeedID,
        kNoWaiter,
        kLastOfCode,
    };

    Error(Code code, const char* file, int line)
        : code{code}, line{line}, file{file} {}

    Code Cause() const { return code; }

    operator bool() const { return this->code != kSuccess; }

    const char* Name() const {
        return code_names[static_cast<int>(this->code)];
    }

    const char* File() const { return file; }
    int Line() const { return line; }

   private:
    static constexpr std::array<char*, 20> code_names = {
        "kSuccess",
        "kFull",
        "kEmpty",
        "kNoEnoughMemory",
        "kIndexOutOfRange",
        "kHostControllerNotHalted",
        "kInvalidSlotID",
        "kPortNotConnected",
        "kInvalidEndpointNumber",
        "kTransferRingNotSet",
        "kAlreadyAllocated",
        "kNotImplemented",
        "kInvalidDescriptor",
        "kBufferTooSmall",
        "kUnknownDevice",
        "kNoCorrespondingSetupStage",
        "kTransferFailed",
        "kInvalidPhase",
        "kUnknownXHCISpeedID",
        "kNoWaiter",
    };
    static_assert(Error::Code::kLastOfCode == code_names.size());

    Code code;
    int line;
    const char* file;
};

#define MAKE_ERROR(code) Error((code), __FILE__, __LINE__)

template <typename T>
struct WithError {
    T value;
    Error error;
};
