#ifndef ENEMYFORMATION_H
#define ENEMYFORMATION_H

#include "Settings.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: EnemyFormation
// Classes Inherited	: None
// Purpose				: To load the first wave form a csv file and generate random waves after
//-------------------------------------------------------------------------------------------------------------------------
class EnemyFormation
{
private:
#pragma region private variables
	bool	m_hasFirstWaveInitiated; // To check if the first wave has been initiated

	int		m_formationSize; // The size of the enemy formation 
	int		m_enemyFormation[ Settings::EnemyProperties::c_formationHeight ][ Settings::EnemyProperties::c_formationWidth ]; // The 2d Array of how formations will be stored

#pragma endregion
public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: EnemyFormation()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	EnemyFormation();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: EnemyFormation()
	// Parameters		: None
	// Notes			: This destructor will delete nothing as nothing has been created
	//---------------------------------------------------------------------------------------------------------------------
	~EnemyFormation();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: initialiseNewFormation()
	// Parameters		: None
	// Purpose			: To initialise the first wave or radomly generate one after each wave has been completed
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialiseNewFormation( );

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setHasFirstWaveInitiated(bool hasFirstWaveInitiated)
	// Parameters		: hasFirstWaveInitiated - set that the first wave has been initiated
	// Purpose			: This will mainly set this boolean to false, when the game has finished, or the player dies so 
	//					,	every new the game, it will load this formation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setHasFirstWaveInitiated( bool hasFirstWaveInitiated );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getFormationSize()
	// Parameters		: None
	// Purpose			: This will get the size of the formation
	// Returns			: The size of the formation
	//---------------------------------------------------------------------------------------------------------------------
	const int getFormationSize() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getEnemyFormationElement(int formationRow , int formationColumn)
	// Parameters		: formaitonRow - the index of the formaiton Row
	//					, formationColumn - the index of the formation column
	// Purpose			: This will get the value of the 2d array using the indexes that are passed through
	// Returns			: The value of the 2d array index
	//---------------------------------------------------------------------------------------------------------------------
	int getEnemyFormationElement( int formationRow , int formationColumn );

#pragma endregion
};

#endif // !ENEMYFORMATION_H
