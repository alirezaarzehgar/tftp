#if !defined(TFTP_HDR_H)
#define TFTP_HDR_H

struct  tftphdr
{
  short th_opcode;      /* packet type */
  union
  {
    char  tu_padding[3];    /* sizeof() compat */
    struct
    {
      union
      {
        unsigned short  tu_block; /* block # */
        short tu_code;    /* error code */
      } __attribute__ ((__packed__)) th_u3;
      char tu_data[0];  /* data or error string */
    } __attribute__ ((__packed__)) th_u2;
    char  tu_stuff[0];    /* request packet stuff */
  } __attribute__ ((__packed__)) th_u1;
} __attribute__ ((__packed__));

typedef struct tftphdr tftphdr_t;

#endif // TFTP_HDR_H
