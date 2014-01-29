#include<iostream>
#include<fstream>
#include<streambuf>
#include<locale>

#include "./WideChar.h"

// namespace std {
//     wostream& operator<<( wostream& os, const wchar_t* str ) {
//  	while( *str ) {
//  	    os.put( *str );
//  	    ++str;
//  	}
//  	return os;
//     }
// }

class MyFacet : public std::codecvt<wchar_t, char, mbstate_t> {
 public:
    MyFacet() {
	std::cout<<"Facet constructor"<<std::endl;
    }
    virtual result do_in(state_type& __state, const extern_type* __from,
			 const extern_type* __from_end, const extern_type*& __from_next,
			 intern_type* __to, intern_type* __to_end,
			 intern_type*& __to_next) const {
	std::cout<<"Hi, I'm the facet"<<std::endl;
	return codecvt_base::error;
    }

    virtual result
	do_out(state_type& __state, const intern_type* __from,
	       const intern_type* __from_end, const intern_type*& __from_next,
	       extern_type* __to, extern_type* __to_end,
	       extern_type*& __to_next) const {
	
	//std::wcout<<L"Hi, I'm the facet"<<std::endl;
	
	std::ofstream outStream( "hi.txt" );
	outStream<<"Hi, I'm the facet"<<std::endl;
	outStream.close();
	return codecvt_base::error;
    }

    virtual result do_unshift(state_type& __state, extern_type* __to,
			      extern_type* __to_end, extern_type*& __to_next) const {
	std::cout<<"Hi, I'm the facet"<<std::endl;
    }


    virtual int do_encoding() const throw() {
	std::cout<<"Hi, I'm the facet"<<std::endl;
	return 43;
    }

    virtual bool do_always_noconv() const throw() {
	std::cout<<"Hi, I'm the facet"<<std::endl;
	return true;
    }

    virtual int do_length(state_type&, const extern_type* __from,
			  const extern_type* __end, size_t __max) const {
	std::cout<<"Hi, I'm the facet"<<std::endl;
	return 42;
    }

    virtual int do_max_length() const throw() {
	std::cout<<"Hi, I'm the facet: do_max_length"<<std::endl;
	return 42;
    }
    
};

int main() {

    std::locale myLocale( std::locale(), new MyFacet() );
    

//     std::ofstream outStream( "test.txt" );

//     if( std::has_facet< std::codecvt<wchar_t, char, mbstate_t> >( outStream.getloc() ) ) {
// 	std::cout<<"hat eins"<<std::endl;
// 	std::cout<< std::use_facet< std::codecvt<wchar_t, char, mbstate_t> >( outStream.getloc() ).max_length() << std::endl;
//     }

//     outStream.imbue( myLocale );
    

//     if( std::has_facet< std::codecvt<wchar_t, char, mbstate_t> >( std::wcout.getloc() ) ) {
// 	std::wcout<<"jetzt hat er eins"<<std::endl;
// 	std::wcout<< std::use_facet< std::codecvt<wchar_t, char, mbstate_t> >( outStream.getloc() ).max_length() << std::endl;
//     }

    std::filebuf strBuf;
    strBuf.pubimbue( myLocale );
    strBuf.open( "test.txt", std::ios::out );
    strBuf.sputc( L'c' );

    return 0;
    

}
