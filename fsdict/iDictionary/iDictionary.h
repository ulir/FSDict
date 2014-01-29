#ifndef FSDICT_IDICTIONARY_H
#define FSDICT_IDICTIONARY_H FSDICT_IDICTIONARY_H

namespace fsdict {

    template< typename AnnType >
    class iDictionary {
    public:
	virtual ~iDictionary() {}
	virtual bool lookup( wchar_t const* str, AnnType* annotation = 0 ) const = 0;
	virtual bool lookup( std::wstring const& str, AnnType* annotation = 0 ) const = 0;
	
    }; // class iDictionary
    
} // namespace fsdict

#endif
