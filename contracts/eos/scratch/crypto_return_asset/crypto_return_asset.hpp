/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/asset.hpp>
#include <eosiolib/currency.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

namespace scoop {
    using namespace eosio;
    using std::string;

    class crypto_return_asset : public contract {
        public :
            crypto_return_asset(account_name self):contract(self) {}

            void create(account_name issuer,
                        asset goal);

            void deposit(account_name investor,
                         asset investment);

            void getalla(account_name owner);

            void getalli(account_name owner);

        private:
            // @abi table assets i64
            struct asset_stats {
                account_name issuer;
                asset goal;
                uint64_t created_date;

                uint64_t primary_key() const {
                    return goal.symbol.name();
                }

                EOSLIB_SERIALIZE(asset_stats, (issuer)(goal)(created_date))
            };

            // @abi table investments i64
            struct investments {
                uint64_t ID;
                account_name investor;
                asset investment;
                uint64_t transaction_date;

                uint64_t primary_key() const {
                    return ID;
                }

                EOSLIB_SERIALIZE(investments, (ID)(investor)(investment)(transaction_date))
            };

            typedef multi_index<N(asset_stats), asset_stats> assetStatsIndex;
            typedef multi_index<N(investments), investments> investmentIndex;
    };
}
