#include <array>
#include <cstdint>
#include <util/error.hpp>

namespace pci {

/** @brief CONFIG_ADDRESSレジスタのIOポートアドレス */
const uint16_t kConfigAddress = 0x0cf8;

/** @brief CONFIG_DATAレジスタのIOポートアドレス */
const uint16_t kConfigData = 0x0cfc;

void WriteAddress(uint32_t address);
void WriteData(uint32_t value);

uint32_t ReadData();
uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);
bool IsSingleFunctionDevice(uint8_t header_type);

struct Device {
    uint8_t bus, device, function, header_type;
};

/** @brief ScanAllBus() によって発見されたPCIデバイスの一覧 */
inline std::array<Device, 32> devices;
/** @brief devicesの有効な要素の数 */
inline int num_device;

/** @brief PCIデバイスを全て探索し、devicesに格納する
 *
 * バス0から再帰的にPCIデバイスを探索し、devicesの先頭から詰めて書き込む
 * 発見したデバイスの数をnum_devicesに設定する
 */
Error ScanAllBus();

}