#ifndef STM32L432KC_DMA_H
#define STM32L432KC_DMA_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CCR;
    uint32_t CNDTR;
    uint32_t CPAR;
    uint32_t CMAR;
    uint32_t RESERVED;
} DMA_CHANNEL_REG_BLOCKS;

typedef struct {
    uint32_t ISR;
    uint32_t IFCR;
    DMA_CHANNEL_REG_BLOCKS CHANNEL[7];
    uint32_t RESERVED[5];
    uint32_t CSELR;
} DMA_REG_BLOCKS;

/* DMA registers as structs */

#define DMA1 ( (DMA_REG_BLOCKS volatile *) 0x40020000 )
#define DMA2 ( (DMA_REG_BLOCKS volatile *) 0x40020400 )

/* DMA ISR register macros */

#define DMA_ISR_GIF1(v) ( ( (v) & 0x1 ) << 0 )
#define DMA_ISR_GIF1_MASK DMA_ISR_GIF1(ALL1)
#define DMA_ISR_TCIF1(v) ( ( (v) & 0x1 ) << 1 )
#define DMA_ISR_TCIF1_MASK DMA_ISR_TCIF1(ALL1)
#define DMA_ISR_HTIF1(v) ( ( (v) & 0x1 ) << 2 )
#define DMA_ISR_HTIF1_MASK DMA_ISR_HTIF1(ALL1)
#define DMA_ISR_TEIF1(v) ( ( (v) & 0x1 ) << 3 )
#define DMA_ISR_TEIF1_MASK DMA_ISR_TEIF(ALL1)
#define DMA_ISR_GIF2(v) ( ( (v) & 0x1 ) << 4 )
#define DMA_ISR_GIF2_MASK DMA_ISR_GIF2(ALL1)
#define DMA_ISR_TCIF2(v) ( ( (v) & 0x1 ) << 5 )
#define DMA_ISR_TCIF2_MASK DMA_ISR_TCIF2(ALL1)
#define DMA_ISR_HTIF2(v) ( ( (v) & 0x1 ) << 6 )
#define DMA_ISR_HTIF2_MASK DMA_ISR_HTIF2(ALL1)
#define DMA_ISR_TEIF2(v) ( ( (v) & 0x1 ) << 7 )
#define DMA_ISR_TEIF2_MASK DMA_ISR_TEIF2(ALL1)
#define DMA_ISR_GIF3(v) ( ( (v) & 0x1 ) << 8 )
#define DMA_ISR_GIF3_MASK DMA_ISR_GIF3(ALL1)
#define DMA_ISR_TCIF3(v) ( ( (v) & 0x1 ) << 9 )
#define DMA_ISR_TCIF3_MASK DMA_ISR_TCIF3(ALL1)
#define DMA_ISR_HTIF3(v) ( ( (v) & 0x1 ) << 10 )
#define DMA_ISR_HTIF3_MASK DMA_ISR_HTIF3(ALL1)
#define DMA_ISR_TEIF3(v) ( ( (v) & 0x1 ) << 11 )
#define DMA_ISR_TEIF3_MASK DMA_ISR_TEIF3(ALL1)
#define DMA_ISR_GIF4(v) ( ( (v) & 0x1 ) << 12 )
#define DMA_ISR_GIF4_MASK DMA_ISR_GIF4(ALL1)
#define DMA_ISR_TCIF4(v) ( ( (v) & 0x1 ) << 13 )
#define DMA_ISR_TCIF4_MASK DMA_ISR_TCIF4(ALL1)
#define DMA_ISR_HTIF4(v) ( ( (v) & 0x1 ) << 14 )
#define DMA_ISR_HTIF4_MASK DMA_ISR_HTIF4(ALL1)
#define DMA_ISR_TEIF4(v) ( ( (v) & 0x1 ) << 15 )
#define DMA_ISR_TEIF4_MASK DMA_ISR_TEIF4(ALL1)
#define DMA_ISR_GIF5(v) ( ( (v) & 0x1 ) << 16 )
#define DMA_ISR_GIF5_MASK DMA_ISR_GIF5(ALL1)
#define DMA_ISR_TCIF5(v) ( ( (v) & 0x1 ) << 17 )
#define DMA_ISR_TCIF5_MASK DMA_ISR_TCIF5(ALL1)
#define DMA_ISR_HTIF5(v) ( ( (v) & 0x1 ) << 18 )
#define DMA_ISR_HTIF5_MASK DMA_ISR_HTIF5(ALL1)
#define DMA_ISR_TEIF5(v) ( ( (v) & 0x1 ) << 19 )
#define DMA_ISR_TEIF5_MASK DMA_ISR_TEIF5(ALL1)
#define DMA_ISR_GIF6(v) ( ( (v) & 0x1 ) << 20 )
#define DMA_ISR_GIF6_MASK DMA_ISR_GIF6(ALL1)
#define DMA_ISR_TCIF6(v) ( ( (v) & 0x1 ) << 21 )
#define DMA_ISR_TCIF6_MASK DMA_ISR_TCIF6(ALL1)
#define DMA_ISR_HTIF6(v) ( ( (v) & 0x1 ) << 22 )
#define DMA_ISR_HTIF6_MASK DMA_ISR_HTIF6(ALL1)
#define DMA_ISR_TEIF6(v) ( ( (v) & 0x1 ) << 23 )
#define DMA_ISR_TEIF6_MASK DMA_ISR_TEIF6(ALL1)
#define DMA_ISR_GIF7(v) ( ( (v) & 0x1 ) << 24 )
#define DMA_ISR_GIF7_MASK DMA_ISR_GIF7(ALL1)
#define DMA_ISR_TCIF7(v) ( ( (v) & 0x1 ) << 25 )
#define DMA_ISR_TCIF7_MASK DMA_ISR_TCIF7(ALL1)
#define DMA_ISR_HTIF7(v) ( ( (v) & 0x1 ) << 26 )
#define DMA_ISR_HTIF7_MASK DMA_ISR_HTIF7(ALL1)
#define DMA_ISR_TEIF7(v) ( ( (v) & 0x1 ) << 27 )
#define DMA_ISR_TEIF7_MASK DMA_ISR_TEIF7(ALL1)

/* DMA IFCR register macros */

#define DMA_IFCR_CGIF1(v) ( ( (v) & 0x1 ) << 0 )
#define DMA_IFCR_CGIF1_MASK DMA_IFCR_CGIF1(ALL1)
#define DMA_IFCR_CTCIF1(v) ( ( (v) & 0x1 ) << 1 )
#define DMA_IFCR_CTCIF1_MASK DMA_IFCR_CTCIF1(ALL1)
#define DMA_IFCR_CHTIF1(v) ( ( (v) & 0x1 ) << 2 )
#define DMA_IFCR_CHTIF1_MASK DMA_IFCR_CHTIF1(ALL1)
#define DMA_IFCR_CTEIF1(v) ( ( (v) & 0x1 ) << 3 )
#define DMA_IFCR_CTEIF1_MASK DMA_IFCR_CTEIF1(ALL1)
#define DMA_IFCR_CGIF2(v) ( ( (v) & 0x1 ) << 4 )
#define DMA_IFCR_CGIF2_MASK DMA_IFCR_CGIF2(ALL1)
#define DMA_IFCR_CTCIF2(v) ( ( (v) & 0x1 ) << 5 )
#define DMA_IFCR_CTCIF2_MASK DMA_IFCR_CTCIF2(ALL1)
#define DMA_IFCR_CHTIF2(v) ( ( (v) & 0x1 ) << 6 )
#define DMA_IFCR_CHTIF2_MASK DMA_IFCR_CHTIF2(ALL1)
#define DMA_IFCR_CTEIF2(v) ( ( (v) & 0x1 ) << 7 )
#define DMA_IFCR_CTEIF2_MASK DMA_IFCR_CTEIF2(ALL1)
#define DMA_IFCR_CGIF3(v) ( ( (v) & 0x1 ) << 8 )
#define DMA_IFCR_CGIF3_MASK DMA_IFCR_CGIF3(ALL1)
#define DMA_IFCR_CTCIF3(v) ( ( (v) & 0x1 ) << 9 )
#define DMA_IFCR_CTCIF3_MASK DMA_IFCR_CTCIF3(ALL1)
#define DMA_IFCR_CHTIF3(v) ( ( (v) & 0x1 ) << 10 )
#define DMA_IFCR_CHTIF3_MASK DMA_IFCR_CHTIF3(ALL1)
#define DMA_IFCR_CTEIF3(v) ( ( (v) & 0x1 ) << 11 )
#define DMA_IFCR_CTEIF3_MASK DMA_IFCR_CTEIF3(ALL1)
#define DMA_IFCR_CGIF4(v) ( ( (v) & 0x1 ) << 12 )
#define DMA_IFCR_CGIF4_MASK DMA_IFCR_CGIF4(ALL1)
#define DMA_IFCR_CTCIF4(v) ( ( (v) & 0x1 ) << 13 )
#define DMA_IFCR_CTCIF4_MASK DMA_IFCR_CTCIF4(ALL1)
#define DMA_IFCR_CHTIF4(v) ( ( (v) & 0x1 ) << 14 )
#define DMA_IFCR_CHTIF4_MASK DMA_IFCR_CHTIF4(ALL1)
#define DMA_IFCR_CTEIF4(v) ( ( (v) & 0x1 ) << 15 )
#define DMA_IFCR_CTEIF4_MASK DMA_IFCR_CTEIF4(ALL1)
#define DMA_IFCR_CGIF5(v) ( ( (v) & 0x1 ) << 16 )
#define DMA_IFCR_CGIF5_MASK DMA_IFCR_CGIF5(ALL1)
#define DMA_IFCR_CTCIF5(v) ( ( (v) & 0x1 ) << 17 )
#define DMA_IFCR_CTCIF5_MASK DMA_IFCR_CTCIF5(ALL1)
#define DMA_IFCR_CHTIF5(v) ( ( (v) & 0x1 ) << 18 )
#define DMA_IFCR_CHTIF5_MASK DMA_IFCR_CHTIF5(ALL1)
#define DMA_IFCR_CTEIF5(v) ( ( (v) & 0x1 ) << 19 )
#define DMA_IFCR_CTEIF5_MASK DMA_IFCR_CTEIF5(ALL1)
#define DMA_IFCR_CGIF6(v) ( ( (v) & 0x1 ) << 20 )
#define DMA_IFCR_CGIF6_MASK DMA_IFCR_CGIF6(ALL1)
#define DMA_IFCR_CTCIF6(v) ( ( (v) & 0x1 ) << 21 )
#define DMA_IFCR_CTCIF6_MASK DMA_IFCR_CTCIF6(ALL1)
#define DMA_IFCR_CHTIF6(v) ( ( (v) & 0x1 ) << 22 )
#define DMA_IFCR_CHTIF6_MASK DMA_IFCR_CHTIF6(ALL1)
#define DMA_IFCR_CTEIF6(v) ( ( (v) & 0x1 ) << 23 )
#define DMA_IFCR_CTEIF6_MASK DMA_IFCR_CTEIF6(ALL1)
#define DMA_IFCR_CGIF7(v) ( ( (v) & 0x1 ) << 24 )
#define DMA_IFCR_CGIF7_MASK DMA_IFCR_CGIF7(ALL1)
#define DMA_IFCR_CTCIF7(v) ( ( (v) & 0x1 ) << 25 )
#define DMA_IFCR_CTCIF7_MASK DMA_IFCR_CTCIF7(ALL1)
#define DMA_IFCR_CHTIF7(v) ( ( (v) & 0x1 ) << 26 )
#define DMA_IFCR_CHTIF7_MASK DMA_IFCR_CHTIF7(ALL1)
#define DMA_IFCR_CTEIF7(v) ( ( (v) & 0x1 ) << 27 )
#define DMA_IFCR_CTEIF7_MASK DMA_IFCR_CTEIF7(ALL1)

#define DMA_IFCR(v, m) ( (m) << ( ( (v) & 0x7 ) * 4 ) )
#define DMA_IFCR_MASK(v) ( ( 0xF << ( ( (v) & 0x7 ) * 4 ) ) )

/* DMA CCR register macros */

#define DMA_CCR_EN(v) ( ( (v) & 0x1 ) << 0 )
#define DMA_CCR_EN_MASK DMA_CCR_EN(ALL1)
#define DMA_CCR_TCIE(v) ( ( (v) & 0x1 ) << 1 )
#define DMA_CCR_TCIE_MASK DMA_CCR_TCIE(ALL1)
#define DMA_CCR_HTIE(v) ( ( (v) & 0x1 ) << 2 )
#define DMA_CCR_HTIE_MASK DMA_CCR_HTIE(ALL1)
#define DMA_CCR_TEIE(v) ( ( (v) & 0x1 ) << 3 )
#define DMA_CCR_TEIE_MASK DMA_CCR_TEIE(ALL1)
#define DMA_CCR_DIR(v) ( ( (v) & 0x1 ) << 4 )
#define DMA_CCR_DIR_MASK DMA_CCR_DIR(ALL1)
#define DMA_CCR_CIRC(v) ( ( (v) & 0x1 ) << 5 )
#define DMA_CCR_CIRC_MASK DMA_CCR_CIRC(ALL1)
#define DMA_CCR_PINC(v) ( ( (v) & 0x1 ) << 6 )
#define DMA_CCR_PINC_MASK DMA_CCR_PINC(ALL1)
#define DMA_CCR_MINC(v) ( ( (v) & 0x1 ) << 7 )
#define DMA_CCR_MINC_MASK DMA_CCR_MINC(ALL1)
#define DMA_CCR_PSIZE(v) ( ( (v) & 0x3 ) << 8 )
#define DMA_CCR_PSIZE_MASK DMA_CCR_PSIZE(ALL1)
#define DMA_CCR_MSIZE(v) ( ( (v) & 0x3 ) << 10 )
#define DMA_CCR_MSIZE_MASK DMA_CCR_MSIZE(ALL1)
#define DMA_CCR_PL(v) ( ( (v) & 0x3 ) << 12 )
#define DMA_CCR_PL_MASK DMA_CCR_PL(ALL1)
#define DMA_CCR_MEM2MEM(v) ( ( (v) & 0x1 ) << 14 )
#define DMA_CCR_MEM2MEM_MASK DMA_CCR_MEM2MEM(ALL1)

/* DMA CNDTR register macros */

#define DMA_CNDTR_NDT(v) ( ( (v) & 0xFFFF ) << 0 )
#define DMA_CNDTR_NDT_MASK DMA_CNDTR1_NDT(ALL1)

/* DMA CPAR register macros */

#define DMA_CPAR_PA(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define DMA_CPAR_PA_MASK DMA_CPAR_PA(ALL1)

/* DMA CMAR register macros */

#define DMA_CMAR_MA(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define DMA_CMAR_MA_MASK DMA_CMAR_MA(ALL1)

/* DMA CSELR register macros */

#define DMA_CSELR_C1S(v) ( ( (v) & 0xF ) << 0 )
#define DMA_CSELR_C1S_MASK DMA_CSELR_C1S(ALL1)
#define DMA_CSELR_C2S(v) ( ( (v) & 0xF ) << 4 )
#define DMA_CSELR_C2S_MASK DMA_CSELR_C2S(ALL1)
#define DMA_CSELR_C3S(v) ( ( (v) & 0xF ) << 8 )
#define DMA_CSELR_C3S_MASK DMA_CSELR_C3S(ALL1)
#define DMA_CSELR_C4S(v) ( ( (v) & 0xF ) << 12 )
#define DMA_CSELR_C4S_MASK DMA_CSELR_C4S(ALL1)
#define DMA_CSELR_C5S(v) ( ( (v) & 0xF ) << 16 )
#define DMA_CSELR_C5S_MASK DMA_CSELR_C5S(ALL1)
#define DMA_CSELR_C6S(v) ( ( (v) & 0xF ) << 20 )
#define DMA_CSELR_C6S_MASK DMA_CSELR_C6S(ALL1)
#define DMA_CSELR_C7S(v) ( ( (v) & 0xF ) << 24 )
#define DMA_CSELR_C7S_MASK DMA_CSELR_C7S(ALL1)

#define DMA_CSELR(v, m) ( (m) << ( (v) * 4 ) )
#define DMA_CSELR_MASK(v) ( ( 0xF << ( ( (v) & 0x7 ) * 4 ) ) )

#endif

