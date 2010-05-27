#!/usr/bin/perl 

use 5.010;
use common::sense;
use Config::Any::General;

my $config = Config::Any::General->load( 'morris.conf' );
if ($config) {
    say "Name: $config->{ name }";
}
