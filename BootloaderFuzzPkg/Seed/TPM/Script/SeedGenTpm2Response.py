## @file
#
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
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
__prog__      = 'SeedGenTpm2Response'
__version__   = '%s Version %s' % (__prog__, '0.1 ')
__copyright__ = 'Copyright (c) 2018, Intel Corporation. All rights reserved.'
__usage__     = '%s [options] -o <output_file>' % (__prog__)

TPM_ALG_SHA1           = 0x0004
TPM_ALG_SHA256         = 0x000B
TPM_ALG_SHA384         = 0x000C
TPM_ALG_SHA512         = 0x000D
TPM_ALG_SM3_256        = 0x0012

TPM_ST_NO_SESSIONS          = 0x8001
TPM_ST_SESSIONS             = 0x8002

TPM_RC_SUCCESS           = 0x000


class TPM2_RESPONSE_HEADER(Structure):
    _fields_ = [
        ('Dummy',                                  c_uint16),
        ('tag',                                    c_uint16),
        ('paramSize',                              c_uint32),
        ('responseCode',                           c_uint32),
        ]
    
class TPMS_PCR_SELECTION(Structure):
    _fields_ = [
        ('hash',                                    c_uint16),
        ('sizeofSelect',                            c_uint8),
        ('pcrSelect',                               ARRAY(c_uint8, 8)),
        ]
    
class TPML_PCR_SELECTION(Structure):
    _fields_ = [
        ('count',                                  c_uint32),
        ('pcrSelections',                          ARRAY(TPMS_PCR_SELECTION, 5)),
        ]


class TPMU_CAPABILITIES(Structure):
    _fields_ = [
        ('assignedPCR',                           TPML_PCR_SELECTION),
        ]

class TPMS_CAPABILITY_DATA(Structure):
    _fields_ = [
        ('capability',                             c_int32),
        ('data',                                   TPMU_CAPABILITIES),
        ]

class TPM2_GET_CAPABILITY_RESPONSE(Structure):
    _fields_ = [
        ('Header',                                 TPM2_RESPONSE_HEADER),
        ('MoreData',                               c_int8),
        ('CapabilityData',                         TPMS_CAPABILITY_DATA),
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

  DummyBuf = create_string_buffer(sizeof(TPM2_GET_CAPABILITY_RESPONSE))

  Tpm2GetCapabilityResponse = TPM2_GET_CAPABILITY_RESPONSE.from_buffer (DummyBuf, 0)
  Tpm2GetCapabilityResponse.Header.tag = socket.ntohs (TPM_ST_SESSIONS)
  Tpm2GetCapabilityResponse.Header.paramSize = socket.ntohl (0x54) # socket.ntohl (sizeof(TPM2_GET_CAPABILITY_RESPONSE) - 2)
  Tpm2GetCapabilityResponse.Header.responseCode = socket.ntohl (TPM_RC_SUCCESS)
  Tpm2GetCapabilityResponse.MoreData = socket.ntohl (0x0) # socket.ntohl (sizeof(TPM2_GET_CAPABILITY_RESPONSE) - 2)
  Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.count = 2
  Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[0].hash = TPM_ALG_SHA256
  memset(Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[0].pcrSelect, 0xFF, 3)
  Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[0].sizeofSelect = 3
  Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[1].hash = TPM_ALG_SHA384
  memset(Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[1].pcrSelect, 0xFF, 3)
  Tpm2GetCapabilityResponse.CapabilityData.data.assignedPCR.pcrSelections[1].sizeofSelect = 3

  args.OutputFile.write(DummyBuf[2:])

  args.OutputFile.close()

