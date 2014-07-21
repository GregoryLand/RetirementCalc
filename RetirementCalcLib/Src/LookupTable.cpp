#include "LookupTable.h"
// Needed Qt items
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
// CalcLibHeaders
#include "Exceptions.h"

namespace RetirementCalc
{
    /*Constructors****************************************************************************/
    // This constructor takes a string to a file on disk to load the lookup table from
    // FileName                    : A string to the Json file
    //
    // Throws                      
    // FileEmpty                   : The file given was blank
    // FileNotFound                : Make sure the file is in the specified directory
    LookupTable::LookupTable( std::string fileName )
    {
        // Get the file from disk
        QScopedPointer<QFile> fileOnDisk( new QFile( fileName.c_str() ) );
        
        // Load the file 
        fileOnDisk->open( QIODevice::ReadOnly | QIODevice::Text );

        // View it as a JSON doc
        QJsonParseError parseError;
        fileAsJson = QJsonDocument::fromJson( fileOnDisk->readAll(), &parseError );
        
        if ( fileAsJson.isNull() )
        {
            throw FileNotFound( "RetirementCalc::LookupTable::Constructor( std::string filename ) = File not Found" );
        }
        if ( fileAsJson.isEmpty() )
        {
            throw FileEmpty( "RetirementCalc::LookupTable::Constructor( std::string filename ) = File empty" );
        }
    }

    /*Destructor******************************************************************************/
    LookupTable::~LookupTable()
    {
    }

    /*Methods*********************************************************************************/
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
    // BadArgument                 : this gets thrown if any of the arguments are out of range
    int LookupTable::Lookup( ProfileType profileType, int currentAge, int startingRetirementFunds, int yearlyRetirementSavings, int desiredRetirementIncome )
    {
        // Error Check this stuff 
        // Basic upper and lower boundary checking 
        if ( currentAge > 50 || currentAge < 25 ) throw RetirementCalc::BadArgument("BadValue:Boundary currentAge");
        if ( startingRetirementFunds <     0 || startingRetirementFunds > 1000000 ) throw RetirementCalc::BadArgument( "BadValue:Boundary startingRetirementFunds" );
        if ( yearlyRetirementSavings <     0 || yearlyRetirementSavings >  100000 ) throw RetirementCalc::BadArgument( "BadValue:Boundary yearlyRetirementSavings" );
        if ( desiredRetirementIncome < 50000 || desiredRetirementIncome >  200000 ) throw RetirementCalc::BadArgument( "BadValue:Boundary desiredRetirementIncome" );

        // make sure values conform to the divisible by 10000 rule
        if ( ( startingRetirementFunds % 10000 ) != 0 ) throw RetirementCalc::BadArgument( "BadValue:NotAMultipleOf10000 startingRetirementFunds" );
        if ( ( yearlyRetirementSavings % 10000 ) != 0 ) throw RetirementCalc::BadArgument( "BadValue:NotAMultipleOf10000 yearlyRetirementSavings" );
        if ( ( desiredRetirementIncome % 10000 ) != 0 ) throw RetirementCalc::BadArgument( "BadValue:NotAMultipleOf10000 desiredRetirementIncome" );

        // Do the deed
        switch ( profileType )
        {
            case RetirementCalc::LookupTable::ProfileType::Cash:
                return this->fileAsJson.object()["cash"].toObject()[QString::number(currentAge)]
                                                        .toObject()[QString::number(startingRetirementFunds)]
                                                        .toObject()[QString::number(yearlyRetirementSavings)]
                                                        .toObject()[QString::number(desiredRetirementIncome)].toInt();

            case RetirementCalc::LookupTable::ProfileType::Future_Advisor:
                return this->fileAsJson.object()["future_advisor"].toObject()[QString::number( currentAge )]
                                                                  .toObject()[QString::number( startingRetirementFunds )]
                                                                  .toObject()[QString::number( yearlyRetirementSavings )]
                                                                  .toObject()[QString::number( desiredRetirementIncome )].toInt();
            default:
                return 0;
        }
        return 0;
    }
}