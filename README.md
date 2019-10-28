# Scoop Data Storage Contract (DSC)
Release Candidate 5

## Overview

EOS CPP contract for the [Scoop Wallet](https://github.com/Scoop-Tech/scpx-app).

[scpx contract](contracts/eos/scpx/scpx.cpp) runs on a public EOS chain instance maintained by [Scoop-Tech](https://github.com/Scoop-Tech) (https://eos.scoop.tech:4242/v1/chain/get_info). Note that this is not EOS mainnet: we have a strong requirement to support completely free account creation, which EOS mainnet does not facilitate. 

The contract is a pass-through wrapper for EOS table operations and acts as as data storage layer for any authorized publisher (currently only [scpx-web-svr](https://github.com/Scoop-Tech/scpx-svr)) to write, remove and update rows in an [EOS Multi Index Table](https://developers.eos.io/eosio-cpp/docs/using-multi-index-tables). 

With the exception of the primary and secondary keys (```owner``` and ```h_email_ui128```) the contract is agnostic to the values that are stored in the table.

## Security

All contact methods may only be invoked by the contract publisher (Scoop-Tech).

## Encryption

See [Scoop Security](https://github.com/Scoop-Tech/scpx-svr/blob/master/sec.md) for details on SCPX's security and encryption model.

### Table Fields

Field               | Datatype        | Key       | Usage
---                 | ----            | ---       | ---
```owner```         | name            | Primary   | EOS account name of the user associated with the row
```e_email```       | std::string     |           | encrypted email address of the user associated with the row
```h_email_ui128``` | uint128_t       | Secondary | 128-bit hash of the encrypted email address of the user associated with the row
```created_at```    | time_point_sec  |           | timestamp of row creation
```assets_json```   | std::string     |           | encrypted user asset data
```data_json```     | std::string     |           | encrypted user app data (settings)
```ex1```           | std::string     |           | reserved for future use
```ex2```           | std::string     |           | reserved for future use

### Contract Methods

* ```void newuser(const name scp_account, const std::string e_email, const uint128_t e_hash_hex128)```

  Creates a user row for the specified SCPX EOS chain account name, email and email hash.

* ```void deleteuser(const name scp_account)```

  Deletes a user row for the specified SCPX EOS chain account name.

* ```void setassets(const name scp_account, std::string assets_json)```

  Sets user asset data for the specified SCPX EOS chain account name.

* ```void setdata(const name scp_account, std::string data_json)```

  Sets user app data for the specified SCPX EOS chain account name.

### Building from Source

The contract is built with [EOSIO.CDT 1.5.0](https://github.com/EOSIO/eosio.cdt).





