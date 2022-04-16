#include <fstream>
#include <iostream>
#include <sstream>

#include "EnemyBase.h"
#include "EnemyFormation.h"

EnemyFormation::EnemyFormation()
// Setting these variables before the constructor gets called
	: m_hasFirstWaveInitiated	( false )
	, m_formationSize			( Settings::EnemyProperties::c_formationWidth * Settings::EnemyProperties::c_formationHeight )
{
	// Initialise the enemy formation, which sets all values to 0
	for ( int formationRow = 0; formationRow < Settings::EnemyProperties::c_formationHeight; ++formationRow )
	{
		for ( int formationColumn = 0; formationColumn < Settings::EnemyProperties::c_formationWidth; ++formationColumn )
		{
			m_enemyFormation[ formationRow ][ formationColumn ] = 0;
		}
	}
}

EnemyFormation::~EnemyFormation()
{
}

void EnemyFormation::initialiseNewFormation( )
{
	// Create an int to randmose and set to the formation
	int enemyType = 0;

	// Check if the first wave was already initiated
	if ( m_hasFirstWaveInitiated == true )
	{
		// Loop through formaiton rows
		for ( int formationRow = 0; formationRow < Settings::EnemyProperties::c_formationHeight; ++formationRow )
		{
			// Loop through formation height
			for ( int formationColumn = 0; formationColumn < Settings::EnemyProperties::c_formationWidth; ++formationColumn )
			{
				// Randomise using max amount of enemy types. There is 4, so the third enemy can be accessed and have 0 as a space
				enemyType = rand() % Settings::EnemyProperties::c_maxAmountOfEnemyTypes;

				// Set that randomised value into the 2d array
  				m_enemyFormation[ formationRow ][ formationColumn ] = enemyType;
			}
		}
	}
	else
	{
		// Set the file name string
		std::string fileName = "csvFiles/wave1_formation1.csv";

		// Store the file in an ifstream variable and open it
		std::ifstream mapFile( fileName );

		// Loop through the row of the file first
		for ( int formationRow = 0; formationRow < Settings::EnemyProperties::c_formationHeight; ++formationRow )
		{
			// Create a string variable that will get the first row of the csv file using the getline function
			std::string fileRow;
			std::getline( mapFile , fileRow );

			// Create an instance of the file row by creating a string stream and store it there
			std::stringstream stringStreamMapRow( fileRow );

			// Loop through the whole column to start adding values to the formation
			for ( int formationColumn = 0; formationColumn < Settings::EnemyProperties::c_formationWidth; ++formationColumn )
			{

				std::string formationElement; // Create another string variable that will store each element of the csv file
				std::getline( stringStreamMapRow , formationElement , ',' ); // Split the row with a ',' and store it in formationElement

				// Create an instance of the element, which will add it to the 2d array
				std::stringstream converter( formationElement );
				converter >> m_enemyFormation[ formationRow ][ formationColumn ];
			}
		}

		// After the loop has finished, the first wave has initialised, which won't be reloaded until the game is reset
		m_hasFirstWaveInitiated = true;
	}
}

void EnemyFormation::setHasFirstWaveInitiated( bool hasFirstWaveInitiated )				{ m_hasFirstWaveInitiated = hasFirstWaveInitiated; }

const int EnemyFormation::getFormationSize() const										{ return m_formationSize; }

int EnemyFormation::getEnemyFormationElement( int formationRow , int formationColumn )	{ return m_enemyFormation[formationRow][formationColumn]; }
