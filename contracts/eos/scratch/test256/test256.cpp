#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;

class[[eosio::contract]] test256  : public contract
{
  struct hasher_rec;

  public:
    using contract::contract;

    test256(name self, name code, datastream<const char *> ds)  : contract(self, code, ds), _hasher(_self,_self.value) {}

    [[eosio::action]] 
     void addhash(const hasher_rec &rec) {
       _hasher.emplace(_self, [&](auto &&r) { 
           r = rec;
       });
    }
 
 private: 

    struct [[eosio::table]] hasher_rec {
        uint64_t id;
        name owner;
        checksum256 hash;
        checksum256 tx;

        uint64_t primary_key() const { return id; }

        key256 by_hash() const { return checksum256_to_sha256(hash); }

        static key256 checksum256_to_sha256(const checksum256 &hash)
        {
            const uint128_t *p128 = reinterpret_cast<const uint128_t *>(&hash);
            //return key256::make_from_word_sequence<uint64_t>(p64[0], p64[1], p64[2], p64[3]);
            key256 k;
            k.data()[0] = p128[0];
            k.data()[1] = p128[1];
            return k;
        }

        // EOSLIB_SERIALIZE(hasher_rec, (id)(owner)(hash)(tx))
    };

    typedef multi_index<"hasher"_n, hasher_rec,
        indexed_by<"hash"_n, const_mem_fun<hasher_rec, key256, &hasher_rec::by_hash>>
        > hasher_table_type;

    hasher_table_type _hasher;
};

EOSIO_DISPATCH(test256, (addhash))