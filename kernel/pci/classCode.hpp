#include <cstdint>

struct ClassCode {
    uint8_t base, sub, interface;
    /** @brief ベースクラスが等しい場合真*/
    bool Match(uint8_t b) { return this->base == b; }
    /** @brief ベースクラスとサブクラスが等しい場合に真を返す */
    bool Match(uint8_t b, uint8_t s) { return Match(b) && s == sub; }
    /** @brief ベース，サブ，インターフェースが等しい場合に真を返す */
    bool Match(uint8_t b, uint8_t s, uint8_t i) {
        return Match(b, s) && i == interface;
    }
};
