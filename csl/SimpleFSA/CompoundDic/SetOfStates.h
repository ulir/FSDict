

class JoinState : public std::vector< State* > {
public:
    JoinState( State* st = 0 ) :
	state_( st ),
	isFinal_( false ),
	isFuge_( false )
	{
    }

    void normalize() {
	std::sort( begin(), end() );
	std::unique( begin(), end() );
    }

    void push_back( State* const& st ) {
	if( st->delta( L'#' ) ) {
	    isFuge_ = true;
	}
	if( st->delta( L'$' ) ) {
	    isFinal_ = true;
	}

	std::vector< State* >::push_back( st );
    }

    void print() const {
	std::wcout<<"[";
	for( const_iterator it = begin(); it != end(); ++it ) {
	    std::wcout<<(*it)->getNumber()<<",";
	}
	// std::wcout<<"*"<< ( (state_)? state_->getNumber() : -1 ) <<"*"; if( isFinal_ ) std::wcout<<"F"; std::wcout<<"]";
    }

    State* state_;
    bool isFinal_;
    bool isFuge_;

private:
};

class JoinStateCompare {
public:
    bool operator() ( JoinState const* a, JoinState const* b ) {
	// std::wcout<<"Compare: "; a->print(); b->print(); std::wcout<<std::endl;
	

	JoinState::const_iterator ait = a->begin();
	JoinState::const_iterator bit = b->begin();
	for( ; ait != a->end() && bit != b->end(); ++ait, ++bit ) {
	    if( *ait != *bit ) {
		// std::wcout<<"return is " <<((*ait)->getNumber() < (*bit)->getNumber() )<<std::endl;
		// return ((*ait)->getNumber() < (*bit)->getNumber() );
		return (*ait < *bit );
	    }
	}
	if( ait != a->end() ) {
	    // std::wcout<<"return is  false " <<std::endl;
	    return false;
	}
	else if( bit != b->end() ) {
	    // std::wcout<<"return is  true " <<std::endl;
	    return true;
	}
	else {
	    // std::wcout<<"return is  false " <<std::endl;
	    return false;
	}
    }
};


class SetOfStates : public std::set< JoinState*, JoinStateCompare > {
public:
    ~SetOfStates() {
	std::wcerr<<"Destroy setOfStates ... "<<std::flush;
	for( const_iterator it = begin(); it != end();  ++it ) {
	    delete( *it );
	}
	std::wcerr<<"ok"<<std::endl;
    }

    void print() const {
	std::wcout<<"********** set of states *************" << std::endl;
	for( const_iterator it = begin(); it != end(); ++it ) {
	    (*it)->print();std::wcout<<std::endl;
	}
	std::wcout<<"**************************************" << std::endl;
    }

private:

};

