#include <list>

class Character
{
public:
	Character() {};
	~Character() {};
	void Name( const char* name ) { m_Name = name; }
	std::string getName() { return m_Name; }
	int getLength() { return m_Name.length(); }

private:
	std::string m_Name;
};

void CharacterSortByName()
{
	std::list<Character> charList;

	Character agebreak;
	agebreak.Name( "agebreak" );
	charList.push_back( agebreak );

	Character sm9;
	sm9.Name( "sm9" );
	charList.push_back( sm9 );
		
	Character miku;
	miku.Name( "miku" );
	charList.push_back( miku );

	Character sm1;
	sm1.Name( "sm1" );
	charList.push_back( sm1 );

	charList.sort([](Character& first, Character& second) ->bool {
		return ( first.getName() < second.getName() );
	} );

	for each( Character elem in charList )
	{
		printf( "%s \n", elem.getName().c_str() );
	}
}

void main()
{
	CharacterSortByName();

	getchar();
}