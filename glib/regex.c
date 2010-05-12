#include <glib.h>

static void
regex_test_print_uppercase_words (const gchar *str)
{
  /* Print all uppercase-only words. */
  GRegex *regex;
  GMatchInfo *match_info;

  regex = g_regex_new ("[A-Z]+", 0, 0, NULL);
  g_regex_match (regex, str, 0, &match_info);
  while (g_match_info_matches (match_info))
    {
      gchar *word = g_match_info_fetch (match_info, 0);
      g_print ("Found: %s\n", word);
      g_free (word);
      g_match_info_next (match_info, NULL);
    }
  g_match_info_free (match_info);
  g_regex_unref (regex);
}

static void
regex_test_address_and_port (const gchar *str)
{
  GError *err;
  GRegex *regex;
  GMatchInfo *match_info;
  gchar *matched;
  gchar *pattern;

  g_print ("pattern: [%s]\n", str);

  pattern = "(?P<protocol>https?)://(?P<address>[^/:]*)(:(?P<port>\\d+))?";

  err = NULL;
  regex = g_regex_new (pattern, 0, 0, &err);
  if (err)
    {
      g_warning ("failed to compile regex [%s]: %s", pattern, err->message);
      g_error_free (err);
      return;
    }

  g_regex_match (regex, str, 0, &match_info);

  matched = g_match_info_fetch_named (match_info, "protocol");
  if (matched)
    g_print ("protocol: [%s]\n", matched);

  matched = g_match_info_fetch_named (match_info, "address");
  if (matched)
    g_print ("address: [%s]\n", matched);

  matched = g_match_info_fetch_named (match_info, "port");
  if (matched)
    g_print ("port: [%s]\n", matched);

  g_match_info_free (match_info);
  g_regex_unref (regex);
}

int
main (int    argc,
      char **argv)
{
  regex_test_print_uppercase_words ("My name is Keedi Kim");

  regex_test_address_and_port ("http://192.168.0.30");
  regex_test_address_and_port ("http://192.168.0.30/onvif/services");
  regex_test_address_and_port ("http://192.168.0.30:80/onvif/services");

  regex_test_address_and_port ("http://localhost");
  regex_test_address_and_port ("http://localhost/onvif");
  regex_test_address_and_port ("http://localhost:3030/onvif");

  regex_test_address_and_port ("https://192.168.0.30");
  regex_test_address_and_port ("https://192.168.0.30/onvif/services");
  regex_test_address_and_port ("https://192.168.0.30:80/onvif/services");

  regex_test_address_and_port ("https://localhost");
  regex_test_address_and_port ("https://localhost/onvif");
  regex_test_address_and_port ("https://localhost:3030/onvif");

  return 0;
}
