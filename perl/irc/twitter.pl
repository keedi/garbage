#!/usr/bin/env perl

use utf8;
use 5.010;

package TwitBot;

use parent 'Bot::BasicBot';
use Encode qw/decode encode/;
use LWP::Simple;

sub said {
    my ( $self, $args ) = @_;

    $args->{body} =~ m|https?://twitter.com/(.*?)/status/\d+|;
    my $id = $1;
    ( my $url = $& ) =~ s/^https/http/;

    my $content = get( $url );
    if ($content =~ m|<meta content="(.*?)" name="description" />|) {
        my $msg = $1;
        $self->say(
            channel => $args->{channel},
            body    => "\@$id: ".encode('utf-8', $msg),
        );
    }
}

1;

package main;

use common::sense;
use Bot::BasicBot;

my $bot = TwitBot->new(
    server   => 'irc.freenode.org',
    nick     => 'twitbot',
    channels => [ '#perl-kr', ],
    encoding => 'utf-8',
)->run;
