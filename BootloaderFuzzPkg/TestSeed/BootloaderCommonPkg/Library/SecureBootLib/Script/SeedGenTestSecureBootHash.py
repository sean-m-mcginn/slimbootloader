## @file
#
# Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
#

'''
SeedGenSecureBootHash
'''

import argparse
from   ctypes import *
import random

#
# Globals for help information
#
__prog__      = 'SeedGenTestSecureBootHash'
__version__   = '%s Version %s' % (__prog__, '0.1 ')
__copyright__ = 'Copyright (c) 2023, Intel Corporation. All rights reserved.'
__usage__     = '%s [options] -o <output_file>' % (__prog__)

HASH_TYPE_NONE                  = 0
HASH_TYPE_SHA256                = 1
HASH_TYPE_SHA384                = 2
HASH_TYPE_SHA512                = 3
HASH_TYPE_SM3                   = 4

DATA_LENGTH                     = 100


class DO_HASH_VERIFY_INPUTS(Structure):
    _fields_ = [
        ('Data',                                    ARRAY(c_uint8, DATA_LENGTH)),
        ('Length',                                  c_uint32),
        ('Usage',                                   c_uint32),
        ('HashAlg',                                 c_uint8),
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

  DummyBuf = create_string_buffer(sizeof(DO_HASH_VERIFY_INPUTS))

  DoHashVerifyInputs = DO_HASH_VERIFY_INPUTS.from_buffer(DummyBuf, 0)
  for i in range(0, DATA_LENGTH):
    DoHashVerifyInputs.Data[i] = random.randint(0,255)
  DoHashVerifyInputs.Length = DATA_LENGTH
  DoHashVerifyInputs.Usage = 0
  DoHashVerifyInputs.HashAlg = HASH_TYPE_SHA256

  args.OutputFile.write(DummyBuf[2:])

  args.OutputFile.close()

