# SCP-EOS (rc0)

## SCPX Data Storage Contract

EOS CPP contract for the [Scoop Wallet](https://github.com/Scoop-Tech/scpx-app) (**"Scoop Client"**).

[scpx contract](contracts/eos/scpx/scpx.cpp) runs on a public EOS chain instance maintained by [Scoop-Tech](https://github.com/Scoop-Tech) (https://eos.scoop.tech:4242/v1/chain/get_info). Note that this is not EOS mainnet: we have a strong requirement to support completely free account creation, which EOS mainnet does not facilitate. 

The contract is a pass-through wrapper for EOS table operations and acts as as data storage layer for any authorized publisher (currently only [scpx-web-svr](https://github.com/Scoop-Tech/scpx-svr)) to write, remove and update rows in an [EOS Multi Index Table](https://developers.eos.io/eosio-cpp/docs/using-multi-index-tables). 

With the exception of the primary and secondary keys (```owner``` and ```h_email_ui128```) the contract is agnostic to the values that are stored in the table.

## Security

All contact methods may only be invoked by the contract publisher (Scoop-Tech).

## Encryption

See [Scoop Security](https://github.com/Scoop-Tech/scpx-svr/blob/master/sec.md) for details on SCPX's security and encryption model.

### Table Fields

* ```owner``` - EOS account name of the user associated with the row (primary key, datatype: name).
* ```e_email``` - encrypted email address of the user associated with the row (datatype: std::string)
* ```h_email_ui128``` - 128-bit hash of the encrypted email address of the user associated with the row (secondary key, datatype: uint128_t).
* ```created_at``` - timestamp of row creation (datatype: time_point_sec).
* ```assets_json``` - encrypted user asset data (datatype: std::string).
* ```data_json``` - encrypted user app data (datatype: std::string).
* ```ex1``` - reserved for future use (datatype: std::string).
* ```ex2``` - reserved for future use (datatype: std::string).

### Contract Methods

* ```newuser``` - creates a user row for the specified SCPX EOS chain account name, email and email hash.
  ```void newuser(const name scp_account, const std::string e_email, const uint128_t e_hash_hex128)```

* ```deleteuser``` - deletes a user row for the specified SCPX EOS chain account name.
  ```void deleteuser(const name scp_account)```

* ```setassets``` - sets user asset data for the specified SCPX EOS chain account name.
  ```void setassets(const name scp_account, std::string assets_json)```

* ```setdata``` - sets user app data for the specified SCPX EOS chain account name.
  ```void setdata(const name scp_account, std::string data_json)```

### Building from Source

The contract is built with [EOSIO.CDT 1.5.0](https://github.com/EOSIO/eosio.cdt).

...



