#include "crypto_return_asset.hpp"

namespace scoop {

// @abi action
void crypto_return_asset::create(account_name issuer, asset goal) {
    require_auth( _self );

    auto symbol = goal.symbol;
    eosio_assert(symbol.is_valid(), "Invalid symbol name");

    assetStatsIndex assetList(_self, _self);
    
    auto iterator = assetList.find(goal.symbol.name());
    eosio_assert(iterator == assetList.end(), "PK already exists.");
    
    assetList.emplace(_self, [&](auto& a) {
        a.goal = goal;
        a.issuer = issuer;
        a.created_date = current_time();
    });
}

// @abi action
void crypto_return_asset::deposit(account_name investor, asset investment) {
    require_auth( _self );
    
    eosio_assert(investment.is_valid(), "Invalid investment");
    
    investmentIndex investmentList(_self, _self);

    print("ID: ", investmentList.available_primary_key());
    investmentList.emplace(_self, [&](auto& t) {
        t.ID = investmentList.available_primary_key();
        t.investor = investor;
        t.investment = investment;
        t.transaction_date = current_time();
    });
}

// @abi action
void crypto_return_asset::getalla(account_name owner) {
    require_auth( _self );

    assetStatsIndex assetList(_self, _self);

    auto iterator = assetList.begin();

    while(iterator != assetList.end()) {
        auto asset = *iterator;
        
        print("Goal: ");
        asset.goal.print();
        print( " Account: ", asset.issuer);
        print("--Time: ", asset.created_date);

        iterator++;
    }
}

// @abi action
void crypto_return_asset::getalli(account_name owner) {
    require_auth( _self );

    investmentIndex investmentList(_self, _self);

    auto iterator = investmentList.begin();

    while(iterator != investmentList.end()) {
        auto transaction = *iterator;
        
        print(" ID: ", transaction.ID);
        print("Investment: ");
        transaction.investment.print();
        print(" Account: ", transaction.investor, " Time: ", transaction.transaction_date);

        iterator++;
    }
}

EOSIO_ABI(crypto_return_asset, (create)(deposit)(getalla)(getalli))

}
