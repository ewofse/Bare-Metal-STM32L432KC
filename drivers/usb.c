#include "usb.h"
#include <m4/nvic.h>
#include <stm32l432kc/usb.h>
#include <stm32l432kc/rcc.h>
#include <stm32l432kc/gpio.h>
#include <stm32l432kc/crs.h>
#include <stm32l432kc/pwr.h>
#include <util/cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#define USB_IRQ 67
#define USB_IRQ_PRI 15

#define GET_DESCRIPTOR 6
#define SET_ADDRESS 5
#define SET_CONFIGURATION 9
#define SET_LINE_CODING 0x20
#define GET_LINE_CODING 0x21
#define SET_CONTROL_LINE_STATE 0x22

#define DEVICE_DESCRIPTOR_TYPE 1
#define CONFIGURATION_DESCRIPTOR_TYPE 2

typedef struct __attribute__( (packed) ) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} device_descriptor_t;

typedef struct __attribute__( (packed) ) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} configuration_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint16_t bcdCDC;
} header_functional_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
    uint8_t bDataInterface;
} call_management_functional_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
} acm_functional_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bMasterInterface;
    uint8_t bSlaveInterface;
} union_functional_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} interface_descriptor_t;

typedef struct __attribute__( (packed) )  {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} endpoint_descriptor_t;

typedef struct __attribute__( (packed) )  {
    configuration_descriptor_t CONFIGURATION_DESCRIPTOR;
    interface_descriptor_t INTERFACE_0_DESCRIPTOR;
    header_functional_descriptor_t HEADER_FUNCTIONAL_DESCRIPTOR;
    call_management_functional_descriptor_t CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR;
    acm_functional_descriptor_t ACM_FUNCTIONAL_DESCRIPTOR;
    union_functional_descriptor_t UNION_FUNCTIONAL_DESCRIPTOR;
    endpoint_descriptor_t ENDPOINT_1_DESCRIPTOR;
    interface_descriptor_t INTERFACE_1_DESCRIPTOR;
    endpoint_descriptor_t ENDPOINT_2_OUT_DESCRIPTOR;
    endpoint_descriptor_t ENDPOINT_2_IN_DESCRIPTOR;
} descriptor_table_t;

typedef struct __attribute__( (packed) ) {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} control_packet_t;

typedef enum {
    EP0_IDLE,
    EP0_TX_IN_PROGRESS,
    EP0_STATUS_ADDRESS_PENDING,
    EP0_RX_LINE_CODING
} ep0_state_t;

static device_descriptor_t const DEVICE_DESCRIPTOR = {
    .bLength = 18,
    .bDescriptorType = 1,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x02,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 8,
    .idVendor = 0x0001,
    .idProduct = 0x0001,
    .bcdDevice = 0x0100,
    .iManufacturer = 0,
    .iProduct = 0,
    .iSerialNumber = 0,
    .bNumConfigurations = 1
};

static descriptor_table_t const DESCRIPTOR_TABLE = {
    .CONFIGURATION_DESCRIPTOR = {
        .bLength = 9,
        .bDescriptorType = 2,
        .wTotalLength = 67,
        .bNumInterfaces = 2,
        .bConfigurationValue = 1,
        .iConfiguration = 0,
        .bmAttributes = 0x80,
        .bMaxPower = 1
    },

    .INTERFACE_0_DESCRIPTOR = {
        .bLength = 9,
        .bDescriptorType = 4,
        .bInterfaceNumber = 0,
        .bAlternateSetting = 0,
        .bNumEndpoints = 1,
        .bInterfaceClass = 0x02,
        .bInterfaceSubClass = 0x02,
        .bInterfaceProtocol = 0,
        .iInterface = 0
    },

    .HEADER_FUNCTIONAL_DESCRIPTOR = {
        .bLength = 5,
        .bDescriptorType = 0x24,
        .bDescriptorSubtype = 0x00,
        .bcdCDC = 0x0110
    },

    .CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR = {
        .bLength = 5,
        .bDescriptorType = 0x24,
        .bDescriptorSubtype = 0x01,
        .bmCapabilities = 0x00,
        .bDataInterface = 1
    },

    .ACM_FUNCTIONAL_DESCRIPTOR = {
        .bLength = 4,
        .bDescriptorType = 0x24,
        .bDescriptorSubtype = 0x02,
        .bmCapabilities = 0x02
    },

    .UNION_FUNCTIONAL_DESCRIPTOR = {
        .bLength = 5,
        .bDescriptorType = 0x24,
        .bDescriptorSubtype = 0x06,
        .bMasterInterface = 0,
        .bSlaveInterface = 1
    },

    .ENDPOINT_1_DESCRIPTOR = {
        .bLength = 7,
        .bDescriptorType = 5,
        .bEndpointAddress = 0x81,
        .bmAttributes = 0x03,
        .wMaxPacketSize = 8,
        .bInterval = 10
    },

    .INTERFACE_1_DESCRIPTOR = {
        .bLength = 9,
        .bDescriptorType = 4,
        .bInterfaceNumber = 1,
        .bAlternateSetting = 0,
        .bNumEndpoints = 2,
        .bInterfaceClass = 0x0A,
        .bInterfaceSubClass = 0x00,
        .bInterfaceProtocol = 0,
        .iInterface = 0
    },

    .ENDPOINT_2_OUT_DESCRIPTOR = {
        .bLength = 7,
        .bDescriptorType = 5,
        .bEndpointAddress = 0x02,
        .bmAttributes = 0x02,
        .wMaxPacketSize = 32,
        .bInterval = 0
    },

    .ENDPOINT_2_IN_DESCRIPTOR = {
        .bLength = 7,
        .bDescriptorType = 5,
        .bEndpointAddress = 0x82,
        .bmAttributes = 0x02,
        .wMaxPacketSize = 32,
        .bInterval = 0
    }
};

static uint8_t raw_bytes[8];
static control_packet_t * control_packet;

static ep0_state_t ep0_state = EP0_IDLE;
static uint8_t pending_address;
static uint8_t line_coding[7];
static _Bool usb_enumerated = false;

static uint8_t const * ep0_tx_ptr;
static uint16_t ep0_tx_remaining;

//static cbuffer_t usb_rx_fifo;
//static cbuffer_t usb_tx_fifo;

static void configure_ep_bdt(void);

static void write_pma_data(uint16_t pma_byte_offest, uint8_t const * src,
    uint16_t byte_count);
static void read_pma_data(uint16_t pma_byte_offset, uint8_t * dest,
    uint16_t byte_count);

static void stage_ep0_tx(uint8_t const * data, uint16_t len);
static void stall_ep0(void);
static void set_ep_stat(uint32_t volatile * epr, uint8_t stat_tx, 
    uint8_t stat_rx);

/* Endpoint & BDT initialization */

static void configure_ep_bdt(void) {
    /* USB endpoint intializations */

    USB_FS->EP0R =
          USB_EPR_CTR_RX(0)
        | USB_EPR_DTOG_RX(0)
        | USB_EPR_STAT_RX(3)
        | USB_EPR_EP_TYPE(1)
        | USB_EPR_EP_KIND(0)
        | USB_EPR_CTR_TX(0)
        | USB_EPR_DTOG_TX(0)
        | USB_EPR_STAT_TX(2)
        | USB_EPR_EA(0);

    USB_FS->EP1R =
          USB_EPR_CTR_RX(0)
        | USB_EPR_DTOG_RX(0)
        | USB_EPR_STAT_RX(0)
        | USB_EPR_EP_TYPE(3)
        | USB_EPR_EP_KIND(0)
        | USB_EPR_CTR_TX(0)
        | USB_EPR_DTOG_TX(0)
        | USB_EPR_STAT_TX(0)
        | USB_EPR_EA(1);

    USB_FS->EP2R =
          USB_EPR_CTR_RX(0)
        | USB_EPR_DTOG_RX(0)
        | USB_EPR_STAT_RX(0)
        | USB_EPR_EP_TYPE(0)
        | USB_EPR_EP_KIND(0)
        | USB_EPR_CTR_TX(0)
        | USB_EPR_DTOG_TX(0)
        | USB_EPR_STAT_TX(0)
        | USB_EPR_EA(2);

    /* Build BDT endpoint entires for Virtual COM Port/CDC */

    USB_SRAM->BDT[0].ADDR_TX  = 0x40;
    USB_SRAM->BDT[0].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[0].ADDR_RX  = 0x80;
    USB_SRAM->BDT[0].COUNT_RX =
          USB_COUNT_RX_BLSIZE(1)
        | USB_COUNT_RX_NUM_BLOCK(1);

    USB_SRAM->BDT[1].ADDR_TX  = 0xC0;
    USB_SRAM->BDT[1].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[1].ADDR_RX  = 0;
    USB_SRAM->BDT[1].COUNT_RX = 0;

    USB_SRAM->BDT[2].ADDR_TX  = 0xD0;
    USB_SRAM->BDT[2].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[2].ADDR_RX  = 0x110;
    USB_SRAM->BDT[2].COUNT_RX =
          USB_COUNT_RX_BLSIZE(1)
        | USB_COUNT_RX_NUM_BLOCK(1);

    USB_FS->CNTR = USB_CNTR_RESETM(1) | USB_CNTR_CTRM(1);
    USB_FS->BCDR |= USB_BCDR_DPPU(1);
    USB_FS->DADDR |= USB_DADDR_EF(1);
}

/* Write data to the USB SRAM (PMA) */

static void write_pma_data(uint16_t pma_byte_offset, uint8_t const * src,
        uint16_t byte_count) {
    uint16_t pma_index = (pma_byte_offset - 64) / 2;

    /* Group the data bytes into half words and store into the USB SRAM */

    for ( uint16_t i = 0; i < (byte_count + 1) / 2; i++ ) {
        uint16_t half_word = src[i * 2];

        if ( (i * 2 + 1) < byte_count ) {
            half_word |= ( src[i * 2 + 1] << 8 );
        }

        USB_SRAM->PMA[pma_index++] = half_word;
    }
}

/* Read data from the USB SRAM (PMA) */

static void read_pma_data(uint16_t pma_byte_offset, uint8_t * dest,
        uint16_t byte_count) {
    uint16_t pma_index = (pma_byte_offset - 64) / 2;

    /* Extract half words from PMA and store into a byte array */

    for ( uint16_t i = 0; i < (byte_count + 1) / 2; i++ ) {
        uint16_t half_word = USB_SRAM->PMA[pma_index++];

        dest[i * 2] = half_word & 0xFF;

        if ( (i * 2 + 1) < byte_count ) {
            dest[i * 2 + 1] = (half_word >> 8) & 0xFF;
        }
    }
}

/* Prepare the next set of bytes in the message for transmission */

static void stage_ep0_tx(uint8_t const * data, uint16_t len) {
    uint16_t chunk = (len < 8) ? len : 8;

    if (chunk > 0) {
        write_pma_data(0x40, data, chunk);
    }

    USB_SRAM->BDT[0].COUNT_TX = USB_COUNT_TX_COUNT_TX(chunk);

    uint32_t ep0r = USB_FS->EP0R;
    uint32_t stat_rx = (ep0r & USB_EPR_STAT_RX_MASK) ^ USB_EPR_STAT_RX(3);
    uint32_t stat_tx = (ep0r & USB_EPR_STAT_TX_MASK) ^ USB_EPR_STAT_TX(3);

    USB_FS->EP0R = ( ep0r & (USB_EPR_EP_TYPE_MASK | USB_EPR_EP_KIND_MASK 
        | USB_EPR_EA_MASK) ) | stat_rx | stat_tx;

    ep0_tx_ptr = data + chunk;
    ep0_tx_remaining = len - chunk;
}

/* Pause commuincation on "unrecognized" requests */

static void stall_ep0(void) {
    uint32_t ep0r = USB_FS->EP0R;
    uint32_t stat_tx = (ep0r & USB_EPR_STAT_TX_MASK) ^ USB_EPR_STAT_TX(1);
    uint32_t stat_rx = (ep0r & USB_EPR_STAT_RX_MASK) ^ USB_EPR_STAT_RX(1);

    USB_FS->EP0R = ( ep0r & (USB_EPR_EP_TYPE_MASK | USB_EPR_EP_KIND_MASK | 
        USB_EPR_EA_MASK) ) | stat_tx | stat_rx;

    ep0_state = EP0_IDLE;
}

/* Set endpoint status */

static void set_ep_stat(volatile uint32_t * epr, uint8_t stat_tx, 
    uint8_t stat_rx) {
    uint32_t ep = *epr;

    uint32_t tx_toggle = (stat_tx != 0xFF)
        ? ( (ep & USB_EPR_STAT_TX_MASK) ^ USB_EPR_STAT_TX(stat_tx) ) : 0;
    uint32_t rx_toggle = (stat_rx != 0xFF)
        ? ( (ep & USB_EPR_STAT_RX_MASK) ^ USB_EPR_STAT_RX(stat_rx) ) : 0;

    *epr = ( ep & (USB_EPR_EP_TYPE_MASK | USB_EPR_EP_KIND_MASK 
        | USB_EPR_EA_MASK) ) | tx_toggle | rx_toggle;
}

/* Configure USB as Virtual COM/CDC */

void configure_usb(void) {
    /* Enable required independent VDD for USB peripheral */

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN(1);
    PWR->CR2 |= PWR_CR2_USV(1);

    /* Enable USB clock with autotrim for needed improved stability for USB */

    RCC->APB1ENR1 |= RCC_APB1ENR1_CRSEN(1);
    CRS->CR |= CRS_CR_AUTOTRIMEN(1) | CRS_CR_CEN(1);
    RCC->APB1ENR1 |= RCC_APB1ENR1_USBFSEN(1);

    /* IRQ enable and priority */

    NVIC->ISER[2] = NVIC_ISER_SETENA(1, USB_IRQ - 64);

    NVIC->IPR[16] =
        (NVIC->IPR[16] & ~NVIC_IPR16_PRI_67_MASK)
      | NVIC_IPR16_PRI_67(USB_IRQ_PRI);

    /* GPIO setup */

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN(1);

    GPIOA->MODER &= ~(GPIO_MODER_MODE11_MASK | GPIO_MODER_MODE12_MASK);
    GPIOA->MODER |= GPIO_MODER_MODE11(2) | GPIO_MODER_MODE12(2);

    GPIOA->AFR[1] &= ~(GPIO_AFR_AFSEL11_MASK | GPIO_AFR_AFSEL12_MASK);
    GPIOA->AFR[1] |= GPIO_AFR_AFSEL11(10) | GPIO_AFR_AFSEL12(10);

    /* Initialize peripheral with USB reset */

    USB_FS->CNTR = USB_CNTR_FRES(1);
    for (uint32_t volatile i = 0; i < 1280; i++); // 20 us delay
    USB_FS->CNTR &= ~USB_CNTR_FRES_MASK;

    USB_FS->ISTR = 0;
    USB_FS->BTABLE = USB_BTABLE_BTABLE(0);

    configure_ep_bdt();
}

_Bool usb_is_enumerated(void) {
    return usb_enumerated;
}

int usb_getchar(char * c) {
    if ( (USB_FS->EP2R & USB_EPR_STAT_RX_MASK) == USB_EPR_STAT_RX(3) ) {
        return -1;
    }

    uint8_t byte;

    read_pma_data(0x110, &byte, 1);
    *c = (char) byte;
    set_ep_stat(&USB_FS->EP2R, 0xFF, 3);

    return 0;
}

int usb_putchar(char c) {
    if (!usb_enumerated) {
        return -1;
    }

    if ( (USB_FS->EP2R & USB_EPR_STAT_TX_MASK) != USB_EPR_STAT_TX(2) ) {
        return -1;
    }

    uint8_t byte = (uint8_t) c;

    write_pma_data(0xD0, &byte, 1);
    USB_SRAM->BDT[2].COUNT_TX = USB_COUNT_TX_COUNT_TX(1);
    set_ep_stat(&USB_FS->EP2R, 3, 0xFF);

    return 0;
}

/* USB ISR */

void __attribute__( (interrupt) ) USB_FS_Handler(void) {
    uint32_t usb_irq_events = USB_FS->ISTR;

    if (usb_irq_events & USB_ISTR_RESET_MASK) {
        configure_ep_bdt();
    } else if (usb_irq_events & USB_ISTR_CTR_MASK) {
        uint8_t ep = usb_irq_events & USB_ISTR_EP_ID_MASK;
        _Bool dir = usb_irq_events & USB_ISTR_DIR_MASK;

        switch (ep) {
            case 0:
                if (USB_FS->EP0R & USB_EPR_SETUP_MASK) {
                    read_pma_data(0x80, raw_bytes, 8);

                    control_packet = (control_packet_t *) raw_bytes;

                    switch (control_packet->bRequest) {
                        case GET_DESCRIPTOR: {
                            uint8_t const * descriptor;
                            uint16_t descriptor_size;

                            uint8_t descriptor_type = 
                                control_packet->wValue >> 8;

                            if (descriptor_type == DEVICE_DESCRIPTOR_TYPE) {
                                descriptor = 
                                    (uint8_t const *) &DEVICE_DESCRIPTOR;

                                descriptor_size = sizeof(DEVICE_DESCRIPTOR);
                            } else if (descriptor_type == 
                                CONFIGURATION_DESCRIPTOR_TYPE) {

                                descriptor = 
                                    (uint8_t const *) &DESCRIPTOR_TABLE;

                                descriptor_size = sizeof(DESCRIPTOR_TABLE);
                            } else {
                                stall_ep0();
                                break;
                            }

                            uint16_t send_len =
                                (control_packet->wLength < descriptor_size)
                                    ? control_packet->wLength
                                    : descriptor_size;

                            stage_ep0_tx(descriptor, send_len);
                            ep0_state = (ep0_tx_remaining > 0)
                                ? EP0_TX_IN_PROGRESS : EP0_IDLE;

                            break;
                        }

                        case SET_ADDRESS:
                            pending_address = control_packet->wValue & 0x7F;
                            stage_ep0_tx(0, 0);
                            ep0_state = EP0_STATUS_ADDRESS_PENDING;

                            break;

                        case SET_CONFIGURATION:
                            set_ep_stat(&USB_FS->EP1R, 2, 0xFF);
                            set_ep_stat(&USB_FS->EP2R, 2, 3);
                            usb_enumerated = true;
                            stage_ep0_tx(0, 0);
                            ep0_state = EP0_IDLE;

                            break;

                        case SET_LINE_CODING:
                            ep0_state = EP0_RX_LINE_CODING;
                            break;

                        case GET_LINE_CODING:
                            stage_ep0_tx( line_coding, sizeof(line_coding) );
                            ep0_state = EP0_IDLE;
                            break;

                        case SET_CONTROL_LINE_STATE:
                            stage_ep0_tx(0, 0);
                            ep0_state = EP0_IDLE;
                            break;

                        default:
                            stall_ep0();
                            break;
                    };
                } else if (!dir) {
                    if (ep0_state == EP0_TX_IN_PROGRESS && 
                            ep0_tx_remaining > 0) {
                        stage_ep0_tx(ep0_tx_ptr, ep0_tx_remaining);

                        if (ep0_tx_remaining == 0) {
                            ep0_state = EP0_IDLE;
                        }
                    } else if (ep0_state == EP0_STATUS_ADDRESS_PENDING) {
                        USB_FS->DADDR = 
                            (pending_address & 0x7F) | USB_DADDR_EF(1);
                        ep0_state = EP0_IDLE;
                    }
                } else {
                    if (ep0_state == EP0_RX_LINE_CODING) {
                        read_pma_data( 0x80, line_coding, sizeof(line_coding) );
                        stage_ep0_tx(0, 0);
                        ep0_state = EP0_IDLE;
                    }
                }

                USB_FS->EP0R &=
                      USB_EPR_EP_TYPE_MASK
                    | USB_EPR_EP_KIND_MASK
                    | USB_EPR_EA_MASK;

                break;

            case 1:
                USB_FS->EP1R &=
                      USB_EPR_EP_TYPE_MASK
                    | USB_EPR_EP_KIND_MASK
                    | USB_EPR_EA_MASK;

                break;

            case 2:
                USB_FS->EP2R &=
                      USB_EPR_EP_TYPE_MASK
                    | USB_EPR_EP_KIND_MASK
                    | USB_EPR_EA_MASK;

                break;
        };
    }
}

