#include <boost/test/unit_test.hpp>
#include "LookupTable.h"
#include "Exceptions.h"
#include <exception>
// Feel free to copy and paste this code to create your own test modules
// Change the BOOST_AUTO_TEST_SUITE and BOOST_AUTO_TEST_CASE arguments to do so

//KeepAtStartOfTestSection//////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE( LookupTable_test );
///////////////////////////////////////////////////////////////////////////////////////////KeepAtStartOfTestSection

/*Constructor tests**********************************************************************************************/
BOOST_AUTO_TEST_CASE( LookupTable_constructor_test )
{
    BOOST_REQUIRE_NO_THROW( RetirementCalc::LookupTable testLoad( "TestData\\retirement-data.json" ) );
}

BOOST_AUTO_TEST_CASE( LookupTable_constructor_failed_to_find_file )
{
    BOOST_REQUIRE_THROW( RetirementCalc::LookupTable testLoad( "" ), RetirementCalc::FileNotFound );
}

/*Lookup method tests**********************************************************************************************/
// int LookupTable::Lookup( ProfileType profileType, int currentAge, int startingRetirementFunds, int yearlyRetirementSavings, int desiredRetirementIncome )
// This method returns the retirement age specified in the lookup table provided
// profileType                 : Valid values ProfileType: arguments | cash 
// currentAge                  : Valid values int |     25 to        50 inclusive
// startingRetirementFunds     : Valid values int |      0 to 1,000,000 inclusive where divisible by 10000
// yearlyRetirementSavings     : Valid values int |      0 to   100,000 inclusive where divisible by 10000
// desiredRetirementIncome     : Valid values int | 50,000 to   200,000 inclusive where divisible by 10000
//
// Returns int                 : 25 - 89 inclusive indicating age to retire at the desired income
//                             : return value of 89 may indicate a capped out value in the lookup table
// 
// Throws                      
// BadArgumentRamge            : this gets thrown if any of the arguments are out of range
BOOST_AUTO_TEST_CASE( LookupTable_Lookup_method_arg_error_test )
{
    // Some helpful constants 
    const int ERROR_RETURNED = 0;
    
    // Good values
    const RetirementCalc::LookupTable::ProfileType CASH = RetirementCalc::LookupTable::ProfileType::Cash;
    const int GOOD_STARTING_AGE              = 30;
    const int GOOD_STARTING_RETIREMENT_FUNDS = 10000;
    const int GOOD_YEARLY_RETIREMENT_SAVINGS = 10000;
    const int GOOD_DESIRED_RETIREMENT_INCOME = 50000;

    RetirementCalc::LookupTable testLoad( "TestData\\retirement-data.json" );

    // CurrentAge
    // currentAge                  : Valid values int |     25 to        50 inclusive
    // Check to see if it works correctly for good values
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH,                25, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH,                50, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    // Check to make sure we are handling corner cases correctly
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, 24, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, 51, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );


    // StartingRetirementFunds
    // startingRetirementFunds     : Valid values int |      0 to 1,000,000 inclusive where divisible by 10000
    // Check to see if it works correctly for good values
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE,                              0, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE,                        1000000, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    // Check to make sure we are handling corner cases correctly
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE,      -1, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, 1000001, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE,  999999, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );


    // YearlyRetirementSavings
    // yearlyRetirementSavings     : Valid values int |      0 to   100,000 inclusive where divisible by 10000
    // Check to see if it works correctly for good values
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS,                              0, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS,                         100000, GOOD_DESIRED_RETIREMENT_INCOME ) );

    // Check to make sure we are handling corner cases correctly
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_YEARLY_RETIREMENT_SAVINGS,     -1, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_YEARLY_RETIREMENT_SAVINGS,   5000, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_YEARLY_RETIREMENT_SAVINGS, 100001, GOOD_DESIRED_RETIREMENT_INCOME ), RetirementCalc::BadArgument );


    // desiredRetirementIncome
    // desiredRetirementIncome     : Valid values int | 50,000 to   200,000 inclusive where divisible by 10000
    // Check to see if it works correctly for good values
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS,                          50000 ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, GOOD_DESIRED_RETIREMENT_INCOME ) );
    BOOST_CHECK( ERROR_RETURNED < testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS,                         200000 ) );

    // Check to make sure we are handling corner cases correctly
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS,  49999 ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS,  50001 ), RetirementCalc::BadArgument );
    BOOST_REQUIRE_THROW( testLoad.Lookup( CASH, GOOD_STARTING_AGE, GOOD_STARTING_RETIREMENT_FUNDS, GOOD_YEARLY_RETIREMENT_SAVINGS, 200001 ), RetirementCalc::BadArgument );
}

//KeepAtEndOfFile//////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE_END();
////////////////////////////////////////////////////////////////////////////////////////////////////KeepAtEndOfFile
