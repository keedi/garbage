#!/usr/bin/env perl

use 5.010;
use common::sense;
use Morris;

# or when you instantiate from a config file
my $config = read_config_file( $config_file );
my $morris = Morris->new_from_config( $config );
$morris->run;
