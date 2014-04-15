#ifndef FSDICT_PATTERNWEIGHTS_H
#define FSDICT_PATTERNWEIGHTS_H FSDICT_PATTERNWEIGHTS_H

#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<map>
#include<math.h>
#include<fsdict/Global.h>
#include<fsdict/UTF8Locale/UTF8Locale.h>
#include<fsdict/Pattern/Pattern.h>

namespace fsdict {

    /**
     *
     * @author Ulrich Reffle <uli@cis.uni-muenchen.de>
     * @date 2009
     */
    class PatternWeights {
    public:
	static const int UNDEF = -1;

	typedef std::map< fsdict::Pattern, double >::iterator PatternIterator;
	typedef std::map< fsdict::Pattern, double >::const_iterator const_PatternIterator;

	/**
	 * @brief a PatternType describes the relation of the lengths of both pattern sides.
	 *        E.g.: the pattern t->th would have the type 1:2
	 *
	 * Those types are used to specify standard weights for certain pattern types
	 */
	class PatternType : public std::pair< size_t, size_t > {
	public:
	    PatternType( size_t l, size_t r ) {
		first = l;
		second = r;
	    }
	};

	PatternWeights();
        virtual ~PatternWeights() {}

	/**
	 * @brief Removes all the weights and defaults. Does NOT change the setting of the smartMerge mode.
	 */
	virtual void clear();

	/**
	 * @brief Removes all the explicit weights, but leaves the defaults intact. Does NOT change the setting of the smartMerge mode.
	 */
	virtual void clearExplicitWeights();

	inline size_t size() const {
	    return patternWeights_.size();
	}

	/**
	 * @return the weight for a given pattern, or PatternWeights::UNDEF if the pattern is not known
	 */
	double getWeight( const  fsdict::Pattern& pattern ) const;

	/**
	 * @brief set a new weight for a pattern
	 */
	void setWeight( const fsdict::Pattern& pattern, double weight );



	double getDefault( PatternType const& patternType ) const;


	void setDefault( PatternType const& patternType, double weight );


	/**
	 * @brief If "smartMerge" is activated, it will override the default settings
	 *        (set via setDefault()) and return the weight UNDEF for
	 *        all merges and splits of the form "xy <-> x" and "xy <-> y".
	 *        It does NOT override the specific weights added via setWeight()
	 *
	 */
	void setSmartMerge( bool t = true );


	const_PatternIterator patternsBegin() const {
	    return patternWeights_.begin();
	}

	PatternIterator patternsBegin() {
	    return patternWeights_.begin();
	}

	const_PatternIterator patternsEnd() const {
	    return patternWeights_.end();
	}

	PatternIterator patternsEnd() {
	    return patternWeights_.end();
	}


	/**
	 * @brief prints the pattern weights
	 */
	void print( std::wostream& str = std::wcout ) const;


	void loadFromFile( const char* patternFile );
	void writeToFile( const char* patternFile ) const;

	void writeToXML( std::wostream& os ) const;
	void writeToXML( const char* xmlFile ) const;


	void sortToVector( std::vector< std::pair< fsdict::Pattern, double > >* vec ) const;

	private:

	/**
	 * @brief This data structure maps the known patterns to their weights
	 */
	std::map< fsdict::Pattern, double> patternWeights_;

	/**
	 *
	 */
	std::map< PatternType, double > defaultWeights_;

	bool smartMerge_;

	/**
	 * @brief sorts the std::pairs according to their second value
	 */
	template< typename pair_t >
	static bool sortBySecond( pair_t const& a, pair_t const& b ) {
	    return ( a.second > b.second ); // reverse ordering
	}

   }; // class PatternWeights



} // ns csl

#endif
