
#ifndef StateFunctions_hpp
#define StateFunctions_hpp

/*
 * Data container that hold pointers to a state's enter and update functions
 * and allows the function pointers to be called
 */
template <typename T>
struct StateFunctions
{
	typedef void (T::* StateFunction)( void );
	
	StateFunctions( StateFunction enterFunc, StateFunction updateFunc )
	: m_enterFunc( enterFunc )
	, m_updateFunc( updateFunc )
	{
		// Not much here
	}
	
	void enter( T* const pT ) const
	{
		(pT->*m_enterFunc)();
	}
	
	void update( T* const pT ) const
	{
		(pT->*m_updateFunc)();
	}
	
private:
	StateFunction m_enterFunc;
	StateFunction m_updateFunc;
};

#endif /* StateFunctions_hpp */
