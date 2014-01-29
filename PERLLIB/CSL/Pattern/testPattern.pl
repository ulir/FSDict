#!/usr/bin/perl

use strict;

use lib "..";
use Pattern;
use utf8;
use encoding 'utf8';

# Standard, 1 pat
{
    my $hist = Pattern::applyInstruction( "teil", "[(t_th,0)]" );
    if( $hist ne "theil" ) { die "Test failed"; }
}

# Standard, 2 pat
{
    my $hist = Pattern::applyInstruction( "teil", "[(t_th,0)(ei_ey,1)]" );
    if( $hist ne "theyl" ) { die "Test failed"; }
}

# Reverse, 1 pat
{
    my $modern = Pattern::applyInstruction( "theil", "[(t_th,0)]", reverse=>1 );
    if( $modern ne "teil" ) { die "Test failed"; }
}

# Reverse, 2 pat
{
    my $modern = Pattern::applyInstruction( "theyl", "[(t_th,0)(ei_ey,1)]", reverse=>1 );
    if( $modern ne "teil" ) { die "Test failed"; }
}

# weird special characters
{
    my $hist = Pattern::applyInstruction( "übeltäter", "[(ü_v,0)(t_th,4)(ä_aͤ,5)]" );
    if( $hist ne "vbelthaͤter" ) { die "Test failed"; }
}

# weird special characters, reverse
{
    my $modern = Pattern::applyInstruction( "vbelthaͤter", "[(ü_v,0)(t_th,4)(ä_aͤ,5)]", reverse => 1 );
    if( $modern ne "übeltäter" ) { die "Test failed"; }
}



