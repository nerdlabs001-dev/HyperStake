// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "db.h"
#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (      0, hashGenesisBlockOfficial )
        (     10, uint256("0x0000074074af28e73189ae5767b706246be2e0827c46d97a61178394aec877cf"))
        (    100, uint256("0x000000115d6f47d1a7489756f379ca9cc1e827ddb086e1d5a77ef9067e8f567b"))
        (   1000, uint256("0x00000000009a77d895a12394d2fc903cea7d3ff1f9c4b4f41c5fb0e4d3c360be"))
        (  10000, uint256("0x139b78a18db9b711f9b90e68073614cba405f59f4a1e5746e2cac520bffa0632"))
        (  25000, uint256("0x3756290bd4724946e831a401075d4fdecf6ab44a656ec94b916679ce95a2e7eb"))
        (  31781, uint256("0x42265210870957b8d37f91a0834c6cda65949b2ca805bb3a7d527a4cd585a090")) //official hyp fork
        (  50000, uint256("0x3756290bd4724946e831a401075d4fdecf6ab44a656ec94b916679ce95a2e7eb"))
        (  80987, uint256("0x6b943fa756e915ddd8b654844781e21090ae9ddfcb2147fba46cac529df5be08")) //not using even number because sync gets sticky
        ( 100000, uint256("0x36092e430f255533638625cbf97cb21c0fbc872f5f2ad372280b066a941d084a"))
        ( 150000, uint256("0xe1b77d01cc57d25e8c442db52ff55b44b1dc792016606ab721c943f8e5b220cd"))
        ( 199999, uint256("0x084b314dfee7db9d311a5db4dc4b8880df36eb7e9bb90ec98dd0bab5af2a7df2"))
        ( 235691, uint256("0xf0f71ea7edf7457e611ee893cdbb6ff19499713f4dae935d6d21e073d96a7dc3"))
        ( 235999, uint256("0xafe60dd0ab56ef529db21ea648ea4fd8de758a11b6a8ac1fa5cd2d4959162106"))
        ( 300000, uint256("0xf7e5bac8e9be5b4e260c98b88542b9d7ec3c379261a90b39f21c37f803e31588"))
        ( 399999, uint256("0x875356232916a420c100b83d87cc9ce3eb9a174750b48d2fd1eefba7292163b5"))
        ( 499999, uint256("0x8e370d8ab8bdb6e6a5a4882dda755b23b5f284f633e04c12e6f73f92de15e68e"))
        ( 600000, uint256("0x47b840003efd1aed727e381cb7787370f760dc864557d98f5ab919d4f7aea5e0"))
        ( 700000, uint256("0xed4e04afe69c739fce0aefac3ada705810d46551b1b136f76472cc9549b5e0b1"))
        ( 800000, uint256("0x4d3fb2e0ed7b352508f8a237488ae742b307c624f716ee804119a7e168f9efbc"))
        ( 900000, uint256("0x68b082b2e9555f4b5112254b77317f9e49a980cde01884831241d390c362d0aa"))
        (1000000, uint256("0xc18a6fb2b9f505a6e046f66e21d2c0aa9210c2ac909f6589a8536012dcd4dfa4"))
        (1100000, uint256("0x72c42408154a70daeebdc39b5934d6489fca117be8850ec229e19cade46628d7"))
        (1207950, uint256("0xbad0a0f14081129f34d42fdc617638756158fd7b1413f4d3a2916bed2c1a61d4"))
        (1377570, uint256("0x3d76cad9c096ce48336da1528ab31b5897eac41b8780fb37f64110ca034f971c"))
	;

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
		(70, uint256("0x97c81df9aab50f1bef2e09ec8d806c3cc7ec6b7b7f13c70f1b854d8e40ed77c9"))
        ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
