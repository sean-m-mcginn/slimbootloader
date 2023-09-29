## @file
#
# Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
#

'''
SeedGenTpm2Response
'''

import os
import sys
import argparse
import subprocess
import uuid
import struct
import collections
import binascii
import socket
from   ctypes import *

#
# Globals for help information
#
__prog__      = 'SeedGenTestTpm2Hierarchy'
__version__   = '%s Version %s' % (__prog__, '0.1 ')
__copyright__ = 'Copyright (c) 2023, Intel Corporation. All rights reserved.'
__usage__     = '%s [options] -o <output_file>' % (__prog__)

TPM_ST_NO_SESSIONS          = 0x8001
TPM_ST_SESSIONS             = 0x8002

TPM_RC_SUCCESS           = 0x000

SHA1_DIGEST_SIZE            = 20
SHA256_DIGEST_SIZE          = 32
SHA384_DIGEST_SIZE          = 48
SHA512_DIGEST_SIZE          = 64
SM3_256_DIGEST_SIZE         = 32

class TPM2_RESPONSE_HEADER(Structure):
    _fields_ = [
        ('Dummy',                                  c_uint16),
        ('tag',                                    c_uint16),
        ('paramSize',                              c_uint32),
        ('responseCode',                           c_uint32),
        ]

class TPMA_SESSION(Union):
    _fields_ = [
        ('continueSession',                 c_uint8, 1),
        ('auditExclusive',                  c_uint8, 1),
        ('auditReset',                      c_uint8, 1),
        ('reserved3_4',                     c_uint8, 2),
        ('decrypt',                         c_uint8, 1),
        ('encrypt',                         c_uint8, 1),
        ('audit',                           c_uint8, 1),
        ]
    
class TPMU_HA(Union):
    _fields_ = [
        ('sha1',                            ARRAY(c_uint8, SHA1_DIGEST_SIZE)),
        ('sha256',                          ARRAY(c_uint8, SHA256_DIGEST_SIZE)),
        ('sm3_256',                         ARRAY(c_uint8, SM3_256_DIGEST_SIZE)),
        ('sha384',                          ARRAY(c_uint8, SHA384_DIGEST_SIZE)),
        ('sha512',                          ARRAY(c_uint8, SHA512_DIGEST_SIZE)),
        ]
    
class TPM2B_DIGEST(Structure):
    _fields_ = [
        ('size',                            c_uint16),
        ('buffer',                          ARRAY(c_uint8, sizeof(TPMU_HA))),
        ]

class TPMS_AUTH_RESPONSE(Structure):
    _fields_ = [
        ('nonce',                           TPM2B_DIGEST),
        ('sessionAttributes',               TPMA_SESSION),
        ('hmac',                            TPM2B_DIGEST),
        ]
    
class TPM2_HIERARCHY_RESPONSE(Structure):
    _fields_ = [
        ('Header',                                 TPM2_RESPONSE_HEADER),
        ('ParameterSize',                          c_uint32),
        ('AuthSession',                            TPMS_AUTH_RESPONSE),
        ]

if __name__ == '__main__':
  #
  # Create command line argument parser object
  #
  
  parser = argparse.ArgumentParser(prog=__prog__, usage=__usage__, description=__copyright__, conflict_handler='resolve')
  parser.add_argument("-v", "--verbose", dest='Verbose', action="store_true", help="increase output messages")
  parser.add_argument("-q", "--quiet", dest='Quiet', action="store_true", help="reduce output messages")
  parser.add_argument("-o", "--output", dest='OutputFileName', type=str, metavar='filename', help="specify the output filename", required=True)

  #
  # Parse command line arguments
  #
  args = parser.parse_args()

  #
  # Write output file
  #
  args.OutputFile = open(args.OutputFileName, 'wb')

  DummyBuf = create_string_buffer(sizeof(TPM2_HIERARCHY_RESPONSE))

  Tpm2HierarchyResponse = TPM2_HIERARCHY_RESPONSE.from_buffer (DummyBuf, 0)
  Tpm2HierarchyResponse.Header.tag = socket.ntohs (TPM_ST_SESSIONS)
  Tpm2HierarchyResponse.Header.paramSize = socket.ntohl (0x96) # socket.ntohl (sizeof(TPM2_HIERARCHY_RESPONSE) - 2)
  Tpm2HierarchyResponse.Header.responseCode = socket.ntohl (TPM_RC_SUCCESS)
  Tpm2HierarchyResponse.ParameterSize = socket.ntohl (0x96)

  args.OutputFile.write(DummyBuf[2:])

  args.OutputFile.close()

