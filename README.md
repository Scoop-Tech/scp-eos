# SCP-EOS

## SCPX Contract (Status: RC1)

[scpx contract](contracts/eos/scpx/scpx.cpp) runs on a public EOS chain instance maintained by [Scoop-Tech](https://github.com/Scoop-Tech) (https://eos.scoop.tech:4242/v1/chain/get_info). Note that this is not the EOS mainnet: we have a strong requirement to support completely free account creation, which EOS mainnet does not support. Hence the decision to run on a separate chain instance.

The contract is a pass-through wrapper providing a data-storage interface for an authorized publisher (currently only [scpx-web-svr](https://github.com/Scoop-Tech/scp-web-svr)) to write and remove rows, and to update existing rows in an [EOS Multi Index Table](https://developers.eos.io/eosio-cpp/docs/using-multi-index-tables) for the [Scoop Wallet](https://github.com/Scoop-Tech/scpx-app) ("SCP").

With the exception of the primary and secondary keys (```owner``` and ```h_email_ui128```) The contract is agnostic to the values that are stored in the table.

## Security

All contact methods may only be invoked by the contract publisher (Scoop-Tech).

## Encryption

See XXXXXXXXX for details on SCP's encryption model.

### Table Fields

- ```owner``` EOS account name of the SCP user associated with the row (primary key, datatype: name).
- ```e_email``` encrypted email address of the SCP user associated with the row (datatype: std::string)
- ```h_email_ui128``` hash of the encrypted email address of the SCP user associated with the row (secondary key, datatype: uint128_t).
- ```created_at``` timestamp of row creation (datatype: time_point_sec).
- ```assets_json``` encrypted asset data (datatype: std::string).
- ```data_json``` encrypted app data (datatype: std::string).
- ```ex1``` reserved for future use (datatype: std::string).
- ```ex2``` reserved for future use (datatype: std::string).

### Contact Methods

- ```newuser``` creates a user row for the specified SCP EOS chain account name, email and email hash.
- ```deleteuser``` deletes a user row for the specified SCP EOS chain account name.
- ```setassets``` sets user asset data for the specified SCP EOS chain account name.
- ```setdata``` sets user app data for the specified SCP EOS chain account name.


