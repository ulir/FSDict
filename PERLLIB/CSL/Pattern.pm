

use strict;

package Pattern;

use Data::Dumper;

sub applyInstruction {
    my ( $inputWord, $instruction, %attr ) = @_;

    my @posPatterns;
    while( $instruction =~ m/(\(.*?\))/g ) {
	my $posPatternStr = $1;
	my ( $left, $right, $position ) = ( $posPatternStr =~ m/\((.*?)_(.*?),(\d+)\)/ );
	push( @posPatterns, { left=>$left, right=>$right, position=>$position } );
    }

    my $newWord = $inputWord;

    if( ! $attr{reverse} ) {
	while( my $posPattern = pop( @posPatterns ) ) {
	    if( substr( $newWord, $posPattern->{position}, length( $posPattern->{left} ) ) ne $posPattern->{left} ) {
		#warn "package Pattern: instruction '$instruction' not applicable to input word. str is '".substr( $newWord, $posPattern->{position}, length( $posPattern->{left} ) )."'";
		return undef;
	    }
	    substr( $newWord, $posPattern->{position}, length( $posPattern->{left} ), $posPattern->{right} );
	}
    }
    else {
	while( my $posPattern = shift( @posPatterns ) ) {
	    if( substr( $newWord, $posPattern->{position}, length( $posPattern->{right} ) ) ne $posPattern->{right} ) {
		warn "package Pattern: instruction '$instruction', pattern $$posPattern{left}_$$posPattern{right} not applicable to input word. str is '".substr( $newWord, $posPattern->{position}, length( $posPattern->{right} ) )."'";
		return undef;
	    }
	    substr( $newWord, $posPattern->{position}, length( $posPattern->{right} ), $posPattern->{left} );
	}
    }


    return $newWord;
}


1;
