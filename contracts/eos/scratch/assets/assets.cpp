#include "Assets.hpp"

namespace CryptoReturnAssets {
    using namespace eosio;
    using std::string;

    class Assets : public contract {
        using contract:: contract;

        public: 
            Assets(account_name self):contract(self) {}

            // @abi action
            void create(const account_name account, string& assetName, uint64_t goal) {
                /**
                 * We require that only the owner of an account can use this action
                 * or somebody with the account authorization
                 */
                require_auth(account);

                assetIndex assets(_self, _self);

                auto iterator = assets.find(account);
                eosio_assert(iterator == assets.end(), "Asset already exists.");

                assets.emplace(account, [&](auto& asset) {
                    asset.account_name = account;
                    asset.assetName = assetName;
                    asset.goal = goal;
                });
            }

            // @abi action
            void getasset(const account_name account) {
                assetIndex assets(_self, _self);

                auto iterator = assets.find(account);
                eosio_assert(iterator != assets.end(), "Asset for account not found");

                auto currentAsset = assets.get(account);
                print("Asset name: ", currentAsset.assetName.c_str(), " goal: ", currentAsset.goal);
            }

        private:

            //@abi table asset i64
            struct cryptoAsset {
                uint64_t account_name;
                string assetName;
                uint64_t goal;

                uint64_t primary_key() const {
                    return account_name;
                }

                EOSLIB_SERIALIZE(cryptoAsset, (account_name)(assetName)(goal));
            };

            typedef multi_index<N(cryptoAsset), cryptoAsset> assetIndex;
    };

    EOSIO_ABI(Assets, (create)(getasset))
}