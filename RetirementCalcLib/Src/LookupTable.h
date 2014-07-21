#pragma once

// LoreiLib Main Header
#include <string>
#include <exception>
#include <QJsonDocument>

namespace RetirementCalc
{
    // Class containing a lookup table in the provided Json object file
    class LookupTable
    {
        /*Enums***********************************************************************************/
        public:
            // Enum used to specify which tables are available
            enum class ProfileType { Cash, Future_Advisor };

        /*Constructors****************************************************************************/
        public:
            // This constructor takes a string to a file on disk to load the lookup table from
            // FileName                    : A std::string to the Json file
            //
            // Throws                      
            // FileEmpty                   : The file given was blank
            // FileNotFound                : Make sure the file is in the specified directory
            LookupTable( std::string fileName );

        /*Destructor******************************************************************************/
        public:
            ~LookupTable();

        /*Methods*********************************************************************************/
        public:
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
            int Lookup( ProfileType profileType, int currentAge, int startingRetirementFunds, int yearlyRetirementSavings, int desiredRetirementIncome );

        /*Data************************************************************************************/
        private:
            QJsonDocument fileAsJson;
	};
}