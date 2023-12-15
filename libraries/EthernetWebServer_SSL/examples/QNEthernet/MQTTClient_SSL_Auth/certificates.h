#ifndef _CERTIFICATES_H_
#define _CERTIFICATES_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* This file is auto-generated by the pycert_bearssl tool.  Do not change it manually.
   Certificates are BearSSL br_x509_trust_anchor format.  Included certs:

   Index:    0
   Label:    COMODO RSA Certification Authority
   Subject:  CN=COMODO RSA Certification Authority,O=COMODO CA Limited,L=Salford,ST=Greater Manchester,C=GB
   Domain(s): hivemq.com

   Index:    1
   Label:    AAA Certificate Services
   Subject:  CN=AAA Certificate Services,O=Comodo CA Limited,L=Salford,ST=Greater Manchester,C=GB
   Domain(s): emqx.io

   Index:    2
   Label:    DST Root CA X3
   Subject:  CN=DST Root CA X3,O=Digital Signature Trust Co.
   Domain(s): mosquitto.org
*/

#define TAs_NUM 3

static const unsigned char TA_DN0[] =
{
  0x30, 0x81, 0x85, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
  0x13, 0x02, 0x47, 0x42, 0x31, 0x1b, 0x30, 0x19, 0x06, 0x03, 0x55, 0x04,
  0x08, 0x13, 0x12, 0x47, 0x72, 0x65, 0x61, 0x74, 0x65, 0x72, 0x20, 0x4d,
  0x61, 0x6e, 0x63, 0x68, 0x65, 0x73, 0x74, 0x65, 0x72, 0x31, 0x10, 0x30,
  0x0e, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x07, 0x53, 0x61, 0x6c, 0x66,
  0x6f, 0x72, 0x64, 0x31, 0x1a, 0x30, 0x18, 0x06, 0x03, 0x55, 0x04, 0x0a,
  0x13, 0x11, 0x43, 0x4f, 0x4d, 0x4f, 0x44, 0x4f, 0x20, 0x43, 0x41, 0x20,
  0x4c, 0x69, 0x6d, 0x69, 0x74, 0x65, 0x64, 0x31, 0x2b, 0x30, 0x29, 0x06,
  0x03, 0x55, 0x04, 0x03, 0x13, 0x22, 0x43, 0x4f, 0x4d, 0x4f, 0x44, 0x4f,
  0x20, 0x52, 0x53, 0x41, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69,
  0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f,
  0x72, 0x69, 0x74, 0x79,
};

static const unsigned char TA_RSA_N0[] =
{
  0x91, 0xe8, 0x54, 0x92, 0xd2, 0x0a, 0x56, 0xb1, 0xac, 0x0d, 0x24, 0xdd,
  0xc5, 0xcf, 0x44, 0x67, 0x74, 0x99, 0x2b, 0x37, 0xa3, 0x7d, 0x23, 0x70,
  0x00, 0x71, 0xbc, 0x53, 0xdf, 0xc4, 0xfa, 0x2a, 0x12, 0x8f, 0x4b, 0x7f,
  0x10, 0x56, 0xbd, 0x9f, 0x70, 0x72, 0xb7, 0x61, 0x7f, 0xc9, 0x4b, 0x0f,
  0x17, 0xa7, 0x3d, 0xe3, 0xb0, 0x04, 0x61, 0xee, 0xff, 0x11, 0x97, 0xc7,
  0xf4, 0x86, 0x3e, 0x0a, 0xfa, 0x3e, 0x5c, 0xf9, 0x93, 0xe6, 0x34, 0x7a,
  0xd9, 0x14, 0x6b, 0xe7, 0x9c, 0xb3, 0x85, 0xa0, 0x82, 0x7a, 0x76, 0xaf,
  0x71, 0x90, 0xd7, 0xec, 0xfd, 0x0d, 0xfa, 0x9c, 0x6c, 0xfa, 0xdf, 0xb0,
  0x82, 0xf4, 0x14, 0x7e, 0xf9, 0xbe, 0xc4, 0xa6, 0x2f, 0x4f, 0x7f, 0x99,
  0x7f, 0xb5, 0xfc, 0x67, 0x43, 0x72, 0xbd, 0x0c, 0x00, 0xd6, 0x89, 0xeb,
  0x6b, 0x2c, 0xd3, 0xed, 0x8f, 0x98, 0x1c, 0x14, 0xab, 0x7e, 0xe5, 0xe3,
  0x6e, 0xfc, 0xd8, 0xa8, 0xe4, 0x92, 0x24, 0xda, 0x43, 0x6b, 0x62, 0xb8,
  0x55, 0xfd, 0xea, 0xc1, 0xbc, 0x6c, 0xb6, 0x8b, 0xf3, 0x0e, 0x8d, 0x9a,
  0xe4, 0x9b, 0x6c, 0x69, 0x99, 0xf8, 0x78, 0x48, 0x30, 0x45, 0xd5, 0xad,
  0xe1, 0x0d, 0x3c, 0x45, 0x60, 0xfc, 0x32, 0x96, 0x51, 0x27, 0xbc, 0x67,
  0xc3, 0xca, 0x2e, 0xb6, 0x6b, 0xea, 0x46, 0xc7, 0xc7, 0x20, 0xa0, 0xb1,
  0x1f, 0x65, 0xde, 0x48, 0x08, 0xba, 0xa4, 0x4e, 0xa9, 0xf2, 0x83, 0x46,
  0x37, 0x84, 0xeb, 0xe8, 0xcc, 0x81, 0x48, 0x43, 0x67, 0x4e, 0x72, 0x2a,
  0x9b, 0x5c, 0xbd, 0x4c, 0x1b, 0x28, 0x8a, 0x5c, 0x22, 0x7b, 0xb4, 0xab,
  0x98, 0xd9, 0xee, 0xe0, 0x51, 0x83, 0xc3, 0x09, 0x46, 0x4e, 0x6d, 0x3e,
  0x99, 0xfa, 0x95, 0x17, 0xda, 0x7c, 0x33, 0x57, 0x41, 0x3c, 0x8d, 0x51,
  0xed, 0x0b, 0xb6, 0x5c, 0xaf, 0x2c, 0x63, 0x1a, 0xdf, 0x57, 0xc8, 0x3f,
  0xbc, 0xe9, 0x5d, 0xc4, 0x9b, 0xaf, 0x45, 0x99, 0xe2, 0xa3, 0x5a, 0x24,
  0xb4, 0xba, 0xa9, 0x56, 0x3d, 0xcf, 0x6f, 0xaa, 0xff, 0x49, 0x58, 0xbe,
  0xf0, 0xa8, 0xff, 0xf4, 0xb8, 0xad, 0xe9, 0x37, 0xfb, 0xba, 0xb8, 0xf4,
  0x0b, 0x3a, 0xf9, 0xe8, 0x43, 0x42, 0x1e, 0x89, 0xd8, 0x84, 0xcb, 0x13,
  0xf1, 0xd9, 0xbb, 0xe1, 0x89, 0x60, 0xb8, 0x8c, 0x28, 0x56, 0xac, 0x14,
  0x1d, 0x9c, 0x0a, 0xe7, 0x71, 0xeb, 0xcf, 0x0e, 0xdd, 0x3d, 0xa9, 0x96,
  0xa1, 0x48, 0xbd, 0x3c, 0xf7, 0xaf, 0xb5, 0x0d, 0x22, 0x4c, 0xc0, 0x11,
  0x81, 0xec, 0x56, 0x3b, 0xf6, 0xd3, 0xa2, 0xe2, 0x5b, 0xb7, 0xb2, 0x04,
  0x22, 0x52, 0x95, 0x80, 0x93, 0x69, 0xe8, 0x8e, 0x4c, 0x65, 0xf1, 0x91,
  0x03, 0x2d, 0x70, 0x74, 0x02, 0xea, 0x8b, 0x67, 0x15, 0x29, 0x69, 0x52,
  0x02, 0xbb, 0xd7, 0xdf, 0x50, 0x6a, 0x55, 0x46, 0xbf, 0xa0, 0xa3, 0x28,
  0x61, 0x7f, 0x70, 0xd0, 0xc3, 0xa2, 0xaa, 0x2c, 0x21, 0xaa, 0x47, 0xce,
  0x28, 0x9c, 0x06, 0x45, 0x76, 0xbf, 0x82, 0x18, 0x27, 0xb4, 0xd5, 0xae,
  0xb4, 0xcb, 0x50, 0xe6, 0x6b, 0xf4, 0x4c, 0x86, 0x71, 0x30, 0xe9, 0xa6,
  0xdf, 0x16, 0x86, 0xe0, 0xd8, 0xff, 0x40, 0xdd, 0xfb, 0xd0, 0x42, 0x88,
  0x7f, 0xa3, 0x33, 0x3a, 0x2e, 0x5c, 0x1e, 0x41, 0x11, 0x81, 0x63, 0xce,
  0x18, 0x71, 0x6b, 0x2b, 0xec, 0xa6, 0x8a, 0xb7, 0x31, 0x5c, 0x3a, 0x6a,
  0x47, 0xe0, 0xc3, 0x79, 0x59, 0xd6, 0x20, 0x1a, 0xaf, 0xf2, 0x6a, 0x98,
  0xaa, 0x72, 0xbc, 0x57, 0x4a, 0xd2, 0x4b, 0x9d, 0xbb, 0x10, 0xfc, 0xb0,
  0x4c, 0x41, 0xe5, 0xed, 0x1d, 0x3d, 0x5e, 0x28, 0x9d, 0x9c, 0xcc, 0xbf,
  0xb3, 0x51, 0xda, 0xa7, 0x47, 0xe5, 0x84, 0x53,
};

static const unsigned char TA_RSA_E0[] =
{
  0x01, 0x00, 0x01,
};

static const unsigned char TA_DN1[] =
{
  0x30, 0x7b, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
  0x02, 0x47, 0x42, 0x31, 0x1b, 0x30, 0x19, 0x06, 0x03, 0x55, 0x04, 0x08,
  0x0c, 0x12, 0x47, 0x72, 0x65, 0x61, 0x74, 0x65, 0x72, 0x20, 0x4d, 0x61,
  0x6e, 0x63, 0x68, 0x65, 0x73, 0x74, 0x65, 0x72, 0x31, 0x10, 0x30, 0x0e,
  0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x07, 0x53, 0x61, 0x6c, 0x66, 0x6f,
  0x72, 0x64, 0x31, 0x1a, 0x30, 0x18, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c,
  0x11, 0x43, 0x6f, 0x6d, 0x6f, 0x64, 0x6f, 0x20, 0x43, 0x41, 0x20, 0x4c,
  0x69, 0x6d, 0x69, 0x74, 0x65, 0x64, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03,
  0x55, 0x04, 0x03, 0x0c, 0x18, 0x41, 0x41, 0x41, 0x20, 0x43, 0x65, 0x72,
  0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x20, 0x53, 0x65, 0x72,
  0x76, 0x69, 0x63, 0x65, 0x73,
};

static const unsigned char TA_RSA_N1[] =
{
  0xbe, 0x40, 0x9d, 0xf4, 0x6e, 0xe1, 0xea, 0x76, 0x87, 0x1c, 0x4d, 0x45,
  0x44, 0x8e, 0xbe, 0x46, 0xc8, 0x83, 0x06, 0x9d, 0xc1, 0x2a, 0xfe, 0x18,
  0x1f, 0x8e, 0xe4, 0x02, 0xfa, 0xf3, 0xab, 0x5d, 0x50, 0x8a, 0x16, 0x31,
  0x0b, 0x9a, 0x06, 0xd0, 0xc5, 0x70, 0x22, 0xcd, 0x49, 0x2d, 0x54, 0x63,
  0xcc, 0xb6, 0x6e, 0x68, 0x46, 0x0b, 0x53, 0xea, 0xcb, 0x4c, 0x24, 0xc0,
  0xbc, 0x72, 0x4e, 0xea, 0xf1, 0x15, 0xae, 0xf4, 0x54, 0x9a, 0x12, 0x0a,
  0xc3, 0x7a, 0xb2, 0x33, 0x60, 0xe2, 0xda, 0x89, 0x55, 0xf3, 0x22, 0x58,
  0xf3, 0xde, 0xdc, 0xcf, 0xef, 0x83, 0x86, 0xa2, 0x8c, 0x94, 0x4f, 0x9f,
  0x68, 0xf2, 0x98, 0x90, 0x46, 0x84, 0x27, 0xc7, 0x76, 0xbf, 0xe3, 0xcc,
  0x35, 0x2c, 0x8b, 0x5e, 0x07, 0x64, 0x65, 0x82, 0xc0, 0x48, 0xb0, 0xa8,
  0x91, 0xf9, 0x61, 0x9f, 0x76, 0x20, 0x50, 0xa8, 0x91, 0xc7, 0x66, 0xb5,
  0xeb, 0x78, 0x62, 0x03, 0x56, 0xf0, 0x8a, 0x1a, 0x13, 0xea, 0x31, 0xa3,
  0x1e, 0xa0, 0x99, 0xfd, 0x38, 0xf6, 0xf6, 0x27, 0x32, 0x58, 0x6f, 0x07,
  0xf5, 0x6b, 0xb8, 0xfb, 0x14, 0x2b, 0xaf, 0xb7, 0xaa, 0xcc, 0xd6, 0x63,
  0x5f, 0x73, 0x8c, 0xda, 0x05, 0x99, 0xa8, 0x38, 0xa8, 0xcb, 0x17, 0x78,
  0x36, 0x51, 0xac, 0xe9, 0x9e, 0xf4, 0x78, 0x3a, 0x8d, 0xcf, 0x0f, 0xd9,
  0x42, 0xe2, 0x98, 0x0c, 0xab, 0x2f, 0x9f, 0x0e, 0x01, 0xde, 0xef, 0x9f,
  0x99, 0x49, 0xf1, 0x2d, 0xdf, 0xac, 0x74, 0x4d, 0x1b, 0x98, 0xb5, 0x47,
  0xc5, 0xe5, 0x29, 0xd1, 0xf9, 0x90, 0x18, 0xc7, 0x62, 0x9c, 0xbe, 0x83,
  0xc7, 0x26, 0x7b, 0x3e, 0x8a, 0x25, 0xc7, 0xc0, 0xdd, 0x9d, 0xe6, 0x35,
  0x68, 0x10, 0x20, 0x9d, 0x8f, 0xd8, 0xde, 0xd2, 0xc3, 0x84, 0x9c, 0x0d,
  0x5e, 0xe8, 0x2f, 0xc9,
};

static const unsigned char TA_RSA_E1[] =
{
  0x01, 0x00, 0x01,
};

static const unsigned char TA_DN2[] =
{
  0x30, 0x3f, 0x31, 0x24, 0x30, 0x22, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13,
  0x1b, 0x44, 0x69, 0x67, 0x69, 0x74, 0x61, 0x6c, 0x20, 0x53, 0x69, 0x67,
  0x6e, 0x61, 0x74, 0x75, 0x72, 0x65, 0x20, 0x54, 0x72, 0x75, 0x73, 0x74,
  0x20, 0x43, 0x6f, 0x2e, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04,
  0x03, 0x13, 0x0e, 0x44, 0x53, 0x54, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20,
  0x43, 0x41, 0x20, 0x58, 0x33,
};

static const unsigned char TA_RSA_N2[] =
{
  0xdf, 0xaf, 0xe9, 0x97, 0x50, 0x08, 0x83, 0x57, 0xb4, 0xcc, 0x62, 0x65,
  0xf6, 0x90, 0x82, 0xec, 0xc7, 0xd3, 0x2c, 0x6b, 0x30, 0xca, 0x5b, 0xec,
  0xd9, 0xc3, 0x7d, 0xc7, 0x40, 0xc1, 0x18, 0x14, 0x8b, 0xe0, 0xe8, 0x33,
  0x76, 0x49, 0x2a, 0xe3, 0x3f, 0x21, 0x49, 0x93, 0xac, 0x4e, 0x0e, 0xaf,
  0x3e, 0x48, 0xcb, 0x65, 0xee, 0xfc, 0xd3, 0x21, 0x0f, 0x65, 0xd2, 0x2a,
  0xd9, 0x32, 0x8f, 0x8c, 0xe5, 0xf7, 0x77, 0xb0, 0x12, 0x7b, 0xb5, 0x95,
  0xc0, 0x89, 0xa3, 0xa9, 0xba, 0xed, 0x73, 0x2e, 0x7a, 0x0c, 0x06, 0x32,
  0x83, 0xa2, 0x7e, 0x8a, 0x14, 0x30, 0xcd, 0x11, 0xa0, 0xe1, 0x2a, 0x38,
  0xb9, 0x79, 0x0a, 0x31, 0xfd, 0x50, 0xbd, 0x80, 0x65, 0xdf, 0xb7, 0x51,
  0x63, 0x83, 0xc8, 0xe2, 0x88, 0x61, 0xea, 0x4b, 0x61, 0x81, 0xec, 0x52,
  0x6b, 0xb9, 0xa2, 0xe2, 0x4b, 0x1a, 0x28, 0x9f, 0x48, 0xa3, 0x9e, 0x0c,
  0xda, 0x09, 0x8e, 0x3e, 0x17, 0x2e, 0x1e, 0xdd, 0x20, 0xdf, 0x5b, 0xc6,
  0x2a, 0x8a, 0xab, 0x2e, 0xbd, 0x70, 0xad, 0xc5, 0x0b, 0x1a, 0x25, 0x90,
  0x74, 0x72, 0xc5, 0x7b, 0x6a, 0xab, 0x34, 0xd6, 0x30, 0x89, 0xff, 0xe5,
  0x68, 0x13, 0x7b, 0x54, 0x0b, 0xc8, 0xd6, 0xae, 0xec, 0x5a, 0x9c, 0x92,
  0x1e, 0x3d, 0x64, 0xb3, 0x8c, 0xc6, 0xdf, 0xbf, 0xc9, 0x41, 0x70, 0xec,
  0x16, 0x72, 0xd5, 0x26, 0xec, 0x38, 0x55, 0x39, 0x43, 0xd0, 0xfc, 0xfd,
  0x18, 0x5c, 0x40, 0xf1, 0x97, 0xeb, 0xd5, 0x9a, 0x9b, 0x8d, 0x1d, 0xba,
  0xda, 0x25, 0xb9, 0xc6, 0xd8, 0xdf, 0xc1, 0x15, 0x02, 0x3a, 0xab, 0xda,
  0x6e, 0xf1, 0x3e, 0x2e, 0xf5, 0x5c, 0x08, 0x9c, 0x3c, 0xd6, 0x83, 0x69,
  0xe4, 0x10, 0x9b, 0x19, 0x2a, 0xb6, 0x29, 0x57, 0xe3, 0xe5, 0x3d, 0x9b,
  0x9f, 0xf0, 0x02, 0x5d,
};

static const unsigned char TA_RSA_E2[] =
{
  0x01, 0x00, 0x01,
};

static const br_x509_trust_anchor TAs[] =
{
  {
    { (unsigned char *)TA_DN0, sizeof TA_DN0 },
    BR_X509_TA_CA,
    {
      BR_KEYTYPE_RSA,
      {
        .rsa = {
          (unsigned char *)TA_RSA_N0, sizeof TA_RSA_N0,
          (unsigned char *)TA_RSA_E0, sizeof TA_RSA_E0,
        }
      }
    }
  },
  {
    { (unsigned char *)TA_DN1, sizeof TA_DN1 },
    BR_X509_TA_CA,
    {
      BR_KEYTYPE_RSA,
      {
        .rsa = {
          (unsigned char *)TA_RSA_N1, sizeof TA_RSA_N1,
          (unsigned char *)TA_RSA_E1, sizeof TA_RSA_E1,
        }
      }
    }
  },
  {
    { (unsigned char *)TA_DN2, sizeof TA_DN2 },
    BR_X509_TA_CA,
    {
      BR_KEYTYPE_RSA,
      {
        .rsa = {
          (unsigned char *)TA_RSA_N2, sizeof TA_RSA_N2,
          (unsigned char *)TA_RSA_E2, sizeof TA_RSA_E2,
        }
      }
    }
  },
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef _CERTIFICATES_H_ */