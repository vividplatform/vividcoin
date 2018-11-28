// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2016-2017 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_TXDB_H
#define BITCOIN_TXDB_H

#include "leveldbwrapper.h"
#include "main.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

// This was determined by summing the balances of the following blacklisted addresses:
// - VLNrmju9o4FXAidZR6kCpbT9YNcFUdSx4r 2600000000000
// - VMUMdG2Tg49TfYMP3nzAtX8DqCeET6rafP 2300000000000
// - VYZusH9N2b898ynCmRSA4YYebgfRBGBgSX 1004000000000
// - VW3c4i7qnDxBfJJzix9VCzcmbkRGv5PtWh 571903421840
// - VJeqfzc3YHqkYmDDf7Pyek5RAzrXAkPKui 3000000000
// - VHZ1ivYRyAKijd5odyLSBMhHJrSB4df6AA 25025929500000
#define BLACKLISTED_SUPPLY 31504832921840

// Specifices the block from what point onward we subtract the blacklisted supply.
// This block wasn't first, but was the first to introduce a spoof above 20k.
// Hash: 7d7f9da087eefac4d5434356b4a5c3536b0f61217096b07445c18d9ea60066b0
#define SUPPLY_FIX_HEIGHT 219958

class CCoins;
class uint256;

//! -dbcache default (MiB)
static const int64_t nDefaultDbCache = 100;
//! max. -dbcache in (MiB)
static const int64_t nMaxDbCache = sizeof(void*) > 4 ? 4096 : 1024;
//! min. -dbcache in (MiB)
static const int64_t nMinDbCache = 4;

/** CCoinsView backed by the LevelDB coin database (chainstate/) */
class CCoinsViewDB : public CCoinsView
{
protected:
    CLevelDBWrapper db;

public:
    CCoinsViewDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

    bool GetCoins(const uint256& txid, CCoins& coins) const;
    bool HaveCoins(const uint256& txid) const;
    uint256 GetBestBlock() const;
    bool BatchWrite(CCoinsMap& mapCoins, const uint256& hashBlock);
    bool GetStats(CCoinsStats& stats) const;
};

/** Access to the block database (blocks/index/) */
class CBlockTreeDB : public CLevelDBWrapper
{
public:
    CBlockTreeDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

private:
    CBlockTreeDB(const CBlockTreeDB&);
    void operator=(const CBlockTreeDB&);

public:
    bool WriteBlockIndex(const CDiskBlockIndex& blockindex);
    bool ReadBlockFileInfo(int nFile, CBlockFileInfo& fileinfo);
    bool WriteBlockFileInfo(int nFile, const CBlockFileInfo& fileinfo);
    bool ReadLastBlockFile(int& nFile);
    bool WriteLastBlockFile(int nFile);
    bool WriteReindexing(bool fReindex);
    bool ReadReindexing(bool& fReindex);
    bool ReadTxIndex(const uint256& txid, CDiskTxPos& pos);
    bool WriteTxIndex(const std::vector<std::pair<uint256, CDiskTxPos> >& list);
    bool WriteFlag(const std::string& name, bool fValue);
    bool ReadFlag(const std::string& name, bool& fValue);
    bool WriteInt(const std::string& name, int nValue);
    bool ReadInt(const std::string& name, int& nValue);
    bool LoadBlockIndexGuts();
};

#endif // BITCOIN_TXDB_H
