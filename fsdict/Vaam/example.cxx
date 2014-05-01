/**
 * This is an example program to demonstrate how to use Vaam.
 *
 * @author Ulrich Reffle
 */

#include "./Vaam.h"

int main() {

    fsdict::MinDic<> baseDic;
    baseDic.loadFromFile( "fsdict/Vaam/Test/small.base.mdic" ); // small.base.mdic was created by the tool compileMD

    fsdict::Vaam vaam( baseDic, "fsdict/Vaam/Test/small.patterns.txt" );
    vaam.setMaxNrOfPatterns( 3 );

    // create a std::vector of fsdict::Interpretation s to collect Vaam's answers
    std::vector< fsdict::Interpretation > answers;

    std::wstring query;
    while( std::wcin >> query ) {
	answers.clear();
	vaam.query( query, &answers );

	std::wcout<<"Possible interpretations:"<<std::endl;

	// for all possible interpretations:
	for( std::vector< fsdict::Interpretation >::const_iterator it = answers.begin(); it!= answers.end(); ++it ) {
	    std::wcout << "original (modern) word: "<< it->baseWord << std::endl;
	    std::wcout<< "Pattern applications: ";

	    // for each PosPattern of the Instruction:
	    for( fsdict::Instruction::const_iterator posPattern = it->instruction.begin(); posPattern != it->instruction.end(); ++posPattern ) {
		std::wcout<<"("<<posPattern->getLeft()<<"->"<<posPattern->getRight()<<","<<posPattern->getPosition()<<")";
	    }
	    std::wcout<<std::endl;

	    // use method print_v2 for alternative, very useful print format:
	    std::wcout<<"Alternative format: ";
	    it->print_v2();
	    std::wcout<<std::endl;
	}
	std::wcout<<std::endl;
    }
}
