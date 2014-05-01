#!/usr/bin/perl


use strict;

package Freqhash;

sub new {
    my $class=shift;
    my $freqlist_file = shift;
    my $self = {};

    bless($self,$class);

    open(FILE,"<$freqlist_file") or die "Couldn't open Frequency list: $!";
    while(my($token,$freq) = split(/\#/,<FILE>)) {
	chomp $token;
	$self->{hash}{$token} = $freq;
    }
    close(FILE);

    return $self;

}

sub lookup {
    my $self = shift;
    my $token = shift;
    return $self->{hash}{$token};
}


1;
