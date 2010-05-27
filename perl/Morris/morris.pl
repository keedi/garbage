#!/usr/bin/env perl

use 5.010;
use common::sense;
use Config::Any::General;
use Morris;

my $config_file = 'morris.conf';

my $config = Config::Any::General->load( $config_file );
die "config file error!\n" unless $config;

my $morris = Morris->new_from_config( $config );
$morris->run;
