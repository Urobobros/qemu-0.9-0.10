#include "hw.h"
#include "pc.h"
#include "pci.h"
#include "console.h"
#include "vga_int.h"

typedef struct PCIS3VGAState {
    PCIDevice dev;
    VGAState vga;
} PCIS3VGAState;

static void pci_s3vga_map(PCIDevice *d, int region_num,
                          uint32_t addr, uint32_t size, int type)
{
    VGAState *s = &container_of(d, PCIS3VGAState, dev)->vga;
    vga_map(s, addr, size, type);
}

static void pci_s3vga_write_config(PCIDevice *d, uint32_t address,
                                   uint32_t val, int len)
{
    pci_default_write_config(d, address, val, len);
}

void pci_s3virge_vga_init(PCIBus *bus, uint8_t *vga_ram_base,
                          ram_addr_t vga_ram_offset, int vga_ram_size)
{
    PCIS3VGAState *d;
    VGAState *s;
    uint8_t *pci_conf;

    d = (PCIS3VGAState *)pci_register_device(bus, "S3 ViRGE VGA",
                                             sizeof(PCIS3VGAState),
                                             -1, NULL, pci_s3vga_write_config);
    if (!d)
        return;

    s = &d->vga;
    vga_common_init(s, vga_ram_base, vga_ram_offset, vga_ram_size);
    vga_init(s);

    s->ds = graphic_console_init(s->update, s->invalidate,
                                 s->screen_dump, s->text_update, s);

    s->pci_dev = &d->dev;
    pci_conf = d->dev.config;
    pci_config_set_vendor_id(pci_conf, PCI_VENDOR_ID_S3);
    pci_config_set_device_id(pci_conf, PCI_DEVICE_ID_S3_VIRGE);
    pci_config_set_class(pci_conf, PCI_CLASS_DISPLAY_VGA);
    pci_conf[0x0e] = 0x00;

    pci_register_io_region(&d->dev, 0, vga_ram_size,
                           PCI_ADDRESS_SPACE_MEM_PREFETCH, pci_s3vga_map);
}

void isa_s3virge_vga_init(uint8_t *vga_ram_base,
                          ram_addr_t vga_ram_offset, int vga_ram_size)
{
    VGAState *s = qemu_mallocz(sizeof(VGAState));

    vga_common_init(s, vga_ram_base, vga_ram_offset, vga_ram_size);
    vga_init(s);
    s->ds = graphic_console_init(s->update, s->invalidate,
                                 s->screen_dump, s->text_update, s);
}
