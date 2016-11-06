#ifndef MYSTRUCT_H
#define MYSTRUCT_H

struct dataFormat {
    quint16 vola[16],stre[8],weae[4];//,vinc[4];
    quint8 ttlout[4];
};

struct dataCurSelected {
    quint16 curvola,curstre,curweae;
};

struct Intr {
    quint16 startpos,endpos;
    quint8 intr;
    quint8 tunel;
    //quint8 crc;
};

struct vincData {
    quint16 vinc0[64],vinc1[64],vinc2[64],vinc3[64];
};

#endif // MYSTRUCT_H
