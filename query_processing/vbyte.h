/*
 * vbyte.h
 *
 *  Created on: Apr 2, 2013
 *      Author: Adam57
 */

#ifndef VBYTE_H_
#define VBYTE_H_


int writeVbyte(unsigned int ui, unsigned char* buf){

        int len = 0;

        while( (ui & ~0x7F) != 0){
//        	printf("%u, larger than 127\n", ui);
            buf[len++] = ((ui & 0x7F) | 0x80 );
//            printf("%u, still larger than 127\n", ((ui & 0x7F) | 0x80 ));
            ui >>= 7;
//            printf("%u, after shifting\n", ui);
        }
        buf[len++] = ui;

        return len;
    }

int readVbyte(unsigned char * buf, unsigned int & res){

        int pos = 0;
        unsigned char b = buf[pos++];
        res = b & 0x7F;

        int shift;
        for(shift = 7; (b & 0x80) !=0; shift+=7){
            b = buf[pos++];
            res |= ((b & 0x7F) << shift);
        }

        return pos;
    }

#endif /* VBYTE_H_ */
