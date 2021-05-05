#pragma once

#include <array>

class Error {
   public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        kLastOfCode,
    };

    Error(Code code) : code{code} {}

    operator bool() const { return this->code != kSuccess; }

    const char* Name() const {
        return code_names[static_cast<int>(this->code)];
    }

   private:
    static constexpr std::array<const char*, 3> code_names = {
        "kSuccess", "kFull", "kEmpty"};
    Code code;
};
