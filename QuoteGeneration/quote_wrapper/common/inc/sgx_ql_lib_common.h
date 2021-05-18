/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
* File: sgx_ql_lib_common.h
*
* Description: Common defintions for high-level quote APIs
*
*/

/* User defined types */
#ifndef _SGX_QL_LIB_COMMON_H_
#define _SGX_QL_LIB_COMMON_H_

#include "sgx_key.h"

#define SGX_QL_MK_ERROR(x)              (0x0000E000|(x))

/** Possible errors generated by the quote interface. */
typedef enum _quote3_error_t {
    SGX_QL_SUCCESS = 0x0000,                                         ///< Success
    SGX_QL_ERROR_MIN = SGX_QL_MK_ERROR(0x0001),                      ///< Indicate min error to allow better translation.
    SGX_QL_ERROR_UNEXPECTED = SGX_QL_MK_ERROR(0x0001),               ///< Unexpected error
    SGX_QL_ERROR_INVALID_PARAMETER = SGX_QL_MK_ERROR(0x0002),        ///< The parameter is incorrect
    SGX_QL_ERROR_OUT_OF_MEMORY = SGX_QL_MK_ERROR(0x0003),            ///< Not enough memory is available to complete this operation
    SGX_QL_ERROR_ECDSA_ID_MISMATCH = SGX_QL_MK_ERROR(0x0004),        ///< Expected ECDSA_ID does not match the value stored in the ECDSA Blob
    SGX_QL_PATHNAME_BUFFER_OVERFLOW_ERROR = SGX_QL_MK_ERROR(0x0005), ///< The ECDSA blob pathname is too large
    SGX_QL_FILE_ACCESS_ERROR = SGX_QL_MK_ERROR(0x0006),              ///< Error accessing ECDSA blob
    SGX_QL_ERROR_STORED_KEY = SGX_QL_MK_ERROR(0x0007),               ///< Cached ECDSA key is invalid
    SGX_QL_ERROR_PUB_KEY_ID_MISMATCH = SGX_QL_MK_ERROR(0x0008),      ///< Cached ECDSA key does not match requested key
    SGX_QL_ERROR_INVALID_PCE_SIG_SCHEME = SGX_QL_MK_ERROR(0x0009),   ///< PCE use the incorrect signature scheme
    SGX_QL_ATT_KEY_BLOB_ERROR = SGX_QL_MK_ERROR(0x000a),             ///< There is a problem with the attestation key blob.
    SGX_QL_UNSUPPORTED_ATT_KEY_ID = SGX_QL_MK_ERROR(0x000b),         ///< Unsupported attestation key ID.
    SGX_QL_UNSUPPORTED_LOADING_POLICY = SGX_QL_MK_ERROR(0x000c),     ///< Unsupported enclave loading policy.
    SGX_QL_INTERFACE_UNAVAILABLE = SGX_QL_MK_ERROR(0x000d),          ///< Unable to load the QE enclave
    SGX_QL_PLATFORM_LIB_UNAVAILABLE = SGX_QL_MK_ERROR(0x000e),       ///< Unable to find the platform library with the dependent APIs.  Not fatal.
    SGX_QL_ATT_KEY_NOT_INITIALIZED = SGX_QL_MK_ERROR(0x000f),        ///< The attestation key doesn't exist or has not been certified.
    SGX_QL_ATT_KEY_CERT_DATA_INVALID = SGX_QL_MK_ERROR(0x0010),      ///< The certification data retrieved from the platform library is invalid.
    SGX_QL_NO_PLATFORM_CERT_DATA = SGX_QL_MK_ERROR(0x0011),          ///< The platform library doesn't have any platfrom cert data.
    SGX_QL_OUT_OF_EPC = SGX_QL_MK_ERROR(0x0012),                     ///< Not enough memory in the EPC to load the enclave.
    SGX_QL_ERROR_REPORT = SGX_QL_MK_ERROR(0x0013),                   ///< There was a problem verifying an SGX REPORT.
    SGX_QL_ENCLAVE_LOST = SGX_QL_MK_ERROR(0x0014),                   ///< Interfacing to the enclave failed due to a power transition.
    SGX_QL_INVALID_REPORT = SGX_QL_MK_ERROR(0x0015),                 ///< Error verifying the application enclave's report.
    SGX_QL_ENCLAVE_LOAD_ERROR = SGX_QL_MK_ERROR(0x0016),             ///< Unable to load the enclaves. Could be due to file I/O error, loading infrastructure error, or non-SGX capable system
    SGX_QL_UNABLE_TO_GENERATE_QE_REPORT = SGX_QL_MK_ERROR(0x0017),   ///< The QE was unable to generate its own report targeting the application enclave either
                                                                     ///< because the QE doesn't support this feature there is an enclave compatibility issue.
                                                                     ///< Please call again with the p_qe_report_info to NULL.
    SGX_QL_KEY_CERTIFCATION_ERROR = SGX_QL_MK_ERROR(0x0018),         ///< Caused when the provider library returns an invalid TCB (too high).
    SGX_QL_NETWORK_ERROR = SGX_QL_MK_ERROR(0x0019),                  ///< Network error when retrieving PCK certs
    SGX_QL_MESSAGE_ERROR = SGX_QL_MK_ERROR(0x001a),                  ///< Message error when retrieving PCK certs
    SGX_QL_NO_QUOTE_COLLATERAL_DATA = SGX_QL_MK_ERROR(0x001b),       ///< The platform does not have the quote verification collateral data available.
    SGX_QL_QUOTE_CERTIFICATION_DATA_UNSUPPORTED = SGX_QL_MK_ERROR(0x001c),
    SGX_QL_QUOTE_FORMAT_UNSUPPORTED = SGX_QL_MK_ERROR(0x001d),
    SGX_QL_UNABLE_TO_GENERATE_REPORT = SGX_QL_MK_ERROR(0x001e),
    SGX_QL_QE_REPORT_INVALID_SIGNATURE = SGX_QL_MK_ERROR(0x001f),
    SGX_QL_QE_REPORT_UNSUPPORTED_FORMAT = SGX_QL_MK_ERROR(0x0020),
    SGX_QL_PCK_CERT_UNSUPPORTED_FORMAT = SGX_QL_MK_ERROR(0x0021),
    SGX_QL_PCK_CERT_CHAIN_ERROR = SGX_QL_MK_ERROR(0x0022),
    SGX_QL_TCBINFO_UNSUPPORTED_FORMAT = SGX_QL_MK_ERROR(0x0023),
    SGX_QL_TCBINFO_MISMATCH = SGX_QL_MK_ERROR(0x0024),
    SGX_QL_QEIDENTITY_UNSUPPORTED_FORMAT = SGX_QL_MK_ERROR(0x0025),
    SGX_QL_QEIDENTITY_MISMATCH = SGX_QL_MK_ERROR(0x0026),
    SGX_QL_TCB_OUT_OF_DATE = SGX_QL_MK_ERROR(0x0027),
    SGX_QL_TCB_OUT_OF_DATE_CONFIGURATION_NEEDED = SGX_QL_MK_ERROR(0x0028),      ///< TCB out of date and Configuration needed
    SGX_QL_SGX_ENCLAVE_IDENTITY_OUT_OF_DATE = SGX_QL_MK_ERROR(0x0029),
    SGX_QL_SGX_ENCLAVE_REPORT_ISVSVN_OUT_OF_DATE = SGX_QL_MK_ERROR(0x002a),
    SGX_QL_QE_IDENTITY_OUT_OF_DATE = SGX_QL_MK_ERROR(0x002b),
    SGX_QL_SGX_TCB_INFO_EXPIRED = SGX_QL_MK_ERROR(0x002c),
    SGX_QL_SGX_PCK_CERT_CHAIN_EXPIRED = SGX_QL_MK_ERROR(0x002d),
    SGX_QL_SGX_CRL_EXPIRED = SGX_QL_MK_ERROR(0x002e),
    SGX_QL_SGX_SIGNING_CERT_CHAIN_EXPIRED = SGX_QL_MK_ERROR(0x002f),
    SGX_QL_SGX_ENCLAVE_IDENTITY_EXPIRED = SGX_QL_MK_ERROR(0x0030),
    SGX_QL_PCK_REVOKED = SGX_QL_MK_ERROR(0x0031),
    SGX_QL_TCB_REVOKED = SGX_QL_MK_ERROR(0x0032),
    SGX_QL_TCB_CONFIGURATION_NEEDED = SGX_QL_MK_ERROR(0x0033),
    SGX_QL_UNABLE_TO_GET_COLLATERAL = SGX_QL_MK_ERROR(0x0034),
    SGX_QL_ERROR_INVALID_PRIVILEGE = SGX_QL_MK_ERROR(0x0035),        ///< No enough privilege to perform the operation
    SGX_QL_NO_QVE_IDENTITY_DATA = SGX_QL_MK_ERROR(0x0037),           ///< The platform does not have the QVE identity data available.
    SGX_QL_CRL_UNSUPPORTED_FORMAT = SGX_QL_MK_ERROR(0x0038),
    SGX_QL_QEIDENTITY_CHAIN_ERROR = SGX_QL_MK_ERROR(0x0039),
    SGX_QL_TCBINFO_CHAIN_ERROR = SGX_QL_MK_ERROR(0x003a),
    SGX_QL_ERROR_QVL_QVE_MISMATCH = SGX_QL_MK_ERROR(0x003b),          ///< QvE returned supplemental data version mismatched between QVL and QvE
    SGX_QL_TCB_SW_HARDENING_NEEDED = SGX_QL_MK_ERROR(0x003c),         ///< TCB up to date but SW Hardening needed
    SGX_QL_TCB_CONFIGURATION_AND_SW_HARDENING_NEEDED = SGX_QL_MK_ERROR(0x003d),        ///< TCB up to date but Configuration and SW Hardening needed

    SGX_QL_UNSUPPORTED_MODE = SGX_QL_MK_ERROR(0x003e),

    SGX_QL_NO_DEVICE = SGX_QL_MK_ERROR(0x003f),
    SGX_QL_SERVICE_UNAVAILABLE = SGX_QL_MK_ERROR(0x0040),
    SGX_QL_NETWORK_FAILURE = SGX_QL_MK_ERROR(0x0041),
    SGX_QL_SERVICE_TIMEOUT = SGX_QL_MK_ERROR(0x0042),
    SGX_QL_ERROR_BUSY = SGX_QL_MK_ERROR(0x0043),

    SGX_QL_UNKNOWN_MESSAGE_RESPONSE  = SGX_QL_MK_ERROR(0x0044),      /// Unexpected error from the cache service
    SGX_QL_PERSISTENT_STORAGE_ERROR  = SGX_QL_MK_ERROR(0x0045),      /// Error storing the retrieved cached data in persistent memory
    SGX_QL_ERROR_MESSAGE_PARSING_ERROR   = SGX_QL_MK_ERROR(0x0046),  /// Message parsing error
    SGX_QL_PLATFORM_UNKNOWN  = SGX_QL_MK_ERROR(0x0047),              /// Platform was not found in the cache
    SGX_QL_UNKNOWN_API_VERSION  = SGX_QL_MK_ERROR(0x0048),           /// The current PCS API version configured is unknown
    SGX_QL_CERTS_UNAVAILABLE  = SGX_QL_MK_ERROR(0x0049),             /// Certificates are not available for this platform

    SGX_QL_QVEIDENTITY_MISMATCH = SGX_QL_MK_ERROR(0x0050),          ///< QvE Identity is NOT match to Intel signed QvE identity
    SGX_QL_QVE_OUT_OF_DATE = SGX_QL_MK_ERROR(0x0051),               ///< QvE ISVSVN is smaller then the ISVSVN threshold
    SGX_QL_PSW_NOT_AVAILABLE = SGX_QL_MK_ERROR(0x0052),             ///< SGX PSW library cannot be loaded, could be due to file I/O error

    SGX_QL_ERROR_MAX = SGX_QL_MK_ERROR(0x00FF),                      ///< Indicate max error to allow better translation.

} quote3_error_t;


#pragma pack(push, 1)
/**  */
typedef struct _sgx_ql_qe3_id_t {
    uint8_t          id[16];  ///< Contains the 16-byte QE_ID
} sgx_ql_qe3_id_t;

/** Used to describe the PCK Cert for a platform */
typedef struct _sgx_ql_pck_cert_id_t
{
    uint8_t *p_qe3_id;                     ///< The QE_ID used to identify the platform for PCK Cert Retrieval
    uint32_t qe3_id_size;                  ///< The Size of hte QE_ID (currenlty 16 bytes)
    sgx_cpu_svn_t *p_platform_cpu_svn;     ///< Pointer to the platform's raw CPUSVN
    sgx_isv_svn_t *p_platform_pce_isv_svn; ///< Pointer to the platform's raw PCE ISVSVN
    uint8_t *p_encrypted_ppid;             ///< Pointer to the enccrypted PPID (Optional)
    uint32_t encrypted_ppid_size;          ///< Size of encrytped PPID.
    uint8_t crypto_suite;                  ///< Crypto algorithm used to encrypt the PPID
    uint16_t pce_id;                       ///< Identifies the PCE-Version used to generate the encrypted PPID.
}sgx_ql_pck_cert_id_t;

/** Contains the valid versions of the sgx_ql_config_t data structure. */
typedef enum _sgx_ql_config_version_t
{
    SGX_QL_CONFIG_VERSION_1 = 1,
}sgx_ql_config_version_t;

/** Contains the certification data used to certify the attestation key and in generating a quote. */
typedef struct _sgx_ql_config_t
{
    sgx_ql_config_version_t version;
    sgx_cpu_svn_t cert_cpu_svn;            ///< The CPUSVN used to generate the PCK Signature used to certify the attestation key.
    sgx_isv_svn_t cert_pce_isv_svn;        ///< The PCE ISVSVN used to generate the PCK Signature used to certify the attestation key.
    uint32_t cert_data_size;               ///< The size of the buffer pointed to by p_cert_data
    uint8_t* p_cert_data;                  ///< The certificaton data used for the quote.
                                           ///todo: It is the assumed to be the PCK Cert Chain.  May want to change to support other cert types.
}sgx_ql_config_t;
#pragma pack(pop)

#ifndef __sgx_ql_qve_collateral_t          // The __sgx_ql_qve_collateral_t can also be defined in QvE _t/_u.h
#define __sgx_ql_qve_collateral_t
typedef struct _sgx_ql_qve_collateral_t
{
    uint32_t version;                      /// version = 1.  PCK Cert chain is in the Quote.
    char *pck_crl_issuer_chain;
    uint32_t pck_crl_issuer_chain_size;
    char *root_ca_crl;                     /// Root CA CRL
    uint32_t root_ca_crl_size;
    char *pck_crl;                         /// PCK Cert CRL
    uint32_t pck_crl_size;
    char *tcb_info_issuer_chain;
    uint32_t tcb_info_issuer_chain_size;
    char *tcb_info;                        /// TCB Info structure
    uint32_t tcb_info_size;
    char *qe_identity_issuer_chain;
    uint32_t qe_identity_issuer_chain_size;
    char *qe_identity;                     /// QE Identity Structure
    uint32_t qe_identity_size;
} sgx_ql_qve_collateral_t;
#endif  //__sgx_ql_qve_collateral_t


#endif //_SGX_QL_LIB_COMMON_H_

